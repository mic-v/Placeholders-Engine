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
#include "FmodWrapper.h"
#include "CUBE.h" 
#include "Player.h"
#include "Engine/Math/math.h"
#include "Camera.h"
#include "Engine/Light.h"
#include "Engine/InputModule.h"
#include "Engine/DebugDraw.h"
#include <vector>
#include "Material.h"
#include "FrameBuffer.h"
#include "PostProcessBuffer.h"
#include "Ability.h"
#include <btBulletDynamicsCommon.h>
#include "AssimpConverter.h"
#include "SkeletalModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Skybox.h"

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
	float TotalGameTime = 0;
	Camera *_camera;
	Camera camera2;
	
	Camera cameraShadow;
	Mesh Debris;
	Mesh Pointer;
	Mesh basemap;
	Mesh river;
	Mesh Spear;

	Mesh idleframe1;
	

	Mesh * Pose;
	


	
	Object Tree1;
	Object Tree2;
	Object Tree3;
	Object Tree4;
	Object TestSpear;
	Object* Mover;
	Object BasePlate;
	Object River;
	Object Aim1;
	Object Aim2;
	Object Spear1;
	Object Spear2;
	Object SecondSpear1;
	Object SecondSpear2;
	Object testPBR;
	Object Mountain;
	Object SkyboxOBJ;
	Object healthHUD;
	Object spawn;
	Mesh healthHUDMesh;
	Mesh mountainMesh;
	Mesh spawnMesh;

	Player Playerone;
	Player Playertwo;
	Mesh testmesh;
	Mesh testmesh2;
	Mesh testPBRMesh;
	Mesh SkyboxMesh;

	Ability tempability;
	Ability tempability2;
	Skillshot playoneskillshot;
	Skillshot playtwoskillshot;
	Skillshot playoneskillshot2;
	Skillshot playtwoskillshot2;
	Shader animsh;
	Shader sh2;
	Shader watershader;
	Shader sht;
	Shader LUTShader;
	Shader PBRShader;
	Shader SKYShader;
	Shader ShadowShader;
	Shader depthPass;
	Shader depthPass2;
	Shader bloomShader;
	Shader brightPass;
	Shader bloomPass;
	Shader bloomBlurX;
	Shader bloomBlurY;
	Shader xrayPass;
	Shader sobelPass;
	Shader addPass;
	Shader invertPass;
	Shader pass;
	Light first;
	Light second;
	Light ShadowLight;
	Texture mapMask;
	Texture overlay;
	Texture TreeTex;
	Texture BaseTex;
	Texture test3;
	Texture lightColor;
	Texture waterNorm;
	Texture arrow;
	Texture Clem;

	FMOD_VECTOR player1 = {0,0,0};
	FMOD_VECTOR player2 = { 0,0,0 };
	FMOD_VECTOR listener = { 0,0,0 };
	FMOD::Channel * Player1Channel;
	FMOD::Channel * Player2Channel;
	std::vector<std::string> skyboxTexture;
	TextureCube *skybox;
	std::vector<Texture*> test;
	//PBR
	Texture metal;
	Texture mMetal;
	Texture NormalMap;
	Texture rMetal;
	Texture ambient;
	Texture IBL_Lookup;

	Texture mountColor;
	Texture mountMetal;
	Texture mountNormal;
	Texture mountAO;
	Texture mountRough;

	Texture debrisColor;
	Texture debrisMetal;
	Texture debrisNormal;
	Texture debrisAO;
	Texture debrisRough;

	Texture spawnColor;
	Texture spawnMetal;
	Texture spawnNormal;
	Texture spawnAO;
	Texture spawnRough;
	//PBR END

	Material testMat;
	FrameBuffer frameBuffer;
	FrameBuffer shadowFramebuffer;

	FrameBuffer bloomFramebuffer;
	FrameBuffer xrayFramebuffer;
	FrameBuffer sobelFramebuffer;

	PostProcessBuffer postBuffer;

	glm::mat4 objectTransform;
	glm::mat4 Player1Transform;
	glm::mat4 Player2Transform;
	glm::mat4 cameraProjection;
	glm::mat4 shadowProjection;
	glm::vec3 position;
	
	
	SA::SkeletalModel g_Player1Model;
	SA::SkeletalModel g_Player2Model;
	SA::SkeletalModel g_MeshTest;
	SA::SkeletalModel g_RunModel;
	SA::SkeletalModel g_RollModel;
	SA::SkeletalModel g_PunchModel;
	SA::SkeletalModel g_ThrowModel;

	SA::sAnimation idle;
	SA::sAnimation run;
	SA::sAnimation roll;
	SA::sAnimation punch;
	SA::sAnimation Throw;

	CUBELoader LUT;

	glm::mat4 depthBiasMVP;

	bool skillshotPress = false;
	
	static float hp1;
	static float hp2;
	static float timer;
	static int win1;
	static int win2;

	// Don't know what to include yet
};