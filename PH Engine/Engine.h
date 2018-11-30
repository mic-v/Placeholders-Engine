#pragma once

// GAME.H
// DOn't do stuff in main
// This will be the main hub . This should really be called the core
// Any major systems that need to interact with one another will occur here.

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
//#include "imgui_impl_opengl3.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Window.h"
#include "Engine/Texture.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include "Engine/Math/math.h"
#include "Engine/Camera.h"
#include "Engine/Light.h"
#include "Engine/FPSCamera.h"
#include "Engine/Entity.h"
#include "Engine/InputModule.h"
#include "Engine/DebugDraw.h"
#include <vector>

#include <btBulletDynamicsCommon.h>

//#include "SOIL2.h"
//
using namespace plaho;
using namespace graphics;
using namespace module;
class Engine
{
public:
	~Engine() {}
	static Engine& instance();

	bool startUp();
	void shutDown();
	void runGame();
	void render();
	void playerInput();
	void runAnimation(std::vector<Mesh*> poselist);
	
	bool isActive;
private:
	Engine() {}

	/***/
	static Engine* _instance;
	GLFWwindow* _window;

	//Physics World
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	DebugDraw _draw;

	bool animation1run = false;
	int currentanimframe = 0;
	float currentlerpparam = 0;
	Camera *_camera;
	Camera camera2;
	FPSCamera camera1;
	Mesh object;
	Mesh object2;
	Mesh basemap;
	Mesh river;
	Mesh attackframe1;
	Mesh attackframe2;
	Mesh attackframe3;
	Mesh attackframe4;
	Mesh attackframe5;
	Mesh attackframe6;
	Mesh attackframe7;
	Mesh attackframe8;
	Mesh attackframe9;
	Mesh * Pose;
	std::vector<Entity*> obj;
	std::vector<Mesh*> animation1;
	Shader sh;
	Shader sh2;
	Shader sh3;
	Light first;
	Light second;
	Light third;
	Texture test;
	Texture test2;
	Texture test3;
	glm::mat4 objectTransform;
	glm::mat4 transform;
	glm::mat4 cameraProjection;
	glm::vec3 position;
	
	static float hp1;
	static float hp2;
	static float timer;
	static int win1;
	static int win2;

	// Don't know what to include yet
};