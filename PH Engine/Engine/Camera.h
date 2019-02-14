#pragma once

#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Math/math.h"

/*
		  Stationery Camera
	       / 			\
	FPS(free rome)		MOBA camera

*/

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera
{
protected:
	float _pitch, _yaw;
	glm::vec3 _position;
	// Matrix
	glm::vec3 _front; glm::vec3 _up; glm::vec3 _right;
	void updateCameraView();
	
public:
	Camera(glm::vec3 position = glm::vec3(0.f,0.f,0.f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.f,
		float pitch = 0.0f)
	: _position(position),_front(glm::vec3(0.0f, 0.0f, -1.0f)), _up(up), _dragSpeed(30.5f), _yaw(yaw), _pitch(pitch) {}
	
	virtual void processKeyboard(Camera_Movement direction, float deltaTime);
	virtual void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	virtual void update();
	void setYDirection(float y);
	void moveUp();
	void moveDown();
	glm::mat4 getLookMatrix();
private:
	float _dragSpeed;
	
	

};
