#version 450

layout(binding = 30) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;

void main() 
{
	outColor = vec4(255.0, 255.0, 255.0, 255.0);
}