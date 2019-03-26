#include "Object.h"
#include <iostream>


Object::Object()
{
}

//initialize static members
vector<Object*> Object::InnerColliders;
vector<Object*> Object::OutterColliders;

Object::Object(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, Material* tempmat)
{
	ObjectMesh = tempmesh;
	ObjectTexture = temptext;
	ObjectMat = tempmat;
	Transform = temptrans;


}

void Object::LoadObject(Shader *tempshader)
{
	if (this->active) {
		ObjectTexture->Bind(0);
		glBindVertexArray(ObjectMesh->VAO);
		tempshader->sendUniformMat4("model", Transform);
		glDrawArrays(GL_TRIANGLES, 0, ObjectMesh->getNumVertices());
		ObjectTexture->Unbind();
		glBindVertexArray(0);
	}
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
glm::mat4 Object::getTransform()
{
	return Transform;
}
float Object::getOrientation()
{
	return orientation;
}

bool Object::getActive()
{
	return active;
}

void Object::setActive(bool temp)
{
	active = temp;
}

//This sets Y rotation by overriding the current angle to whatever is inputted. 
void Object::setOrientation(float angle)
{
	orientation = angle;
	if (orientation > 360) {
		int div = orientation / 360;
		orientation = orientation - (360 * div);
	}

	this->setTransform(glm::rotate(this->getTransform(), glm::radians(orientation), glm::vec3(0.0f, 1.0f, 0.0f)));
}
void Object::Rotate(float angle)
{
	this->setTransform(glm::rotate(this->getTransform(), glm::radians(-orientation), glm::vec3(0.0f, 1.0f, 0.0f)));
	orientation = angle;
	if (orientation > 360) {
		int div = orientation / 360;
		orientation = orientation - (360 * div);
	}

	this->setTransform(glm::rotate(this->getTransform(), glm::radians(orientation), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Object::setRotationX(float angle)
{



	Transform *= glm::rotate(angle, glm::vec3(1, 0, 0));
}

//This sets Y rotation by adding to it, not changing it completely.
void Object::setRotationY(float angle)
{

	this->setOrientation(orientation + angle);
}

void Object::setRotationZ(float angle)
{



	Transform *= glm::rotate(angle, glm::vec3(0, 0, 1));
}
void Object::setTransform(glm::mat4 temp)
{
	Transform = temp;
}
void Object::setRadius(float temp)
{
	Radius = temp;
}
float Object::getRadius()
{
	return Radius;
}
/*std::cout << Transform[0].x << " " << Transform[1].x << " " << Transform[2].x << " " << Transform[3].x  << std::endl;
std::cout << Transform[0].y << " " << Transform[1].y << " " << Transform[2].y << " " << Transform[3].y << std::endl;
std::cout << Transform[0].z << " " << Transform[1].z << " " << Transform[2].z << " " << Transform[3].z << std::endl;
std::cout << Transform[0].w << " " << Transform[1].w << " " << Transform[2].w << " " << Transform[3].w << std::endl;*/

bool Object::checkInnerCollision(Object* obj2) {

	glm::vec3 pos1 = this->getPositionV3();
	glm::vec3 pos2 = obj2->getPositionV3();

	float rad1 = this->getRadius();
	float rad2 = obj2->getRadius();

	float x = pos1.x - pos2.x;
	float z = pos1.z - pos2.z;

	if (sqrt((x*x) + (z*z)) <= sqrt((rad1 + rad2) * (rad1 + rad2))) {
		return false;
	}

	return true;
}
bool Object::checkOutterCollision(Object* obj2) {

	glm::vec3 pos1 = this->getPositionV3();
	glm::vec3 pos2 = obj2->getPositionV3();

	float rad1 = this->getRadius();
	float rad2 = obj2->getRadius();

	float x = pos1.x - pos2.x;
	float z = pos1.z - pos2.z;

	if (sqrt((x*x) + (z*z)) >= sqrt((rad1 + rad2) * (rad1 + rad2))) {
		return false;
	}

	return true;
}
bool Object::checkCollisions() {
	for (int i = 0; i < InnerColliders.size(); i++) {
		if (checkInnerCollision(InnerColliders[i])) {
			return true;
		}
	}
	for (int i = 0; i < OutterColliders.size(); i++) {
		if (checkOutterCollision(OutterColliders[i])) {
			return true;
		}
	}
	return false;
}