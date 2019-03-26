#version 460

uniform vec3 uCameraPosition;
uniform vec3 uLightPosition;

in vec2 texcoord;
in vec3 norm;
in vec3 pos;
in vec4 shadowcoord;

layout(binding = 13) uniform sampler2D uTexShadowDepth;
layout(binding = 14) uniform sampler2D uTexLightColor;

out vec4 outColor;

void main()
{
	vec3 normal = normalize(norm * 2 - 1);
	// TODO: Calculate the shadow texture coordinates by converting the viewspace position into the light's clip space
	//vec4 shadowcoord = uViewToShadow * position;
	float shadowDepth = texture(uTexShadowDepth, shadowcoord.xy).r;

	// TODO: change level of shadow depending on whether the depth of the shadow map is in front or behind the scene
	// You'll also want to adjust this calculation to avoid shadow acne! (Refer to slides 17-18 for an example)
	// This threshold should be increased based on how perpendicular the light is to the surface!
	float shadowAmount = 1;
	// shadowAmount is multiplied into the diffuse and specular equations, meaning there will be no lighting if shadowAmount is 0!
	if(shadowDepth < shadowcoord.z - 0.00022f)
	{
		shadowAmount = shadowAmount = 0.1f;
	}
          
   	// the dot product of the normal and light direction determines how much light there is
	vec3 lightDir = normalize(uLightPosition - pos);
	float NdotL = dot(normal, lightDir);		
	// Clamp NdotL so that there are negative values, otherwise 
	// the opposite side of an object would receive negative lighting!
	NdotL = max(NdotL, 0.0);
	
	// Calculate the diffuse contribution
	outColor.rgb += albedoColor.rgb * uLightColor * NdotL * shadowAmount;
				
	// Normalized vector pointing towards the camera
	vec3 eye = normalize(uCameraPosition - pos); //gets camera direction
	vec3 reflection = reflect(-lightDir, normal);	
	float specularStrength = dot(reflection, eye);
	specularStrength = max(specularStrength, 0.0); // don't let it fall before zero

	// Calculate the specular contribution
	outColor.rgb += uLightColor * pow(specularStrength, uMaterialSpecularExponent) * shadowAmount;
}
