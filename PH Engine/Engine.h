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


#include "Engine/Window.h"
#include "Player.h"
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
	void checkAnimation();
	bool runAnimation(std::vector<Mesh*> poselist, float);
	
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
	bool animation2run = false;
	bool animation3run = false;
	bool animation4run = false;
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

	Mesh idleframe1;
	Mesh idleframe2;
	Mesh idleframe3;
	Mesh idleframe4;
	Mesh idleframe5;
	Mesh idleframe6;
	Mesh idleframe7;

	Mesh attack2frame1;
	Mesh attack2frame2;
	Mesh attack2frame3;
	Mesh attack2frame4;
	Mesh attack2frame5;
	Mesh attack2frame6;
	Mesh attack2frame7;
	Mesh attack2frame8;
	Mesh attack2frame9;
	Mesh attack2frame10;
	Mesh attack2frame11;

	//run forward
	Mesh runframe1;
	Mesh runframe2;
	Mesh runframe3;
	Mesh runframe4;
	Mesh runframe5;
	Mesh runframe6;
	Mesh runframe7;
	Mesh runframe8;
	Mesh runframe9;
	Mesh runframe10;

	//run back
	Mesh runframe11;
	Mesh runframe12;
	Mesh runframe13;
	Mesh runframe14;
	Mesh runframe15;
	Mesh runframe16;
	Mesh runframe17;
	Mesh runframe18;
	


	Mesh * Pose;
	std::vector<Entity*> obj;
	//attack1 animation
	std::vector<Mesh*> animation1;
	//idleanimation
	std::vector<Mesh*> animationidle;
	//runforward animation
	std::vector<Mesh*> animation2;
	//run backward animation
	std::vector<Mesh*> animation3;
	//attack2 animation
	std::vector<Mesh*> animation4;
	Object Trees;
	Object BasePlate;
	Object River;
	Player Playerone;
	Player Playertwo;
	Shader sh2;
	Shader sht;
	Light first;
	Light second;
	Texture TreeTex;
	Texture BaseTex;
	Texture test3;
	glm::mat4 objectTransform;
	glm::mat4 Player1Transform;
	glm::mat4 cameraProjection;
	glm::vec3 position;
	
	static float hp1;
	static float hp2;
	static float timer;
	static int win1;
	static int win2;

	// Don't know what to include yet
};