
#pragma once
#include "Engine/Texture.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Material.h"

class Object {
public:
	Object();
	Object(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, Material *tempmat);

	void LoadObject(Shader *tempshader);
	void setPosition(glm::vec3 newpos);
	void setPosition(glm::vec4 newpos);
	glm::vec3 getPositionV3();
	glm::vec4 getPositionV4();
	glm::mat4 getTransform();
	
	float getOrientation();

	bool getActive();
	void setActive(bool temp);
	void setOrientation(float angle);
	void setRotationX(float angle);
	void setRotationY(float angle);
	void setRotationZ(float angle);
	void setTransform(glm::mat4 temp);
private:
	Mesh *ObjectMesh;
	Texture *ObjectTexture;
	glm::mat4 Transform;
	Material *ObjectMat;
	float orientation = 0;
	bool active = true;

};