#include "Entity.h"

Entity::Entity(Shader * shader, const char * meshloc, glm::vec3 position)
{
	_position = glm::vec3();
	_position = position;
	_matrixPosition = glm::mat4(1.0f);
	_matrixPosition = glm::translate(_matrixPosition, _position);
	_matrixPosition = glm::scale(_matrixPosition, glm::vec3(0.25f, 0.25f, 0.25f));

	_shader = new Shader();
	_shader = &(*shader);
	_mesh =  Mesh();
	_mesh.loadFromFile(meshloc);
}

Entity::~Entity()
{

}

Shader & Entity::getShader()
{
	return *_shader;
}

Mesh & Entity::getMesh()
{
	return _mesh;
}

void Entity::update(float dt)
{

}

void Entity::draw()
{
	//_shader->use();

	glBindVertexArray(_mesh.VAO);
	_shader->sendUniformMat4("model", _matrixPosition);
	glDrawArrays(GL_TRIANGLES, 0, _mesh.getNumVertices());
}

glm::vec3 Entity::getPosition() const
{
	return _position;
}

glm::mat4 Entity::getMatrixPosition() const
{
	return _matrixPosition;
}

void Entity::translate(glm::vec3 position)
{
	_position += position;
	_matrixPosition = glm::translate(_matrixPosition, _position);
}

