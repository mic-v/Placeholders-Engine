#include "Transform.h"

Transform::Transform()
	: m_pScale(1.0f),
	color(1.0f)
{
}

Transform::~Transform() {}

void Transform::setPosition(glm::vec3 newPosition)
{
	m_pLocalPosition = newPosition;
}
void Transform::setPositionX(float pos)
{
	m_pLocalPosition.x = pos;
}
void Transform::setPositionY(float pos)
{
	m_pLocalPosition.y = pos;
}
void Transform::setPositionZ(float pos)
{
	m_pLocalPosition.z = pos;
}

void Transform::setRotationX(float newAngle)
{
	m_pRotX = newAngle;
}

void Transform::setRotationY(float newAngle)
{
	m_pRotY = newAngle;
}

void Transform::setRotationZ(float newAngle)
{
	m_pRotZ = newAngle;
}

void Transform::setScale(float newScale)
{
	m_pScale = glm::vec3(newScale, newScale, newScale);
}

void Transform::setScale(glm::vec3 newScale)
{
	m_pScale = newScale;
}

glm::vec3 Transform::getPosition()
{
	return m_pLocalPosition;
}

float Transform::getPositionX()
{
	return m_pLocalPosition.x;
}

float Transform::getPositionY()
{
	return m_pLocalPosition.y;
}

float Transform::getPositionZ()
{
	return m_pLocalPosition.z;
}

float Transform::getRotationX()
{
	return m_pRotX;
}

float Transform::getRotationY()
{
	return m_pRotY;
}

float Transform::getRotationZ()
{
	return m_pRotZ;
}

void Transform::update(float dt)
{
	// Create 4x4 transformation matrix

	// Create rotation matrix

	glm::mat4 rx; 
	glm::mat4 ry; 
	glm::mat4 rz; 

	//glm::rotateX(glm::vec4(rx[5], rx[6], rx[9], rx[10]), m_pRotX);
	//glm::rotateY(glm::vec4(ry[0], ry[2], ry[8], ry[10]), m_pRotY);
	//glm::rotateZ(glm::vec4(rz[0], rz[1], rz[4], rz[5]), m_pRotZ);
	rx = glm::rotate(rx, glm::radians(m_pRotX), glm::vec3(1,0,0));
	ry = glm::rotate(ry, glm::radians(m_pRotY), glm::vec3(0, 1, 0));
	rz = glm::rotate(rz, glm::radians(m_pRotZ), glm::vec3(0, 0, 1));

	// Note: pay attention to rotation order, ZYX is not the same as XYZ
	m_pLocalRotation = rz * ry * rx;

	// Create translation matrix
	glm::mat4 tran;
	tran = glm::translate(m_pLocalPosition);

	// Create scale matrix
	glm::mat4 scale; 
	scale = glm::scale((m_pScale));

	// Combine all above transforms into a single matrix
	// This is the local transformation matrix, ie. where is this game object relative to it's parent
	// If a game object has no parent (it is a root node) then its local transform is also it's global transform
	// If a game object has a parent, then we must apply the parent's transform
	m_pLocalToWorldMatrix = tran * m_pLocalRotation * scale;
}

void Transform::update()
{
	// Create 4x4 transformation matrix

	// Create rotation matrix

	glm::mat4 rx;
	glm::mat4 ry;
	glm::mat4 rz;

	//glm::rotateX(glm::vec4(rx[5], rx[6], rx[9], rx[10]), m_pRotX);
	//glm::rotateY(glm::vec4(ry[0], ry[2], ry[8], ry[10]), m_pRotY);
	//glm::rotateZ(glm::vec4(rz[0], rz[1], rz[4], rz[5]), m_pRotZ);
	rx = glm::rotate(rx, glm::radians(m_pRotX), glm::vec3(1, 0, 0));
	ry = glm::rotate(ry, glm::radians(m_pRotY), glm::vec3(0, 1, 0));
	rz = glm::rotate(rz, glm::radians(m_pRotZ), glm::vec3(0, 0, 1));

	// Note: pay attention to rotation order, ZYX is not the same as XYZ
	m_pLocalRotation = rz * ry * rx;

	// Create translation matrix
	glm::mat4 tran;
	tran = glm::translate(m_pLocalPosition);

	// Create scale matrix
	glm::mat4 scale;
	scale = glm::scale((m_pScale));

	// Combine all above transforms into a single matrix
	// This is the local transformation matrix, ie. where is this game object relative to it's parent
	// If a game object has no parent (it is a root node) then its local transform is also it's global transform
	// If a game object has a parent, then we must apply the parent's transform
	m_pLocalToWorldMatrix = tran * m_pLocalRotation * scale;
}