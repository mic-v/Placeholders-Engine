
#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include <fstream>
#include <iostream>


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
	//BUFFER_OFFSET(23);
}

Mesh::~Mesh()
{
}

bool Mesh::loadFromFile(const char * file)
{
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open the file" << std::endl;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//Unqieue data
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> textureData;
	std::vector<glm::vec3> normalData;
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
			glm::vec3 temp;
			std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "vn " <<  temp.x << "," << temp.y << "," << temp.z << std::endl;
			normalData.push_back(temp);
		}
		else if (std::strstr(inputString, "vt") != nullptr)
		{
			//this line is aocmment
			glm::vec2 temp;
			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			//std::cout << "vt " << temp.x << "," << temp.y << std::endl;
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "v") != nullptr)
		{
			//this line is aocmment
			glm::vec3 temp;
			//std::cout << "before " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "v " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			vertexData.push_back(temp);
		}
		else if (std::strstr(inputString, "f") != nullptr)
		{
			//this line contains face data
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
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

			//std::cout << textureData.size() << std::endl;
			//std::cout << faceData.size() << std::endl;
			//std::cout << i << std::endl;
			//std::cout << j << std::endl;
			//std::cout << textureData[faceData[i].textures[j] - 1].x << std::endl;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedVertexData.size(), &unpackedVertexData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedNormalData.size(), &unpackedNormalData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*std::cout << "N: " << unpackedNormalData.size() << std::endl;
	std::cout << "V: "<<unpackedVertexData.size() << std::endl;*/
	vertexData.clear();
	textureData.clear();
	normalData.clear();
	faceData.clear();
	unpackedVertexData.clear();
	unpackedTextureData.clear();
	unpackedNormalData.clear();

	return true;
}



bool Mesh::loadSecondFromFile(const char * file)
{
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open the file" << std::endl;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//Unqieue data
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> textureData;
	std::vector<glm::vec3> normalData;
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
			glm::vec3 temp;
			std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "vn " <<  temp.x << "," << temp.y << "," << temp.z << std::endl;
			normalData.push_back(temp);
		}
		else if (std::strstr(inputString, "vt") != nullptr)
		{
			//this line is aocmment
			glm::vec2 temp;
			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			//std::cout << "vt " << temp.x << "," << temp.y << std::endl;
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "v") != nullptr)
		{
			//this line is aocmment
			glm::vec3 temp;
			//std::cout << "before " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			//std::cout << "v " << temp.x << "," << temp.y << "," << temp.z << std::endl;
			vertexData.push_back(temp);
		}
		else if (std::strstr(inputString, "f") != nullptr)
		{
			//this line contains face data
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
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
			unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

			//std::cout << textureData.size() << std::endl;
			//std::cout << faceData.size() << std::endl;
			//std::cout << i << std::endl;
			//std::cout << j << std::endl;
			//std::cout << textureData[faceData[i].textures[j] - 1].x << std::endl;

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
	//glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Verticies2);
	glGenBuffers(1, &VBO_UVS2);
	glGenBuffers(1, &VBO_Normals2);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(4); //Vertex
	glEnableVertexAttribArray(5); // UVS
	glEnableVertexAttribArray(6); // NORMALS

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Verticies2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedVertexData.size(), &unpackedVertexData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedNormalData.size(), &unpackedNormalData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

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




bool Mesh::loadFromVector(const char *file, const SA::sAnimatedMesh& temp)
{
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open texture file for Animated Mesh" << std::endl;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//Unqieue data
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> textureData;
	std::vector<glm::vec3> normalData;
	std::vector<MeshFace> faceData;
	//OpenGL ready data
	std::vector<float> unpackedTextureData;

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
		else if (std::strstr(inputString, "vt") != nullptr)
		{
			//this line is aocmment
			glm::vec2 temp;
			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			//std::cout << "vt " << temp.x << "," << temp.y << std::endl;
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "f") != nullptr)
		{
			//this line contains face data
			MeshFace temp;

			/*std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&temp.vertices[0], &temp.textures[0], &temp.normals[0],
				&temp.vertices[1], &temp.textures[1], &temp.normals[1],
				&temp.vertices[2], &temp.textures[2], &temp.normals[2]
			);*/

			//faceData.push_back(temp);
		}
	}
	input.close();

	/*for (unsigned i = 0; i < faceData.size(); i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{

			unpackedTextureData.push_back(textureData[faceData[i].textures[j] - 1].x);
			unpackedTextureData.push_back(textureData[faceData[i].textures[j] - 1].y);


		}
	}*/

	for (unsigned int i = 0; i < temp.NumIndices; ++i)
	{
		unsigned int Index = temp.pIndices[i];
		glm::vec3 n = temp.pNormals[Index];
		glm::vec3 v = temp.pVertices[Index];
		glm::vec3 newn = glm::vec3(-n.x, n.z, -n.y);
		glm::vec3 newv = glm::vec3(-v.x, v.z, -v.y);
		//std::cout << "xv: "<<newv.x << "yv: " << newv.y <<"zv: " << newv.z << std::endl;
		//std::cout << "xn: " << newn.x << "yn: " << newn.y << "zn: " << newn.z << std::endl;
		normalData.push_back(newn);
		vertexData.push_back(newv);
		//temp.
	}
	std::cout <<"n: " <<normalData.size() << std::endl;
	std::cout << "v: "<<vertexData.size() << std::endl;
	//std::cout << "numofverts: " << temp.NumVertices << std::endl;
	//std::cout << "numofind: " << temp.NumIndices << std::endl;
	//glm::vec3 *parray = &(temp.pNormals[0]);

	//std::cout << sizeof(parray) << std::endl;
	_numFaces = vertexData.size();
	_numVertices = vertexData.size() * 3;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size()*3, &vertexData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size()*3, &normalData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	textureData.clear();
	normalData.clear();
	vertexData.clear();

	faceData.clear();

	unpackedTextureData.clear();

	return true;
}

