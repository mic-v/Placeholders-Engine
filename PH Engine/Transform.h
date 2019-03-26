#pragma once

#include <string>
#include "Engine/Math/math.h"

class Transform
{
public:
	glm::vec3 m_pScale = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_pRotX = 0.0f;
	float m_pRotY = 0.0f;
	float m_pRotZ = 0.0f; // local rotation angles

	glm::vec3 m_pLocalPosition;

	// TODO: Compute these matrices in the Update function
	glm::mat4 m_pLocalRotation;
	glm::mat4 m_pLocalToWorldMatrix;

	Transform();
	~Transform();

	void setPosition(glm::vec3 newPosition);
	void setPositionX(float pos);
	void setPositionY(float pos);
	void setPositionZ(float pos);
	glm::vec3 getPosition();
	float getPositionX();
	float getPositionY();
	float getPositionZ();

	void setRotationX(float newAngle);
	void setRotationY(float newAngle);
	void setRotationZ(float newAngle);
	float getRotationX();
	float getRotationY();
	float getRotationZ();

	void setScale(float newScale);
	void setScale(glm::vec3 newScale);


	virtual void update(float dt);
	virtual void update();
	
	// Other Properties
	std::string name;
	glm::vec4 color; 
};