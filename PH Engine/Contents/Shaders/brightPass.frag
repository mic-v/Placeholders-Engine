#version 450

layout(binding = 30) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;
void main() 
{
    vec3 color = texture(uTex, texcoord).rgb;      
    
    float brightness = (color.r + color.g + color.b) / 3.0f;

    if(brightness > 1.0f){

    outColor = vec4(color, 1.0f);

    }else{
        outColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}