
#pragma once
#include "Engine/Texture.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include <GLFW/glfw3.h>

class Object {
public:
	Object();
	Object(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans);

	void LoadObject(Shader *tempshader);
	void setPosition(glm::vec3 newpos);
	void setPosition(glm::vec4 newpos);
	glm::vec3 getPositionV3();
	glm::vec4 getPositionV4();
private:
	Mesh *ObjectMesh;
	Texture *ObjectTexture;
	glm::mat4 Transform;


};