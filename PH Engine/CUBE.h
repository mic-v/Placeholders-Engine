#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include "IO.h"
#include "Engine/Texture.h"

class CUBELoader : public Texture {
public:

	bool loadLUT(std::string file);
	void loadTexture();
	int getSize();
	void setLerp(float temp);
	float getLerp();
private:
	
	GLuint texture3D = 0;
	std::vector<glm::vec3> LUT;
	int LUTsize;
	float LerpAmount = 0.5f;

};