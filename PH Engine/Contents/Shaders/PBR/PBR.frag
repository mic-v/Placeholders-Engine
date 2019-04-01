#version 460

#define PI 3.14159265359
//Quinn Szmutni PBR Shader (based off learnopengl PBR theory tutorial)
//ALL PBR CALCULATIONS MUST BE DONE IN LINEAR SPACE ALL INPUTS PASSED MUST BE LINEAR OR IT WILL NOT LOOK PROPER.


in vec2 texcoord;
in vec3 norm;
in vec3 pos;

in vec3 out_tangents;
in vec3 out_bitangents;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec4 maskColor;

uniform vec3 uCameraPosition;
uniform mat4 iView;
uniform mat4 depthBiasMVP;



layout(binding = 0) uniform sampler2D uAlbedoMap; //Albedo Data
layout(binding = 1) uniform sampler2D uRoughnessMap; //Roughness [0-1]
layout(binding = 2) uniform sampler2D uMetallicMap; //Metalicness [0-1]
layout(binding = 3) uniform sampler2D uAoMap; //Ambient Occlusion map [0-1]
layout(binding = 4) uniform sampler2D uNormalMap; //Normal map [0-1]
layout(binding = 25) uniform samplerCube uTexSpecularIrradiance;
layout(binding = 26) uniform samplerCube uTexIrradiance;
layout(binding = 27) uniform sampler2D uTexSpecularBRDF;
layout(binding = 28) uniform sampler2D uTexShadowDepth;


uniform vec3 uLightPosition;
uniform vec3 uLightColor;

//Normalization Values for normal maps
vec3 tangents;
vec3 bitangents;
vec3 normal;
mat3 TBN;


float dot0(vec3 v0, vec3 v1){
	return max(dot(v0, v1), 0.0f);
}

vec3 frenselEquation(float angle, vec3 f0){ // Calculates ratio between specular and diffuse reflection (How much surface reflects/refracts lighting)

	return f0 + (1.0 - f0) * pow(1.0 - angle, 5.0); // f0 is how much the surface reflects at a angle of 90. (Most things besides metal can have a constant f0 of 0.04f)
} 

float DistributionGGX(vec3 N, vec3 HalfWayVector, float Roughness){ // Aproximates ratio of microfacets that are alligned with our halfway vector

	float a = Roughness * Roughness;
	float a2 = a*a;
	float NdotHalf = max(dot(N,HalfWayVector), 0.0f);
	float NdotHalf2 = NdotHalf * NdotHalf;

	float numerator = a2;
	float denominator = (NdotHalf2 * (a2 - 1.0f) + 1.0f);
		denominator = PI * denominator * denominator;

		return numerator/denominator;

}


// Mesures microfacet shadowing based on roughness [0-1]
float GeometrySchlickGGX(float NdotV, float Roughness){
	float r = (Roughness + 1.0f);
	float k = (r*r) / 8.0f;

	float numerator = NdotV;
	float denominator = NdotV * (1.0 - k) + k;

	return numerator/denominator;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float Roughness){
	float NdotV = max(dot(N,V), 0.0f);
	float NdotL = max(dot(N,L), 0.0f);

	float ggxView = GeometrySchlickGGX(NdotV, Roughness);
	float ggxLight = GeometrySchlickGGX(NdotL, Roughness);

	return ggxView * ggxLight;
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}   

