//#include "FPSCamera.h"
//#include <iostream>
//void FPSCamera::processKeyboard(Camera_Movement direction, float deltaTime)
//{
//	float velocity = _movementSpeed * deltaTime;
//	if (direction == FORWARD)
//		_position += _front * velocity;
//	if (direction == BACKWARD)
//		_position -= _front * velocity;
//	if (direction == LEFT)
//		_position -= _right * velocity;
//	if (direction == RIGHT)
//		_position += _right * velocity;
//
//	//updateCameraView();
//}
//
//void FPSCamera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
//{
//	xoffset *= _mouseSensitivity;
//	yoffset *= _mouseSensitivity;
//
//	_yaw += xoffset;
//	_pitch += yoffset;
//
//	// Make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (constrainPitch)
//	{
//		if (_pitch > 89.0f)
//			_pitch = 89.0f;
//		if (_pitch < -89.0f)
//			_pitch = -89.0f;
//	}
//}
//
//void FPSCamera::update()
//{
//	this->updateCameraView();
//	std::cout << "yee" << std::endl;
//}
//
