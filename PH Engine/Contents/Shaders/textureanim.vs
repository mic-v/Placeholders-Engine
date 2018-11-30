#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (location = 4) in vec3 vert2;
layout (location = 5) in vec2 uv2;
layout (location = 6) in vec3 normal2;

uniform float lerpParam;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

void main()
{

	texcoord = uv;//mix(uv, uv2, lerpParam);
	norm = mat3(view) * mat3(model) * normal;//mix(normal, normal2, lerpParam);
	vec4 viewSpace = view * model * vec4(mix(vert, vert2, lerpParam), 1.0f);

	
	gl_Position = projection * viewSpace;

	pos = viewSpace.xyz;
}