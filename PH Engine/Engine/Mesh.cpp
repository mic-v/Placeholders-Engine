
#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include "Math/math.h"

#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i) ((char *)0 + (i))

struct MeshFace
{
	MeshFace()
	{
		vertices[0] = 0;
		vertices[1] = 0;
		vertices[2] = 0;

		textures[0] = 0;
		textures[1] = 0;
		textures[2] = 0;

		normals[0] = 0;
		normals[1] = 0;
		normals[2] = 0;
	}

	MeshFace(
		unsigned v1, unsigned v2, unsigned v3,
		unsigned t1, unsigned t2, unsigned t3,
		unsigned n1, unsigned n2, unsigned n3)
	{
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;

		textures[0] = t1;
		textures[1] = t2;
		textures[2] = t3;

		normals[0] = n1;
		normals[1] = n2;
		normals[2] = n3;
	}

	unsigned vertices[3];
	unsigned textures[3];
	unsigned normals[3];
};

Mesh::Mesh()
{
	BUFFER_OFFSET(23);
}

Mesh::~Mesh()
{
}

bool Mesh::loadFromFile(const std::string & file)
{
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open the file" << std::endl;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//Unqieue data
	std::vector<vec3> vertexData;
	std::vector<vec2> textureData;
	std::vector<vec3> normalData;
	//index/face data
	std::vector<MeshFace> faceData;
	//OpenGL ready data
	std::vector<float> unpackedVertexData;
	std::vector<float> unpackedTextureData;
	std::vector<float> unpackedNormalData;

	while (!input.eof())
	{
		//input.getline(&inputString, CHAR_BUFFER_SIZE);
		//if (std::strstr(&inputString, != nullptr)
		//{

		//}
		input.getline(inputString, sizeof(inputString));
		if (std::strstr(inputString, "#") != nullptr)
		{
			//this line is aocmment
			continue;
		}
		else if (std::strstr(inputString, "l") != nullptr)
		{
			continue;
		}
		else if (std::strstr(inputString, "vn") != nullptr)
		{
			//this line is aocmment
			vec3 temp;
			std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "vn " <<  temp.x << "," << temp.y << "," << temp.z << std::endl;
			normalData.push_back(temp);
		}
		else if (std::strstr(inputString, "vt") != nullptr)
		{
			//this line is aocmment
			vec2 temp;
			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			//std::cout << "vt " << temp.x << "," << temp.y << std::endl;
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "v") != nullptr)
		{
			//this line is aocmment
			vec3 temp;
			//std::cout << "before " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "v " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			vertexData.push_back(temp);
		}
		else if (std::strstr(inputString, "f") != nullptr)
		{
			//this line is aocmment
			MeshFace temp;
			std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&temp.vertices[0], &temp.textures[0], &temp.normals[0],
				&temp.vertices[1], &temp.textures[1], &temp.normals[1],
				&temp.vertices[2], &temp.textures[2], &temp.normals[2]
			);
			//std::cout << "f " << temp.vertices[0] << "," << temp.textures[0] << "," << temp.normals[0] << "  "
			//				<< temp.vertices[1] << "," << temp.textures[1] << "," << temp.normals[1] << "  "
			//				<< temp.vertices[2] << "," << temp.textures[2] << "," << temp.normals[2] << std::endl;

			faceData.push_back(temp);
		}
	}
	input.close();

	for (unsigned i = 0; i < faceData.size(); i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{
			//std::cout << i << std::endl;
			//std::cout << j << std::endl;
			//std::cout << faceData[i].vertices[j] - 1 << std::endl;
			//std::cout << vertexData[faceData[i].vertices[j] - 1] << std::endl;
			//std::cout << i << std::endl;
			//std::cout << j << std::endl;
			//std::cout << faceData[i].vertices[j] - 1 << std::endl;
			//std::cout << normalData[faceData[i].normals[j] - 1] << std::endl;
			std::cout << i << std::endl;
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

			unpackedTextureData.push_back(textureData[faceData[i].textures[j] - 1].x);
			unpackedTextureData.push_back(textureData[faceData[i].textures[j] - 1].y);

			unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].x);
			unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].y);
			unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].z);
		}
	}

	_numFaces = faceData.size();
	_numVertices = _numFaces * 3;

	//send data to opengl
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Verticies);
	glGenBuffers(1, &VBO_UVS);
	glGenBuffers(1, &VBO_Normals);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); //Vertex
	glEnableVertexAttribArray(1); // UVS
	glEnableVertexAttribArray(2); // NORMALS

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Verticies);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedVertexData.size(), &unpackedVertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedNormalData.size(), &unpackedNormalData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vertexData.clear();
	textureData.clear();
	normalData.clear();
	faceData.clear();
	unpackedVertexData.clear();
	unpackedTextureData.clear();
	unpackedNormalData.clear();

	return true;
}

void Mesh::unload()
{
	glDeleteBuffers(1, &VBO_Verticies);
	glDeleteBuffers(1, &VBO_UVS);
	glDeleteBuffers(1, &VBO_Normals);
	glDeleteVertexArrays(1, &VAO);

	VBO_Normals = 0;
	VBO_UVS = 0;
	VBO_Verticies = 0;
	VAO = 0;

	_numFaces = 0;
	_numVertices = 0;
}

unsigned int Mesh::getNumFaces() const
{
	return _numFaces;
}

unsigned int Mesh::getNumVertices() const
{
	return _numVertices;
}
