#version 450

layout(binding = 28) uniform sampler2D sobel;
layout(binding = 29) uniform sampler2D mask;
layout(binding = 30) uniform sampler2D uScene;
in vec2 texcoord;
out vec4 outColor;
void main() 
{
    vec4 s = texture(sobel, texcoord); 
    vec4 m = texture(mask, texcoord);
    vec4 u = texture(uScene, texcoord); 
  outColor = mix( s, u, m.r );
}