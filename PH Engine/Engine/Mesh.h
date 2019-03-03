#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../Types.h"
#include "../SkeletalModel.h"
//
class Mesh
{
public:
	Mesh();
	~Mesh();
	bool loadFromFile(const char *file);
	bool loadFromVector(const char *file, const SA::sAnimatedMesh& temp);
	bool loadFromAnimatedModel(const char *file, const SA::SkeletalModel& temp);
	bool loadFromAnimatedModel2(const char *file, const SA::SkeletalModel& temp);
	bool loadSecondFromFile(const char *file);

	void unload();

	unsigned int getNumFaces() const;
	unsigned int getNumVertices() const;	

	unsigned int VBO_Verticies = 0;
	unsigned int VBO_UVS = 0;	
	unsigned int VBO_Normals = 0;
	unsigned int VBO_VERTEXBONEDATA = 0;
	unsigned int VBO_BONEWEIGHTDATA = 0;

	unsigned int VBO_Verticies2 = 0;
	unsigned int VBO_UVS2 = 0;
	unsigned int VBO_Normals2 = 0;



	unsigned int VAO = 0;
	float lerpParameter = 0.0f;
private:
	unsigned int _numFaces = 0;
	unsigned int _numVertices = 0;
	unsigned int _numVertBones = 0;
	unsigned int _numBoneWeights = 0;

};