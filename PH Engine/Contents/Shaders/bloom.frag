#version 450

layout(binding = 29) uniform sampler2D uBloom;
layout(binding = 30) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;
void main() 
{
    vec3 hdrColor = texture(uTex, texcoord).rgb;      
    vec3 bloomColor = texture(uBloom, texcoord).rgb;
    hdrColor += bloomColor; // additive blending
    outColor = vec4(hdrColor, 1.0);
}