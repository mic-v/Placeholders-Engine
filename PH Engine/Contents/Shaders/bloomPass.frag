#version 450

layout(binding = 5) uniform sampler2D uBloom;
//layout(binding = 28) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;
void main() 
{
	vec4 pass = texture(uBloom, texcoord);

	vec3 diff = pass.rgb - (0.0, 0.0, 0.0);
	float alpha = step(dot(diff, diff), 0.1);

	pass.a = alpha;

	outColor = pass;
}