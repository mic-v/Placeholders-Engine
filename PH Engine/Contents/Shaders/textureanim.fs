#version 450


uniform mat4 view;
//color

//scalars


struct PointLight{

	vec4 LightPosition;

	vec3 LightAmbient;
	vec3 LightDiffuse;
	vec3 LightSpecular;


	float LightSpecularExponent;
	float Attenuation_Constant;
	float Attenuation_Linear;
	float Attenuation_Quadratic;



};
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

//the slot in which ur texture is bound in, by default set to 0
//goes from 0-32, 
//if multitexturing is needed, utilize other slots
uniform sampler2D uTex;


//stuff coming in from frag shader

in vec2 texcoord;
in vec3 norm;
in vec3 pos;
out vec4 outColor;



void CalcPointLight(PointLight light){
	
	vec3 normal = normalize(norm);
	vec3 lightVec = (view * light.LightPosition).xyz - pos;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;

	float NdotL = dot(normal, lightDir);

	if (NdotL > 0.0){
		//how much the light affects this surface

		//calculate attenuation
		float attenuation = 1.0 / (light.Attenuation_Constant + (light.Attenuation_Linear * dist)+ (light.Attenuation_Quadratic * dist * dist));

		//calculate diffuse 
		outColor.rgb += light.LightDiffuse * NdotL * attenuation;

		//phong half vector 
		float NdotHV = max(dot(normal, normalize(lightDir + normalize(-pos))), 0.0);

		//calcluate specular contribution 
		outColor.rgb += light.LightSpecular * pow(NdotHV, light.LightSpecularExponent) * attenuation;

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