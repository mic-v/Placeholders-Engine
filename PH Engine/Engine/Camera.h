#ifndef CAMERA_H
#define CAMERA_H

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Math/math.h"
#include <iostream>
#define _USE_MATH_DEFINES // for C++  
#include <cmath>  

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0F;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// Objects
	// -------
	//glm::vec3 position;
	//glm::vec3 front;
	//glm::vec3 up;
	//glm::vec3 right;
	//glm::vec3 worldUp;
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;
	//euler angles
	float yaw;
	float pitch;
	//camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	// Constructors
	// ------------
	//Camera(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f), float yaw_ = YAW, float pitch_ = PITCH) 
	//	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	//{
	//	position = position_;
	//	yaw = yaw_;
	//	pitch = pitch_;
	//	worldUp = up_;
	//	updateCameraVectors();
	//}
	//

	Camera(vec3 position_ = vec3(0.0f, 0.0f, 0.0f), vec3 up_ = vec3(0.0f, 1.0f, 0.0f), vec3 right_ = vec3(1.0f,0.0f,0.0f), float yaw_ = YAW, float pitch_ = PITCH)
		: front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		position = position_;
		yaw = yaw_;
		pitch = pitch_;
		worldUp = up_;
		right = right_;
		updateCameraVectors();
	}
	// Methods
	// -------
	mat44 getLookMatrix()
	{
		return mat44::lookAt(position, right, worldUp, position + front);
	}

	mat44 getLookMatrix2()
	{
		std::cout << position << std::endl;
		std::cout << front << std::endl;
		std::cout << position + front << std::endl;
		std::cout << "testing" << std::endl;
		return mat44::lookAt2(position, position + front, up);
	}

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;
		
		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch)
		{
			if (pitch > 89.f)
				pitch = 89.f;
			if (pitch < -89.f)
				pitch = -89.f;
		}
		updateCameraVectors();
	}

	void processKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= right * velocity;
		if (direction == RIGHT)
			position += right * velocity;
	}

	void processMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

private:
	void updateCameraVectors()
	{
		vec3 Front;
		//Front.x = cos((0.01745329251994329576923690768489f) * (yaw)) * cos((0.01745329251994329576923690768489f) * (pitch));
		//Front.y = sin((0.01745329251994329576923690768489f) * (pitch));
		//Front.z = sin((0.01745329251994329576923690768489f) * (yaw)) * cos((0.01745329251994329576923690768489f) * (pitch));
		//front = Front.Normalize();
		//Front.x = cos(yaw * (3.14159265358979323846 / 180.0f)) * cos(pitch *(3.14159265358979323846 / 180.0f));
		//Front.y = sin(pitch * (3.14159265358979323846 / 180.0f));
		//Front.z = sin( yaw * (3.14159265358979323846 / 180.0f)) * cos(pitch * (3.14159265358979323846 / 180.0f));
		Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front.y = sin(glm::radians(pitch));
		Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = vec3::Normalize(Front);
		std::cout << front << std::endl;

		right = (vec3::CrossProduct2(front, worldUp)).Normalize();
		up = (vec3::CrossProduct2(right, front)).Normalize();
		//right = glm::normalize(glm::cross(Front, worldUp));

	} 
};

#endif