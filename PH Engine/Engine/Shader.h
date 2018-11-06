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
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, vec2 vec) const;
	void setVec3(const std::string & name, vec3 vec) const;
	void setVec4(const std::string & name, vec4 vec) const;
	void setMat4(const std::string & name, const mat4& mat) const;

private:
	GLuint ID;
	GLuint vertex, fragment;
	//std::string vertexCode;
	//std::string fragmentCode;
	void checkCompile(unsigned int shader, std::string type);
};
