#version 450

layout(binding = 5) uniform sampler2D uTexLook;
layout(binding = 0) uniform sampler2D uTex;
in vec2 texcoord;
layout (location = 0) out vec4 outColor;
layout (location = 1) out vec4 maskColor;

void main() 
{
	outColor = vec4(255, 0.0, 0.0, 1.0f);
	maskColor = outColor;
}