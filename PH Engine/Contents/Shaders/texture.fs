#version 450

uniform vec4 LightPosition;
uniform mat4 view;
//color
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 LightSpecular;
//scalars
uniform float LightSpecularExponent;
uniform float Attenuation_Constant;
uniform float Attenuation_Linear;
uniform float Attenuation_Quadratic;



//the slot in which ur texture is bound in, by default set to 0
//goes from 0-32, 
//if multitexturing is needed, utilize other slots
uniform sampler2D uTex;


//stuff coming in from frag shader

in vec2 texcoord;
in vec3 norm;
in vec3 pos;
out vec4 outColor;

void main()
{
	outColor.rgb = LightAmbient; //= texture(uTex, texcoord);
	//account for rasterizer interpolating
	vec3 normal = normalize(norm);
	vec3 lightVec = (view * LightPosition).xyz - pos;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;

	float NdotL = dot(normal, lightDir);

	if (NdotL > 0.0){
		//how much the light affects this surface

		//calculate attenuation
		float attenuation = 1.0 / (Attenuation_Constant + (Attenuation_Linear * dist)+ (Attenuation_Quadratic * dist * dist));

		//calculate diffuse 
		outColor.rgb += LightDiffuse * NdotL * attenuation;

		//phong half vector 
		float NdotHV = max(dot(normal, normalize(lightDir + normalize(-pos))), 0.0);

		//calcluate specular contribution 
		outColor.rgb += LightSpecular * pow(NdotHV, LightSpecularExponent) * attenuation;

	}
	vec4 textureColor = texture(uTex, texcoord);
	outColor.rgb *= textureColor.rgb;
	outColor.a = textureColor.a;
	
}