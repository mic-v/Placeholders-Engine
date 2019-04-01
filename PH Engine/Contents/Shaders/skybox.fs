#version 420

layout(binding = 25) uniform samplerCube uTexCube;

in vec2 texcoord;
in vec3 norm;
in vec3 pos;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec4 maskColor;


void main()
{
	outColor = texture(uTexCube, normalize(norm));
	maskColor = vec4(0.0, 0.0, 0.0, 0.0);
}