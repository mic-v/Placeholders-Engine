#include "CUBE.h"
#include <fstream>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#define CHAR_BUFFER_SIZE 128
bool CUBELoader::loadLUT(std::string file)
{
	ifstream LUTFile(file);
	if (LUTFile.fail()) {
		cout << "Cube file failed to load" << endl;
		return false;
	}
	while (!LUTFile.eof()) {
		string LUTline;
		getline(LUTFile, LUTline);

		if (LUTline.empty()) {
			continue;
		}
		if (sscanf_s(LUTline.c_str(), "LUT_3D_SIZE %i", &LUTsize)) {
			//cout << LUTsize << endl;
		}
		glm::vec3 line;
		if (sscanf_s(LUTline.c_str(), "%f %f %f", &line.x, &line.y, &line.z) == 3) {
			LUT.push_back(line);
		}
	}
	if (LUT.size() != (pow(LUTsize, 3.0))) {
		cout << "LUT size is incorrect." << endl;
		return false;
	}
	//loadTexture();
	return true;
	
}

void CUBELoader::loadTexture()
{
	glEnable(GL_TEXTURE_3D);
	_Target = GL_TEXTURE_3D;
	glGenTextures(1, &_TexHandle);
	glBindTexture(GL_TEXTURE_3D, _TexHandle);
	glTexParameteri(_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(_Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(_Target, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexImage3D(_Target, 0, GL_RGB, LUTsize, LUTsize, LUTsize, 0, GL_RGB, GL_FLOAT, &LUT[0]);
	glBindTexture(GL_TEXTURE_3D, 0);
	glDisable(GL_TEXTURE_3D);
}


int CUBELoader::getSize()
{
	return LUTsize;
}

void CUBELoader::setLerp(float temp)
{
	LerpAmount = temp;
}

float CUBELoader::getLerp()
{
	return LerpAmount;
}


