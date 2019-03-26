#pragma once
#include "Transform.h"
#include "Engine/Math/math.h"

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Transform
{
public:
	Camera();
	Camera(ProjectionType projType);

	void perspective(
		float fovy, float aspect,
		float zNear, float zFar);

	void orthographic(
		float left, float right,
		float bottom, float top,
		float zNear, float zFar);

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
	glm::vec3 getDirection() const;
	glm::mat4 projection;

private:
	ProjectionType projectionType = ProjectionType::Perspective;

};