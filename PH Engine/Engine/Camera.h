#ifndef CAMERA_H
#define CAMERA_H

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	//euler angles
	float yaw;
	float pitch;
	//camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	// Constructors
	// ------------
	Camera(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f), float yaw_ = YAW, float pitch_ = PITCH) 
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		position = position_;
		yaw = yaw_;
		pitch = pitch_;
		worldUp = up_;
		updateCameraVectors();
	}
	

	// Methods
	// -------
	glm::mat4 getLookMatrix()
	{
		return glm::lookAt(position, position + front, worldUp);
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
		glm::vec3 Front;
		Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front.y = sin(glm::radians(pitch));
		Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(Front);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};

#endif