#pragma once
#include <string>
#include <vector>
#include "math.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
class Material
{
public:
	Material();
	~Material();

	bool loadFile(const char* file);
	glm::vec3 getSpecular() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getAmbient() const;
	int getSpecularExponent() const;

private:
	int _matSpecularExponent;
	float test;
	int count;
	int illum;
	std::string matName;
	glm::vec3 _matSpecular;
	glm::vec3 _matDiffuse;
	glm::vec3 _matAmbient;
	std::vector<std::vector<glm::vec3>> matStorage;

};