#pragma once
#include "Engine/Texture.h"
#include <vector>



struct TextureFilter
{
	GLenum mag = GL_LINEAR;
	GLenum min = GL_LINEAR_MIPMAP_LINEAR;
};


struct TextureWrap
{
	TextureWrap();

	union
	{
		struct
		{
			GLenum x, y, z;
		};
		struct
		{
			GLenum s, t, r;
		};
	};
};

class TextureCube
{
public:
	TextureCube() = default;
	TextureCube(const std::string &file);
	TextureCube(const std::vector<std::string> &file);
	bool load(const std::string &file, bool mipmap = true);
	bool load(const std::vector<std::string> &file, bool mipmap = true);
private:


	GLenum _Target;
	GLenum _InternalFormat;
	GLuint _TexHandle;
	TextureFilter _Filter;
	TextureWrap _Wrap;	
	int sizeX;
	int sizeY;
	std::string filename;
	std::string filetype;
	int channels;

};