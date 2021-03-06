#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Math/math.h"

class Shader
{
public:
	Shader() {}
	Shader(const char* vertPath, const char* fragPath);
	~Shader() {}
	void load(const char* vertPath, const char* fragPath);
	void unload();
	std::string readFile(const char* path);
	void use();
	void unuse();

	int getAttribLocation(const std::string & location) const;
	int getUniformLocation(const std::string & location) const;

	void setAttribLocation(unsigned int index, const std::string &location);
	void sendUniformBool(const std::string &name, bool value) const;
	void sendUniformInt(const std::string &name, int value) const;
	void sendUniformFloat(const std::string &name, float value) const;
	void sendUniformVec2(const std::string &name, glm::vec2 &vec) const;
	void sendUniformVec3(const std::string & name, glm::vec3 &vec) const;
	void sendUniformVec4(const std::string & name, glm::vec4 &vec) const;
	void sendUniformMat4(const std::string & name, const glm::mat4& mat) const;

private:
	GLuint ID;
	GLuint vertex, fragment;
	//std::string vertexCode;
	//std::string fragmentCode;
	void checkCompile(unsigned int shader, std::string type);
};
