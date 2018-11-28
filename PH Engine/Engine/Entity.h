#pragma once

/*
	Entity Class

*/
#include <glad/glad.h>
#include "Math/math.h"

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include <string>


class Entity
{
public:
	Entity(Shader * shader, const char * meshloc, glm::vec3 position = glm::vec3(-4.0f, 0.0f, 0.0f));
	~Entity();

	Shader& getShader();
	Mesh& getMesh();

	virtual void update(float dt);
	virtual void draw();
	glm::vec3 getPosition() const;
	glm::mat4 getMatrixPosition() const;
	void translate(glm::vec3 position);
private:
	glm::vec3 _position;
	glm::mat4 _matrixPosition;
	Shader* _shader;
	Mesh _mesh;
	
};