void main(){

tangents = normalize(out_tangents);
bitangents = normalize(out_bitangents);
normal = normalize(norm);

TBN = mat3(tangents.x, bitangents.x, normal.x,tangents.y, bitangents.y, normal.y,tangents.z, bitangents.z, normal.z);

vec4 shadowcoord = depthBiasMVP * vec4(pos, 1.0);

float shadowDepth = texture(uTexShadowDepth, shadowcoord.xy).r;

float shadowAmount = 1.0f;

	// shadowAmount is multiplied into the diffuse and specular equations, meaning there will be no lighting if shadowAmount is 0!
	if(shadowDepth < shadowcoord.z - 0.00022)
	{
		shadowAmount = 0.1f;
	}

	
vec3 uAlbedo = texture(uAlbedoMap, texcoord).rgb; //Albedo Data
uAlbedo.r = pow(uAlbedo.r, 2.2);
uAlbedo.g = pow(uAlbedo.g, 2.2);
uAlbedo.b = pow(uAlbedo.b, 2.2);
float uMetallic = texture(uMetallicMap, texcoord).r; //Metalicness [0-1]
float uRoughness = texture(uRoughnessMap, texcoord).r; //Roughness [0-1]
float uAo = texture(uAoMap, texcoord).r; //Ambient Occlusion map [0-1]
normal = normalize(TBN * (texture(uNormalMap, texcoord).rgb * 2.0 - 1.0)); //[0-1]//normalize(TBN * (texture(uNormalMap, texcoord).rgb * 2.0 - 1.0));

//normal = normalize(norm * 2.0f - 1.0f); //Normalized our lerp'd normal from vert shader (Change it from [-1-1])

vec3 cameraVec = normalize(uCameraPosition - pos); //gets camera direction

vec3 reflected = reflect(-cameraVec, normal);

vec3 f0 = vec3(0.04);
f0 = mix(f0, uAlbedo, uMetallic); //Very f0 based on metalness with LERP
vec3 L_o = vec3 (0.0); //radient flux^2/Area * Solid Angle * cos(Theta)

//Forloop here for multiple lights

//for(int i = 0; i <= 4; ++i){
// Calculates pre-light radience
vec3 L = normalize(uLightPosition - pos);
vec3 HalfWayVector = normalize(cameraVec + L); //This is a half way vector. Its used to calculate the halfway positon between the viewer and the light position.
										   // The more the microfacets are alligned to the halfway vector the shaper and stronger the specular reflection is
float lightDistance = length(uLightPosition - pos); // Light Distance
float attenuation = 1.0 / (lightDistance * lightDistance * 0.001 + 0.001); // Light drops off based on distance
vec3 radiance = uLightColor * attenuation;	


float cosLo = dot0(normal, -reflected);

//BASIC PBR

// cook-torrance brdf
	float NDF = DistributionGGX(normal, HalfWayVector, uRoughness);
	float Geo = GeometrySmith(normal,cameraVec,L, uRoughness);
	vec3 F = frenselEquation(max(dot(HalfWayVector, cameraVec), 0.0), f0); //CosAngle, f0

	
	
	// Calculates each lights contribution to the reflectence equation

	vec3 ratioSpecular = F; //Represents the energy of light reflected so therefor remaining ratio is refracted light
	vec3 ratioDiffuse = vec3(1.0) - ratioSpecular;

	ratioDiffuse *= 1.0 - uMetallic;


	vec3 numerator = NDF * Geo * F;
	float denominator = 4 *	max(dot(normal,cameraVec), 0.0) * max(dot(normal, L), 0.0) + 1.0f;
	vec3 specular = numerator / denominator;


	//add to outgoing radience L_o
	float NdotL = max(dot(normal,L), 0.0);
	L_o += (ratioDiffuse * uAlbedo / PI + specular) * radiance * NdotL;
// end loop here
//}


//SKYBOX PBR AMBIENT IBL DIFFUSE AND SPEC
F = fresnelSchlickRoughness(max(dot(normal, cameraVec), 0.0), f0, uRoughness);

 	ratioSpecular = F;
    ratioDiffuse = 1.0 - ratioSpecular;
    ratioDiffuse *= 1.0 - uMetallic;
// Convert the normal to worldspace
	//vec3 convertNormal = mat3(iView) * normal;

	vec3 irradiance = texture(uTexIrradiance, normal).rgb;
	vec3 diffuseIBL =  uAlbedo * irradiance * shadowAmount;

	vec2 specularBDRF = texture(uTexSpecularBRDF, vec2(max(dot(normal, cameraVec), 0.0), uRoughness)).rg; //SAMPLE FROM LOOKUP TEXTUER BASED ON ANGLE

	
	vec3 specularIrradiance = textureLod(uTexSpecularIrradiance, reflected,  uRoughness * 4.0f).rgb;


	vec3 specularIBL = (F * specularBDRF.x + specularBDRF.y) * specularIrradiance;



	vec3 ambient = ((ratioDiffuse * diffuseIBL + specularIBL) * uAo); //vec3(0.03) * uAlbedo * uAo;
	//SKYBOX AMBIENT ENDS HERE

	vec3 color = ambient + L_o;

	//Gamma correction
	color = color/(color + vec3(1.0f));
	color = pow(color, vec3(1.0/2.2f));

	outColor = vec4(color, 1.0f);
	//outColor.rgb =  bitangents * 0.5 + 0.5;
	maskColor = vec4(0.0, 0.0, 0.0, 0.0);
}

