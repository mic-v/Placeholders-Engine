#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitangents;

uniform float uTime;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

out vec3 newtans;
out vec3 newbitans;
void main()
{
	mat4 uModelView = view * model;
	texcoord = uv;
	newtans = mat3(uModelView) * tangents;
	newbitans = mat3(uModelView) * bitangents;
	norm = mat3(uModelView) * normal;
	vec4 position = vec4(vert, 1.0f);
	position.y += (
		sin(position.x * 0.45 + uTime * 1.0)/8 + sin(position.x * 0.76 - uTime * 0.352)/8 ) 
		* 0.125;
	vec4 viewSpace = view * model * position;
	
	
	gl_Position = projection * viewSpace;

	pos = viewSpace.xyz;
}