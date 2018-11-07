#pragma once
#include <string>
#include <glad/glad.h>
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
	void Unbind();
	GLuint Textobj = 0;

};