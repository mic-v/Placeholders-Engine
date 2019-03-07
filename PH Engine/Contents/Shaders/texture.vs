#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitangents;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

out vec3 newtans;
out vec3 newbitans;
void main()
{
	texcoord = uv;
	newtans = tangents;
	newbitans = bitangents;
	norm = mat3(view) * mat3(model) * normal;
	vec4 viewSpace = view * model * vec4(vert, 1.0f);
	
	
	gl_Position = projection * viewSpace;

	pos = viewSpace.xyz;
}