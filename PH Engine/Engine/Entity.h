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
	Entity(Shader shader, std::string &meshloc, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
	~Entity();

	Shader& getShader();
	Mesh& getMesh();

	virtual void update(float dt);
	virtual void draw();
	glm::vec3 getPosition() const;
private:
	glm::vec3 _position;
	Shader* _shader;
	Mesh* _mesh;
	
};