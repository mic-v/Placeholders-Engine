#include "Object.h"
#include <iostream>


Object::Object()
{
}

Object::Object(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans)
{
	ObjectMesh = tempmesh;
	ObjectTexture = temptext;
	Transform = temptrans;

	
}

void Object::LoadObject(Shader *tempshader)
{
	ObjectTexture->Bind(0);
	glBindVertexArray(ObjectMesh->VAO);
	tempshader->sendUniformMat4("model", Transform);
	glDrawArrays(GL_TRIANGLES, 0, ObjectMesh->getNumVertices());
	ObjectTexture->Unbind();
	glBindVertexArray(0);
}

void Object::setPosition(glm::vec3 newpos)
{
	this->Transform[3] = glm::vec4(newpos, 1.0f);
}
void Object::setPosition(glm::vec4 newpos)
{
	this->Transform[3] = newpos;
	
}

glm::vec3 Object::getPositionV3()
{

	return glm::vec3(Transform[3].x, Transform[3].y, Transform[3].z);
}
glm::vec4 Object::getPositionV4()
{

	return glm::vec4(Transform[3].x, Transform[3].y, Transform[3].z, Transform[3].w);
}
	/*std::cout << Transform[0].x << " " << Transform[1].x << " " << Transform[2].x << " " << Transform[3].x  << std::endl;
	std::cout << Transform[0].y << " " << Transform[1].y << " " << Transform[2].y << " " << Transform[3].y << std::endl;
	std::cout << Transform[0].z << " " << Transform[1].z << " " << Transform[2].z << " " << Transform[3].z << std::endl;
	std::cout << Transform[0].w << " " << Transform[1].w << " " << Transform[2].w << " " << Transform[3].w << std::endl;*/

