#version 460

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 texcoord;

void main()
{
	texcoord = uv;
	gl_Position = vec4(vert, 1.0);

}