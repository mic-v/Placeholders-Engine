#version 420 //Version of OpenGL we're using. - 4.2

layout(binding = 30) uniform sampler2D uTex;

uniform mat4 view;

uniform float height;

in vec2 texcoord;
out vec4 outColor;

float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);


vec2 Pack(vec2 param)
{
	return param * 0.5 + 0.5;
}

vec2 Unpack(vec2 param)
{
	return param + param - 1.0;
}

void main()
{
	
vec2 offset = 1.0f / textureSize(uTex, 0);
vec3 result = texture(uTex, texcoord).rgb * weight[0];

 for (int i=1; i<5; ++i) {
result += texture(uTex, texcoord + vec2(0.0, offset.y * i)).rgb * weight[i];
result += texture(uTex, texcoord - vec2(0.0, offset.y * i)).rgb * weight[i];

    }

outColor = vec4(result.rgb, 1.0f);

}