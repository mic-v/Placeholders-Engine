#version 460

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

void main()
{
	 gl_Position =  projection * view * model * vec4(vert, 1.0);
}