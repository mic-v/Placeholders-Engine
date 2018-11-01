#pragma once
#include <string>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "SOIL2.h"
#include <iostream>
using namespace std;


//
//
class Texture {
public:
	Texture();
	~Texture();
	bool LoadTexture(const char);
	void Unload();
	void Bind();
	void Unbind();
	GLuint Textobj = 0;
};