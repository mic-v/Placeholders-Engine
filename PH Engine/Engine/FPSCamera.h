//#pragma once
//
//#include "Camera.h"
//#include "Math/math.h"
//
//class FPSCamera : public Camera
//{
//public:
//
//	//
//	FPSCamera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
//		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f),
//		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
//			float yaw = -90.f,
//			float pitch = 0.0f) 
//	{
//		_position = position;
//		_front = glm::vec3(0.0f, 0.0f, -1.0f);
//		_up = up;
//		_right = glm::vec3(1.0f, 0.0f, 0.0f);
//		_mouseSensitivity = 0.1f;
//		_movementSpeed = 5.0f;
//		_yaw = yaw;
//		_pitch = pitch;
//	}
//
//
//	~FPSCamera() {}
//	void processKeyboard(Camera_Movement direction, float deltaTime) override;
//	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) override;
//	void update() override;
//private:
//	float _mouseSensitivity; float _movementSpeed;
//};