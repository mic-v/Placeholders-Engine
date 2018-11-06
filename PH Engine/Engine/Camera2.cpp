#include "Camera2.h"
#include <iostream>
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = _dragSpeed * deltaTime;
	if (direction == FORWARD)
		_pitch += velocity;
	if (direction == BACKWARD)
		_pitch -= velocity;
	if (direction == LEFT)
		_yaw -= velocity;
	if (direction == RIGHT)
		_yaw += velocity;

	if (_pitch > 89.f)
		_pitch = 89.f;
	if (_pitch < -89.f)
		_pitch = -89.f;
	std::cout << _pitch << std::endl;

	//updateCameraView();
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
}

//void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//{
//	updateCameraView();
//}

void Camera::updateCameraView()
{
	vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = vec3::Normalize(front);

	_right = (vec3::CrossProduct2(_front, _up)).Normalize();
	_up = (vec3::CrossProduct2(_right, _front)).Normalize();
}

void Camera::update()
{
	this->updateCameraView();
}

mat4 Camera::getLookMatrix()
{
	return mat4::lookat(_position, _position + _front, _up);
}
