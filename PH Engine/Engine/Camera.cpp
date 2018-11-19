#include "Camera.h"
#include <iostream>

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	//float velocity = _dragSpeed * deltaTime;
	//if (direction == FORWARD)
	//	_pitch += velocity;
	//if (direction == BACKWARD)
	//	_pitch -= velocity;
	//if (direction == LEFT)
	//	_yaw -= velocity;
	//if (direction == RIGHT)
	//	_yaw += velocity;

	//if (_pitch > 89.f)
	//	_pitch = 89.f;
	//if (_pitch < -89.f)
	//	_pitch = -89.f;

	//updateCameraView();
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
}

void Camera::updateCameraView()
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(front);

	_right = glm::normalize(glm::cross(_front, _up));
	_up = glm::normalize(glm::cross(_right, _front));
}

void Camera::update()
{
	this->updateCameraView();
}

void Camera::setYDirection(float y)
{
	_pitch = y;
}

void Camera::moveUp()
{
	_position += glm::vec3(0.0, 0.01f, 0.0f);
}

void Camera::moveDown()
{
	_position -= glm::vec3(0.0, 0.01f, 0.0f);
}

glm::mat4 Camera::getLookMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}
