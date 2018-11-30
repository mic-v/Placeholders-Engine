#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 mcolor;

uniform mat4 projection;
out vec4 f_color;

void main()
{
	f_color = mcolor;
	gl_Position = projection * vec4(position, 1.0f);
}