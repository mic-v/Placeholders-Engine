#pragma once

#include "Camera.h"
#include "Math/math.h"

class FPSCamera : public Camera
{
public:

	//
	FPSCamera(vec3 position = vec3(0.f, 0.f, 0.f),
			vec3 right = vec3(1.0f, 0.0f, 0.0f),
			vec3 up = vec3(0.0f, 1.0f, 0.0f),
			float yaw = -90.f,
			float pitch = 0.0f) 
	{
		_position = position;
		_front = vec3(0.0f, 0.0f, -1.0f);
		_up = up;
		_right = vec3(1.0f, 0.0f, 0.0f);
		_mouseSensitivity = 0.1f;
		_movementSpeed = 5.0f;
		_yaw = yaw;
		_pitch = pitch;
	}


	~FPSCamera() {}
	virtual void processKeyboard(Camera_Movement direction, float deltaTime) override;
	virtual void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) override;
private:
	float _mouseSensitivity; float _movementSpeed;
};