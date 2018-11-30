#pragma once

#include <string>
#include <vector>
#include "math.h"
#include "../../../External/glad/include/glad/glad.h"
//
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool loadFromFile(const char *file);
	bool loadSecondFromFile(const char *file);

	void unload();

	unsigned int getNumFaces() const;
	unsigned int getNumVertices() const;	

	unsigned int VBO_Verticies = 0;
	unsigned int VBO_UVS = 0;	
	unsigned int VBO_Normals = 0;

	unsigned int VBO_Verticies2 = 0;
	unsigned int VBO_UVS2 = 0;
	unsigned int VBO_Normals2 = 0;
	unsigned int VAO = 0;
	float lerpParameter = 0.0f;
private:
	unsigned int _numFaces = 0;
	unsigned int _numVertices = 0;

};