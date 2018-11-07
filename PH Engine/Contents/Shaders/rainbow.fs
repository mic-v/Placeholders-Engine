#version 450

out vec4 outColor;

in vec3 tNormal;

void main()
{
	outColor = vec4(tNormal, 1.0f);
}