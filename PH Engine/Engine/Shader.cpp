#include "Shader.h"

Shader::Shader(const char * vertPath, const char * fragPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.open(vertPath);
	fShaderFile.open(fragPath);
	std::stringstream vShaderStream, fShaderStream;
	// read file's buffer contents into streams
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	// close file handlers
	vShaderFile.close();
	fShaderFile.close();
	// convert stream into string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompile(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompile(fragment, "FRAGMENT");
	// if geometry shader is given, compile geometry shader
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);

	glLinkProgram(ID);
	checkCompile(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::load(const char * vertPath, const char * fragPath)
{
}

void Shader::unload()
{
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::readFile(const char * path)
{

	return std::string();
}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::unuse()
{
	glUseProgram(0);
}

int Shader::getAttribLocation(const std::string & location) const
{
	return glGetAttribLocation(ID, location.c_str());
}

int Shader::getUniformLocation(const std::string & location) const
{
	return glGetUniformLocation(ID, location.c_str());
}

void Shader::setAttribLocation(unsigned int index, const std::string & location)
{
	glBindAttribLocation(ID, index, location.c_str());
}

void Shader::sendUniformBool(const std::string & name, bool value) const
{
	glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::sendUniformInt(const std::string & name, int value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::sendUniformFloat(const std::string & name, float value) const
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::sendUniformVec2(const std::string & name, glm::vec2 &vec) const
{
	glUniform2fv(getUniformLocation(name), 1,&vec[0]);
}

void Shader::sendUniformVec3(const std::string & name, glm::vec3 &vec) const
{
	glUniform3fv(getUniformLocation(name), 1, &vec[0]);
}

void Shader::sendUniformVec4(const std::string & name, glm::vec4 &vec) const
{
	glUniform4fv(getUniformLocation(name), 1, &vec[0]);
}

void Shader::sendUniformMat4(const std::string & name, const glm::mat4 & mat) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompile(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error:SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error: PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}
