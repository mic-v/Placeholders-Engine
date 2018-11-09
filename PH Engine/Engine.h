#pragma once

// GAME.H
// DOn't do stuff in main
// This will be the main hub . This should really be called the core
// Any major systems that need to interact with one another will occur here.


#include "Engine/Window.h"
#include "Engine/Texture.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include "Engine/Math/math.h"
#include "Engine/Camera.h"
#include "Engine/Light.h"
#include "Engine/FPSCamera.h"
#include "Engine/Entity.h"
#include <vector>

//#include "SOIL2.h"
//
using namespace plaho;
using namespace graphics;

class Engine
{
public:
	~Engine();
	static Engine& instance();

	void startUp();
	void shutDown();
	void update(float dt);
	void render();
	void cameraMovement();
	Window* _window;
	
	
	bool isActive;
private:
	Engine();

	/***/
	static Engine* _instance;
	Camera *_camera;
	
	Camera camera2;
	FPSCamera camera1;
	Mesh object;
	Mesh object2;
	std::vector<Entity*> obj;
	Shader sh;
	Shader sh2;
	Shader sh3;
	Light first;
	Light second;
	Light third;
	Texture test;
	glm::mat4 objectTransform;
	glm::mat4 transform;
	glm::mat4 cameraProjection;
	glm::vec3 position;
	

	// Don't know what to include yet
};