#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
#include <fstream>
#include <iostream>

#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i) ((char *)0 + (i))

Material::Material()
{
}

Material::~Material()
{
}

bool Material::loadFile(const char * file)
{
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open the file" << std::endl;
	}

	char inputString[CHAR_BUFFER_SIZE];

	while (!input.eof())
	{
		input.getline(inputString, sizeof(inputString));
		if (std::strstr(inputString, "#") != nullptr)
		{
			continue;
		
		}

		else if (std::strstr(inputString, "# Material Count: ") != nullptr)
		{
			int temp;
			std::sscanf(inputString, "# Material Count: %f", &temp);
			count = temp;

		}

		else if (std::strstr(inputString, "Ns") != nullptr)
		{
			float temp;
			std::sscanf(inputString, "Ns %f", &temp);
			_matSpecularExponent = temp;
		}

		else if (std::strstr(inputString, "Ka") != nullptr)
		{
			glm::vec3 temp;
			std::sscanf(inputString, "Ka %f %f %f", &temp.x, &temp.y, &temp.z);
			_matAmbient = temp;

		}
		else if (std::strstr(inputString, "Kd") != nullptr)
		{
			glm::vec3 temp;
			std::sscanf(inputString, "Kd %f %f %f", &temp.x, &temp.y, &temp.z);
			_matDiffuse = temp;


		}

		else if (std::strstr(inputString, "Ks") != nullptr)
		{
			glm::vec3 temp;
			std::sscanf(inputString, "Ks %f %f %f", &temp.x, &temp.y, &temp.z);
			_matSpecular = temp;


		}
		else if (std::strstr(inputString, "illum") != nullptr)
		{
			int temp;
			std::sscanf(inputString, "illum %f", &temp);
			illum = temp;

		}

		//illum 2

	}
	input.close();
	return true;
}

glm::vec3 Material::getSpecular() const
{
	return _matSpecular;
}

glm::vec3 Material::getDiffuse() const
{
	return _matDiffuse;
}

glm::vec3 Material::getAmbient() const
{
	return _matAmbient;
}

int Material::getSpecularExponent() const
{
	return _matSpecularExponent;
}
