#version 420


uniform mat4 model;
uniform mat4 view;
uniform mat4 model;



layout(location = 0) in vec3 in_vert;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

void main()
{	
	norm = mat3(view) * in_normal;
	pos =  model * vec4(in_vert, 1.0f)).xyz;

	gl_Position = model * vec4(pos, 1.0f);
}
