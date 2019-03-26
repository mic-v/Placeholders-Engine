#include "Camera.h"

Camera::Camera()
{
	int number = rand() % 2;
	Camera((ProjectionType)number);
}

Camera::Camera(ProjectionType projType)
{
	if (projType == ProjectionType::Perspective)
		perspective(60.0f, 1.0f, 0.1f, 100.0f);
	else
		orthographic(-10, 10, -10, 10, -100, 100);
}

void Camera::perspective(float fovy, float aspect, float zNear, float zFar)
{
	//projectionType = ProjectionType::Perspective;
	glm::mat4 proj = glm::perspective(
		fovy, aspect,
		zNear, zFar);
	//projection = proj;
}

void Camera::orthographic(float left, float right, float top, float bottom, float zNear, float zFar)
{
	//projectionType = ProjectionType::Orthographic;
	glm::mat4 ortho = glm::ortho(
		left, right,
		top, bottom,
		zNear, zFar);
	//projection = ortho;
}

glm::mat4 Camera::getView() const
{
	return m_pLocalToWorldMatrix;
}

glm::mat4 Camera::getProjection() const
{
	return projection;
}

glm::vec3 Camera::getDirection() const
{
	glm::mat4 tempMat = m_pLocalToWorldMatrix;
	glm::vec3 temp;
	temp.x = tempMat[2].x;
	temp.y = tempMat[2].y;
	temp.z = tempMat[2].z;
	temp = glm::normalize(temp);

	return temp;
}

