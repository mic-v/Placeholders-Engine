#include "Shader.h"

Shaderclass::Shaderclass() {

}
Shaderclass::~Shaderclass() {

}


bool Shaderclass::Load(const std::string &vertfile, const std::string &fragfile) {
	_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	_Program = glCreateProgram();

	std::string source = ReadFile(vertfile);
	const GLchar *temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(_VertexShader, 1, &temp, NULL);

	source = ReadFile(fragfile);
	temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(_FragShader, 1, &temp, NULL);

	if (!CompileShader(_VertexShader)) {
		std::cout << "Vertex shader file failed to compile" << std::endl;
		OutputShaderLog(_VertexShader);
		Unload();
		return false;
	}
	if (!CompileShader(_FragShader)) {
		std::cout << "Fragment shader file failed to compile" << std::endl;
		OutputShaderLog(_FragShader);
		Unload();
		return false;
	}
	glAttachShader(_Program, _VertexShader);
	glAttachShader(_Program, _FragShader);

	if (!Link()) {
		std::cout << "Program failed to link" << std::endl;

		OutputProgramLog();
		Unload();
		return false;
	}
	IsInit = true;
	return true;
}

void Shaderclass::Unload() {
	if (_VertexShader != 0) {
		glDetachShader(_Program, _VertexShader);
		glDeleteShader(_VertexShader);
		_VertexShader = 0;
	}
	if (_FragShader != 0) {
		glDetachShader(_Program, _FragShader);
		glDeleteShader(_FragShader);
		_FragShader = 0;
	}
	if (_Program != 0) {
		glDeleteProgram(_Program);
		_Program = 0;
	}
	IsInit = false;
}
bool Shaderclass::Loaded() const {
	return IsInit;
}

void Shaderclass::Bind() const {
	glUseProgram(_Program);
}
void Shaderclass::Unbind() {
	glUseProgram(0);
}

bool Shaderclass::Link() {
	glLinkProgram(_Program);
	GLint success;
	glGetProgramiv(_Program, GL_LINK_STATUS, &success);

	return success == GL_TRUE;
}
void Shaderclass::Addattrib(unsigned int index, const std::string &attributepointer) {
	glBindAttribLocation(_Program, index, attributepointer.c_str());
}

int Shaderclass::getAttribLocation(const std::string &name) {
	return glGetAttribLocation(_Program, name.c_str());
}
int Shaderclass::getUniformLocation(const std::string &name) {
	return glGetUniformLocation(_Program, name.c_str());
}


void Shaderclass::sendUniform(const std::string &name, int integ) {
	GLint location = getUniformLocation(name);
	glUniform1i(location, integ);
}
void Shaderclass::sendUniform(const std::string &name, unsigned int usinteg) {
	GLint location = getUniformLocation(name);
	glUniform1i(location, usinteg);
}
void Shaderclass::sendUniform(const std::string &name, float scalar) {
	GLint location = getUniformLocation(name);
	glUniform1f(location, scalar);
}
void Shaderclass::sendUniform(const std::string &name, vec2 &vector) {
	GLint location = getUniformLocation(name);
	glUniform2f(location, vector.x, vector.y);
}
void Shaderclass::sendUniform(const std::string &name, vec3 &vector) {
	GLint location = getUniformLocation(name);
	glUniform3f(location, vector.x, vector.y, vector.z);
}
void Shaderclass::sendUniform(const std::string &name, vec4 &vector) {
	GLint location = getUniformLocation(name);
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}
void Shaderclass::sendUniformMat3(const std::string &name, float *matrix, bool transpose) {
	GLint location = getUniformLocation(name);
	glUniformMatrix3fv(location, 1, transpose, matrix);
}
void Shaderclass::sendUniformMat4(const std::string &name, const mat4& mat, bool transpose) {
	GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, transpose, &mat.m[0][0]);
}








std::string Shaderclass::ReadFile(const std::string &file) {
	std::ifstream infile(file);

	if (!infile.good()) {
		std::cout << "Shader file not found" << std::endl;
		return std::string();
	}
	std::string data(std::istreambuf_iterator<char>(infile), (std::istreambuf_iterator<char>()));
	return data;
}
bool Shaderclass::CompileShader(GLuint shader) {
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success == GL_TRUE;
}
void Shaderclass::OutputShaderLog(GLuint shader) {
	std::vector<char> infoLog;
	infoLog.resize(512);
	GLint infolength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolength);
	glGetShaderInfoLog(shader, sizeof(char) * 512, &infolength, &infoLog[0]);

	std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;
}
void Shaderclass::OutputProgramLog() {
	std::vector<char> infoLog;
	infoLog.resize(512);
	GLint infolength;
	glGetProgramiv(_Program, GL_INFO_LOG_LENGTH, &infolength);
	glGetProgramInfoLog(_Program, sizeof(char) * 512, &infolength, &infoLog[0]);

	std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;
}