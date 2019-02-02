#version 450

out vec4 outColor;

in vec3 textNormal;

uniform sampler2D uTex;

void main()
{
	vec4 newText = texture(uTex, textNormal);
	
	outColor.rgb = newText.rgb;
	//SET TRANSPARENCY/ALPHA TO PICTURES TRANSPARENCY/ALPHA
	outColor.a = texture.a;
}