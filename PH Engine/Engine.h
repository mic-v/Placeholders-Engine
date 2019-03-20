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
#include "CUBE.h" 
#include "Player.h"
#include "Engine/Math/math.h"
#include "Engine/Camera.h"
#include "Engine/Light.h"
#include "Engine/FPSCamera.h"

#include "Engine/InputModule.h"
#include "Engine/DebugDraw.h"
#include <vector>
#include "Material.h"
#include "FrameBuffer.h"
#include "Ability.h"
#include <btBulletDynamicsCommon.h>
#include "AssimpConverter.h"
#include "SkeletalModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
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
	void loadAssimpAnim(std::string filename, SA::SkeletalModel* tempskele);
	void runGame();
	void render();
	void playerInput(float t);
	void checkAnimation();
	bool runAnimation(std::vector<Mesh*> poselist, float);
	void controllerInput(float Dt, int controller, float speed, Player *player, const float*axes, const unsigned char* buttons, Player * otherplayer, SA::SkeletalModel * playersmod);
	
	

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
	float skillshotT = 0.0f;
	bool keyCheck = false;
	float currentlerpparam = 0;
	Camera *_camera;
	Camera camera2;
	FPSCamera camera1;
	Mesh Debris;
	Mesh object2;
	Mesh basemap;
	Mesh river;
	Mesh rockMesh;

	Mesh idleframe1;
	

	Mesh * Pose;
	
	
	Object Trees;
	Object BasePlate;
	Object River;
	Object rockObject;
	Object rockObject2;
	Player Playerone;
	Player Playertwo;
	Mesh testmesh;
	Mesh testmesh2;

	Ability tempability;
	Ability tempability2;
	Skillshot playoneskillshot;
	Skillshot playtwoskillshot;
	Shader animsh;
	Shader sh2;
	Shader sht;
	Shader LUTShader;
	Light first;
	Light second;
	Texture TreeTex;
	Texture BaseTex;
	Texture test3;
	Material testMat;
	Framebuffer frameBuffer;
	glm::mat4 objectTransform;
	glm::mat4 Player1Transform;
	glm::mat4 Player2Transform;
	glm::mat4 cameraProjection;
	glm::vec3 position;
	
	
	SA::SkeletalModel g_Player1Model;
	SA::SkeletalModel g_Player2Model;
	SA::SkeletalModel g_MeshTest;
	SA::SkeletalModel g_RunModel;
	SA::SkeletalModel g_RollModel;
	SA::SkeletalModel g_PunchModel;

	SA::sAnimation idle;
	SA::sAnimation run;
	SA::sAnimation roll;
	SA::sAnimation punch;

	CUBELoader LUT;

	bool skillshotPress = false;
	
	static float hp1;
	static float hp2;
	static float timer;
	static int win1;
	static int win2;

	// Don't know what to include yet
};