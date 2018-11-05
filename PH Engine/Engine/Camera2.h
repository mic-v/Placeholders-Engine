#pragma once

#include <glad\glad.h>
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
	vec3 _position; 
	// Matrix
	vec3 _front; vec3 _up; vec3 _right;
	void updateCameraView();
	
public:
	Camera(vec3 position = vec3(0.f,0.f,0.f),
		vec3 right =	   vec3(1.0f,0.0f,0.0f),
		vec3 up =		   vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.f,
		float pitch = 0.0f)
	: _position(position),_front(vec3(0.0f, 0.0f, -1.0f)),_right(right), _up(up), _dragSpeed(30.5f), _yaw(yaw), _pitch(pitch) {}
	
	virtual void processKeyboard(Camera_Movement direction, float deltaTime);
	virtual void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	virtual void update();
	void setYDirection(float y);
	void moveUp();
	void moveDown();
	mat4 getLookMatrix();
private:
	float _dragSpeed;
	
	

};
