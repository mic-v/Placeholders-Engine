#version 450


uniform mat4 view;

uniform vec4 LightDirection;
uniform float uTime;

//color

//scalars


struct PointLight{

	vec3 LightAmbient;
	vec3 LightDiffuse;
	vec3 LightSpecular;
	float LightSpecularExponent;




};
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

//the slot in which ur texture is bound in, by default set to 0
//goes from 0-32, 
//if multitexturing is needed, utilize other slots
uniform sampler2D uTex;
uniform mat4 depthBiasMVP;
layout (binding = 13) uniform sampler2D uTexShadowDepth;
layout (binding = 14) uniform sampler2D uTexNormal;


//stuff coming in from frag shader

in vec2 texcoord;
in vec3 norm;
in vec3 newtans;
in vec3 newbitans;
in vec3 pos;
out vec4 outColor;
vec3 normal;


void CalcPointLight(PointLight light){
	
	//vec3 normal = normalize(norm);


	float NdotL = dot(normal, LightDirection.xyz);

vec4 shadowcoord = depthBiasMVP * vec4(pos, 1.0);

float shadowDepth = texture(uTexShadowDepth, shadowcoord.xy).r;

float shadowAmount = 1.0f;

	vec3 col = vec3(0);
	if(shadowDepth < shadowcoord.z - 0.00022)
	{
		shadowAmount = 0.1f;
		
	}
//	outColor.rgb += col.rgb * shadowAmount;
	
		//how much the light affects this surface
if(NdotL > 0.0f){

		//calculate diffuse 
		outColor.rgb += light.LightDiffuse * NdotL * shadowAmount;

		//phong half vector 
		float NdotHV = max(dot(normal, normalize(LightDirection.xyz + normalize(-pos))), 0.0);

		//calcluate specular contribution 
		outColor.rgb += light.LightSpecular * pow(NdotHV, light.LightSpecularExponent) * shadowAmount;

	
}

}

void main()
{
	float rads = 90;
	outColor.rgb = pointLights[0].LightAmbient;
	 //= texture(uTex, texcoord);
	//account for rasterizer interpolating
	normal = normalize(norm);
	vec3 tangent = normalize(newtans); 
	vec3 bitangent = normalize(newbitans);

	mat3 tangentToView = mat3( tangent.x, bitangent.x, normal.x,
								tangent.y, bitangent.y, normal.y,
								tangent.z, bitangent.z, normal.z);

	normal = texture(uTexNormal, texcoord + uTime/100).rgb * 2.0 - 1.0;
	
	normal += texture(uTexNormal, texcoord - uTime/100).rgb * 2.0 - 1.0;
	normal += texture(uTexNormal,vec2(cos(rads),sin(rads)) * texcoord - uTime/100).rgb * 2.0 - 1.0;
	normal += texture(uTexNormal,vec2(cos(rads),sin(rads)) * texcoord + uTime/100).rgb * 2.0 - 1.0;
	normal = normalize(normal);
	normal = normal * tangentToView;

	for(int i = 0; i < NR_POINT_LIGHTS; i++){
		//outColor.rgb += pointLights[i].LightAmbient;
		CalcPointLight(pointLights[i]);
	}
	
	vec4 textureColor = texture(uTex,  texcoord);
	outColor.rgb *= textureColor.rgb;
	outColor.a = textureColor.a;
	
}