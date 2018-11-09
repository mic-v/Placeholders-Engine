#version 450

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 tNormal;


void main()
{
	tNormal = normal;
	
	gl_Position = projection * view * model * vec4(vert, 1.0f);
}