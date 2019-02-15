#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "SOIL2.h"
#include <iostream>
#include <cassert>
using namespace std;


//
//
class Texture {
public:
	Texture();
	~Texture();
	bool LoadTexture(const std::string& filename);
	void Unload();
	void Bind(unsigned int unit);
	void Bind3D(int textureSlot) const;
	void unbind3D(int textureSlot) const;
	void Unbind();
	GLuint Textobj = 0;
	GLuint _TexHandle;
	GLenum _Target;

};