bool Mesh::loadFromAnimatedModel(const char *file, const  SA::SkeletalModel& animodel)
{

	//glDeleteBuffers(1, &VBO_Verticies);
	//glDeleteBuffers(1, &VBO_UVS);
	//glDeleteBuffers(1, &VBO_Normals);
	//glDeleteVertexArrays(1, &VAO);

	char inputString[CHAR_BUFFER_SIZE];

	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec3> normalData;
	std::vector<glm::vec4> vertexBoneData;
	std::vector<glm::vec4> BoneWeightData;

	 const SA::sAnimatedMesh& temp = animodel.GetMesh(0);
	for (unsigned int i = 0; i < temp.NumIndices; ++i)
	{
		unsigned int Index = temp.pIndices[i];
		glm::vec3 n = temp.pNormals[Index];
		glm::vec3 v = temp.pVertices[Index];
		glm::vec4 vertbones = animodel.vertbonedata[Index];
		glm::vec4 boneweights = animodel.weightdata[Index];


		glm::vec3 newn = glm::vec3(n.x, n.y, n.z);
		glm::vec3 newv = glm::vec3(v.x, v.y, v.z);
		//std::cout << "xv: "<< vertbones.x << "yv: " << vertbones.y <<"zv: " << vertbones.z << std::endl;
		//std::cout << "xv: " << newv.x << "yv: " << newv.y << "zv: " << newv.z << std::endl;
		//std::cout << "xb: " << boneweights.x << "yb: " << boneweights.y << "zb: " << boneweights.z << std::endl;
		normalData.push_back(newn);
		vertexData.push_back(newv);
		vertexBoneData.push_back(vertbones);
		BoneWeightData.push_back(boneweights);
		//temp.
	}
	std::cout << "n: " << vertexBoneData.size() << std::endl;
	std::cout << "v vec: " << BoneWeightData.size() << std::endl;
	std::cout << "v: " << vertexData.size() << std::endl;
	//std::cout << "numofverts: " << temp.NumVertices << std::endl;
	//std::cout << "numofind: " << temp.NumIndices << std::endl;
	//glm::vec3 *parray = &(temp.pNormals[0]);

	_numFaces = vertexData.size();
	_numVertices = vertexData.size() * 3;
	_numVertBones = vertexBoneData.size();
	_numBoneWeights = BoneWeightData.size();


	//send data to opengl
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Verticies);

	glGenBuffers(1, &VBO_Normals);
	glGenBuffers(1, &VBO_VERTEXBONEDATA);
	glGenBuffers(1, &VBO_BONEWEIGHTDATA);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); //Vertex
	glEnableVertexAttribArray(2); // NORMALS
	glEnableVertexAttribArray(3); //BONES AFFECTING VERT
	glEnableVertexAttribArray(4); //WEIGHT OF BONES

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Verticies);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size() * 3, &vertexData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size() * 3, &normalData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	
	//FOR MESH SKINNING
	glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEXBONEDATA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBoneData.size() * 4, &vertexBoneData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_BONEWEIGHTDATA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BoneWeightData.size() * 4, &BoneWeightData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	return true;
}

//glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size() * 3, &normalData[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
//
//
////FOR MESH SKINNING
//glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEXBONEDATA);
//glBufferData(GL_ARRAY_BUFFER, sizeof(int) * vertexBoneData.size() * 4, &vertexBoneData[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(3, 4, GL_INT, GL_FALSE, sizeof(int) * 4, BUFFER_OFFSET(0));
//
//glBindBuffer(GL_ARRAY_BUFFER, VBO_BONEWEIGHTDATA);
//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BoneWeightData.size() * 4, &BoneWeightData[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, BUFFER_OFFSET(0));

bool Mesh::loadFromAnimatedModel2(const char *file, const  SA::SkeletalModel& animatedmodel)
{

	glDeleteBuffers(1, &VBO_Verticies);
	glDeleteBuffers(1, &VBO_UVS);
	glDeleteBuffers(1, &VBO_Normals);
	glDeleteVertexArrays(1, &VAO);

	char inputString[CHAR_BUFFER_SIZE];

	std::vector<glm::vec3> vertexData;

	std::vector<glm::vec3> normalData;

	const SA::sAnimatedMesh& temp = animatedmodel.GetMesh(0);
	for (unsigned int i = 0; i < temp.NumIndices; ++i)
	{
		unsigned int Index = temp.pIndices[i];
		glm::vec3 n = temp.pTransformedNormals[Index];
		glm::vec3 v = temp.pTransformedVertices[Index];
		glm::vec3 newn = glm::vec3(n.x, n.y, n.z);
		glm::vec3 newv = glm::vec3(v.x, v.y, v.z);
		//std::cout << "xv: "<<newv.x << "yv: " << newv.y <<"zv: " << newv.z << std::endl;
		//std::cout << "xn: " << newn.x << "yn: " << newn.y << "zn: " << newn.z << std::endl;
		normalData.push_back(newn);
		vertexData.push_back(newv);
		//temp.
	}
	std::cout << "n: " << normalData.size() << std::endl;
	std::cout << "v vec: " << temp.NumVertices << std::endl;
	std::cout << "v: " << vertexData.size() << std::endl;
	//std::cout << "numofverts: " << temp.NumVertices << std::endl;
	//std::cout << "numofind: " << temp.NumIndices << std::endl;
	//glm::vec3 *parray = &(temp.pNormals[0]);

	_numFaces = vertexData.size();
	_numVertices = vertexData.size() * 3;


	//send data to opengl
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Verticies);

	glGenBuffers(1, &VBO_Normals);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); //Vertex

	glEnableVertexAttribArray(2); // NORMALS

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Verticies);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size() * 3, &vertexData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size() * 3, &normalData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




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
