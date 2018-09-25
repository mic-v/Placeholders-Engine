#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include "mat4.h"

#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i) ((char *)0 + (i)))

Mesh::Mesh()
{
	//BUFFER_OFFSET(23);
}

Mesh::~Mesh()
{
}

bool Mesh::loadFromFile(const std::string & file)
{
	return false;
}

void Mesh::unload()
{
}

unsigned int Mesh::getNumFaces() const
{
	return 0;
}

unsigned int Mesh::getNumVertices() const
{
	return 0;
}
