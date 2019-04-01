#version 450


layout(binding = 30) uniform sampler2D uTex;
in vec2 texcoord;
out vec4 outColor;

vec4 col = vec4(0,0,0,1);

uniform vec3 screenSize;


 float sobelX[9] = float[](
    1.0, 2.0, 1.0, 
    0.0, 0.0, 0.0, 
   -1.0, -2.0, -1.0 
);

float sobelY[9] = float[](
    1.0, 0.0, -1.0, 
    2.0, 0.0, -2.0, 
    1.0, 0.0, -1.0 
);


vec2 pixelSize = vec2(1.0, 1.0) / screenSize.rg;
float offsetX = gl_FragCoord.x / pixelSize.x;
float offsetY = gl_FragCoord.y / pixelSize.y;

 vec2 offsets[9] = vec2[](
        vec2(-offsetX,  offsetY), // top-left
        vec2( 0.0f,    offsetY), // top-center
        vec2( offsetX,  offsetY), // top-right
        vec2(-offsetX,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offsetX,  0.0f),   // center-right
        vec2(-offsetX, -offsetY), // bottom-left
        vec2( 0.0f,   -offsetY), // bottom-center
        vec2( offsetX, -offsetY)  // bottom-right    
    );

void main() 
{


vec3 tex = texture(uTex, texcoord.st).rgb;
vec3 sum;
vec3 image[9];
sum += vec3(texture(uTex, texcoord.st + offsets[0])).rgb * sobelX[0];
sum += vec3(texture(uTex, texcoord.st + offsets[1])).rgb * sobelX[1];
sum += vec3(texture(uTex, texcoord.st + offsets[2])).rgb * sobelX[2];
sum += vec3(texture(uTex, texcoord.st + offsets[3])).rgb * sobelX[3];
sum +=vec3(texture(uTex, texcoord.st + offsets[4])).rgb  * sobelX[4];
sum += vec3(texture(uTex, texcoord.st + offsets[5])).rgb * sobelX[5];
sum += vec3(texture(uTex, texcoord.st + offsets[6])).rgb * sobelX[6];
sum += vec3(texture(uTex, texcoord.st + offsets[7])).rgb * sobelX[7];
sum += vec3(texture(uTex, texcoord.st + offsets[8])).rgb * sobelX[8];
//sum += vec3(texture(uTex, texcoord.st + offsets[9])).rgb * sobelX[9];

sum += vec3(texture(uTex, texcoord.st + offsets[0])).rgb * sobelY[0];
sum += vec3(texture(uTex, texcoord.st + offsets[1])).rgb * sobelY[1];
sum += vec3(texture(uTex, texcoord.st + offsets[2])).rgb * sobelY[2];
sum += vec3(texture(uTex, texcoord.st + offsets[3])).rgb * sobelY[3];
sum +=vec3(texture(uTex, texcoord.st + offsets[4])).rgb  * sobelY[4];
sum += vec3(texture(uTex, texcoord.st + offsets[5])).rgb * sobelY[5];
sum += vec3(texture(uTex, texcoord.st + offsets[6])).rgb * sobelY[6];
sum += vec3(texture(uTex, texcoord.st + offsets[7])).rgb * sobelY[7];
sum += vec3(texture(uTex, texcoord.st + offsets[8])).rgb * sobelY[8];
//sum += vec3(texture(uTex, texcoord.st + offsets[9])).rgb * sobelY[9];

float g = length(sum);
outColor = vec4(tex - vec3(g), 1.0);

}