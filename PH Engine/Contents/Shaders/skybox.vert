#version 460
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(std140, binding = 1) uniform Time
{
	uniform float uTime;
};

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

void main()
{

	texcoord = uv;

	norm = mat3(view) * mat3(model) * normal;

	vec4 viewSpace = view * model * vec4(vert, 1.0f);

	gl_Position = projection * viewSpace;

	pos = viewSpace.xyz;
}