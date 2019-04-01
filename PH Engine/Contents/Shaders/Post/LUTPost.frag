#version 420 //Version of OpenGL we're using. - 4.2


layout(binding = 12) uniform sampler3D uLUT3D;
layout(binding = 30) uniform sampler2D uSceneTex;


uniform float LUTSize;
uniform float uAmount = 0.0f;

in vec2 texcoord;
out vec4 outColor;
vec3 finalColor;

void main()
{
	vec3 source = texture(uSceneTex, texcoord).rgb;

	vec3 scale = vec3((LUTSize - 1.0) / LUTSize);
	vec3 offset = vec3(1.0 / (2.0 * LUTSize));

	vec3 applyLut = texture(uLUT3D, scale * source + offset).rgb;
	finalColor = mix(source, applyLut, uAmount);

outColor = vec4(finalColor, 1.0f);

}