#version 420

// The sampler2D represents a texture and must be a uniform.
// The value of the uniform is the slot of the texture. This is
// usually simply 0 if you are only using one texture.
uniform sampler2D uTex;

// This texture coordinate will have been interpolated by
// the rasterizer.
in vec2 texcoord;
out vec4 outColor;

void main()
{	
	// The texture() function will fetch the color from uTexture at texcoord.
	// Notice that we decided to only read RGB values in this case.
	// For textures with an alpha channel, you can also read the 'a'.
	vec4 texture = texture(uTex, texcoord).rgba;
	
	outColor = texture;//vec4(texture, 1.0f);
    outColor.a = 0.5f;
}
