#version 420

layout(binding = 0) uniform samplerCube uTexCube;

in vec2 texcoord;
in vec3 norm;
in vec3 pos;

out vec4 outColor;

void main()
{
	outColor = texture(uTexCube, normalize(norm));
}