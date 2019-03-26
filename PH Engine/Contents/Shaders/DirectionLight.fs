#version 450


uniform mat4 view;

uniform vec4 LightDirection;
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


//stuff coming in from frag shader

in vec2 texcoord;
in vec3 norm;
in vec3 pos;
out vec4 outColor;



void CalcPointLight(PointLight light){
	
	vec3 normal = normalize(norm);


	float NdotL = dot(normal, LightDirection.xyz);

vec4 shadowcoord = depthBiasMVP * vec4(pos, 1.0);

float shadowDepth = texture(uTexShadowDepth, shadowcoord.xy).r;

float shadowAmount = 1.0f;

	// shadowAmount is multiplied into the diffuse and specular equations, meaning there will be no lighting if shadowAmount is 0!
	if(shadowDepth < shadowcoord.z - 0.00022)
	{
		shadowAmount = 0.1f;
	}

	
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
	outColor.rgb = pointLights[0].LightAmbient;
	 //= texture(uTex, texcoord);
	//account for rasterizer interpolating
	for(int i = 0; i < NR_POINT_LIGHTS; i++){
		//outColor.rgb += pointLights[i].LightAmbient;
		CalcPointLight(pointLights[i]);
	}
	vec4 textureColor = texture(uTex, texcoord);
	outColor.rgb *= textureColor.rgb;
	outColor.a = textureColor.a;
	
}