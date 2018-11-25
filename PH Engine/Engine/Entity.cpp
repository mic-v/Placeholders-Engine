#include "Entity.h"

Entity::Entity(Shader shader, std::string& meshloc, glm::vec3 position)
{
	_shader = &shader;
	_mesh = new Mesh();
	_mesh->loadFromFile(meshloc);
	_position = position;
}

Entity::~Entity()
{
	delete _shader;
	delete _mesh;
}

Shader & Entity::getShader()
{
	return *_shader;
}

Mesh & Entity::getMesh()
{
	return *_mesh;
}

void Entity::update(float dt)
{
}

void Entity::draw()
{
}

glm::vec3 Entity::getPosition() const
{
	return _position;
}

