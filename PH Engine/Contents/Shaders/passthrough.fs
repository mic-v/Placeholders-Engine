#version 450

layout(binding = 30) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;

void main() 
{
	outColor = texture(uTex, texcoord);
}