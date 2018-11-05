#pragma once

//#include <GL/glew.h>
//#include <MiniMath/Core.h>
#include <glad/glad.h>
#include "Math/math.h"
#include <string>
#include <iostream>
#include <fstream>

#include <vector>

class Shaderclass {
public:
	Shaderclass();
	~Shaderclass();


	bool Load(const std::string &vertfile, const std::string &fragfile);
	void Unload();
	bool Loaded() const;
	bool Link();

	void Bind() const;
	void Unbind();
	void Addattrib(unsigned int index, const std::string &attributepointer);

	int getAttribLocation(const std::string &name);
	int getUniformLocation(const std::string &name);


	void sendUniform(const std::string &name, int integ);
	void sendUniform(const std::string &name, unsigned int usinteg);
	void sendUniform(const std::string &name, float scalar);
	void sendUniform(const std::string &name, vec2 &vector);
	void sendUniform(const std::string &name, vec3 &vector);
	void sendUniform(const std::string &name, vec4 &vector);
	void sendUniformMat3(const std::string &name, float *matrix, bool transpose);
	void sendUniformMat4(const std::string &name, const mat4& mat, bool transpose);
private:
	bool IsInit = false;
	GLuint _VertexShader = 0;
	GLuint _FragShader = 0;
	GLuint _Program = 0;

	std::string ReadFile(const std::string &file);
	bool CompileShader(GLuint shader);
	void OutputShaderLog(GLuint shader);
	void OutputProgramLog();

};