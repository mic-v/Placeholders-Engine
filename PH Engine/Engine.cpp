#include "Engine.h"
#include <glm/gtc/constants.hpp>


#define NAME "Projite"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900


int controllertype = 4;


Engine* Engine::_instance = nullptr;
float currentAngle = 135.0f;
//new
float Engine::hp1 = 100.f;
float Engine::hp2 = 100.f;
int Engine::win1 = 0.f;
int Engine::win2 = 0.f;
float Engine::timer = 120.0f;
/*
	This is the Singleton Pattern. Read more here:
	http://Engineprogrammingpatterns.com/singleton.html
	Essentially, make sures there is only one instance of a certain class
	I wanted to practice it so I decided to use this pattern for Engine. You don't have to follow this
	for every class
*/
Engine & Engine::instance()
{
	// TODO: insert return statement here
	if (_instance == nullptr)
	{
		_instance = new Engine();
		return *_instance;
	}
	else
	{
		return *_instance;
	}
	
}

//
bool Engine::startUp()
{
	/// setup Window ///
	// ------------- //
	if (glfwInit() == NULL)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_SAMPLES, 16);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, NAME, NULL, NULL);
	glfwMakeContextCurrent(_window);



	    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Platform/Renderer bindings
	const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

	InputModule::getInstance().startUp();

	/// glad: load all OpenGL function pointers ///
	// ---------------------------------------- //
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	

	//_draw = DebugDraw();
	//PHYSICS
	//bullet here
	//collisionConfiguration = new btDefaultCollisionConfiguration();
	//dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//overlappingPairCache = new btDbvtBroadphase();
	//solver = new btSequentialImpulseConstraintSolver;
	//dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	//
	//dynamicsWorld->setGravity(btVector3(0, 0, 0));
	//_draw.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	//dynamicsWorld->setDebugDrawer(&_draw);

	//{
	//	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	//	collisionShapes.push_back(groundShape);

	//	btTransform groundTransform;
	//	groundTransform.setIdentity();
	//	groundTransform.setOrigin(btVector3(0, -56, 0));

	//	btScalar mass(0.);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		groundShape->calculateLocalInertia(mass, localInertia);

	//	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);

	//	//add the body to the dynamics world
	//	dynamicsWorld->addRigidBody(body);
	//}

	//{
	//	//create a dynamic rigidbody

	//	//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
	//	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	//	collisionShapes.push_back(colShape);

	//	/// Create Dynamic Objects
	//	btTransform startTransform;
	//	startTransform.setIdentity();

	//	btScalar mass(1.f);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		colShape->calculateLocalInertia(mass, localInertia);

	//	startTransform.setOrigin(btVector3(2, 10, 0));

	//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);

	//	dynamicsWorld->addRigidBody(body);
	//}

	isActive = true;
	_camera = nullptr;
	camera2 = Camera(Perspective);
	//_camera->perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);
	camera2.setPosition(glm::vec3(0.0, 11.0f, 10.0f));
	camera2.setRotationX(-45.0f);
	cameraShadow = Camera(Orthographic);
	cameraShadow.setPosition(glm::vec3(0.0, 11.0f, 10.0f));
	cameraShadow.setRotationX(-45.0f);
	//cameraShadow.orthographic(35.0f, -35.0f, -35.0f, 35.0f, -10.0f, 20.0f);
	_camera = &camera2;




	position = glm::vec3(-4.0f, 0.4f, 0.0f);
	objectTransform = glm::mat4(1.0f);
	Player1Transform = glm::mat4(1.0f);
	objectTransform = glm::translate(objectTransform, glm::vec3(0.0f, 0.0f, 0.0f));
	Player1Transform = glm::translate(Player1Transform, position);
	Player1Transform = glm::rotate(Player1Transform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Player2Transform = glm::scale(Player1Transform, glm::vec3(0.001f, 0.001f, 0.001f));
	Player1Transform = glm::scale(Player1Transform, glm::vec3(0.002f, 0.002f, 0.002f));
	Player2Transform = Player1Transform;
	cameraProjection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);
	shadowProjection = glm::ortho(35.0f, -35.0f, -35.0f, 35.0f, 1.0f, 50.0f);
	_draw.projection = cameraProjection;





	FrameBuffer::initFramBuffers();
	frameBuffer.addDepthTarget();
	frameBuffer.addColorTarget(GL_RGB8);
	frameBuffer.addColorTarget(GL_R16F);
	frameBuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	shadowFramebuffer.addDepthTarget();
	//shadowFramebuffer.addColorTarget(GL_R11F_G11F_B10F);
	shadowFramebuffer.init(4096, 4096);

	postBuffer.setFormat(GL_R11F_G11F_B10F);
	postBuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	bloomFramebuffer.addDepthTarget();
	bloomFramebuffer.addColorTarget(GL_RGB32F);
	bloomFramebuffer.addColorTarget(GL_RGB8);
	bloomFramebuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	xrayFramebuffer.addDepthTarget();
	xrayFramebuffer.addColorTarget(GL_RGB8);
	xrayFramebuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	sobelFramebuffer.addDepthTarget();
	sobelFramebuffer.addColorTarget(GL_RGB8);
	sobelFramebuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Shader ex = Shader("Engine/Point.vs", "Engine/Point.fs");
	//_draw.line = ex;
	animsh = Shader("Contents/Shaders/textureskinned.vs", "Contents/Shaders/texture.fs");
	sh2 = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/DirectionLight.fs");
	watershader = Shader("Contents/Shaders/texturewater.vs", "Contents/Shaders/DirectionLightwater.fs");
	sht = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/trans.fs");
	LUTShader = Shader("Contents/Shaders/PassThrough.vert","Contents/Shaders/Post/LUTPost.frag");
	PBRShader = Shader("Contents/Shaders/PBR/PBR.vert", "Contents/Shaders/PBR/PBR.frag");
	SKYShader = Shader("Contents/Shaders/skybox.vert", "Contents/Shaders/skybox.fs");
	depthPass = Shader("Contents/Shaders/depthPass.vert", "Contents/Shaders/depthPass.fs");
	depthPass2 = Shader("Contents/Shaders/textureskinned.vs", "Contents/Shaders/depthPass.fs");
	xrayPass = Shader("Contents/Shaders/textureskinned.vs", "Contents/Shaders/xrayPass1.fs");

	sobelPass = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/sobelPass.fs");

	bloomPass = Shader("Contents/Shaders/depthPass.vert", "Contents/Shaders/bloomPass.frag");
	bloomBlurX = Shader("Contents/Shaders/PassThrough.vert","Contents/Shaders/bloomBlurX.frag");
	bloomBlurY = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/bloomBlurY.frag");

	bloomShader = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/bloom.frag");

	brightPass = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/brightPass.frag");

	pass = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/passthrough.fs");
	
	addPass = Shader("Contents/Shaders/PassThrough.vert", "Contents/Shaders/addFBdiscard.frag");
	//Debris = Mesh();
	//Debris.loadFromFile("Contents/Models/Derbis.obj");
	Debris.loadFromFBX("Debris1.fbx");
	
	
	Spear.loadFromFBX("Spear.fbx");
	Pointer = Spear;
	testPBRMesh.loadFromFBX("Sphere.fbx");

	mountainMesh.loadFromFBX("MOUNTAINS.fbx");
	healthHUDMesh.loadFromFBX("HealthHUD.fbx");
	//testMat.loadFile("Contents/Materials/Final Map.mtl");

	SkyboxMesh.loadFromFBX("skyboxTest.fbx");
	
	basemap.loadFromFBX("baseMap.fbx");
	

	river.loadFromFBX("River.fbx");
	LUT.loadLUT("Contents/CUBE/Zeke.CUBE");
	LUT.loadTexture();
	







	
	//idleframe1.loadFromFBX("Clem.fbx");


	//Pose = &idleframe1;
	//4.0, 5.0, 0, 1.0
	first = Light(glm::vec4(cameraShadow.getPosition(), 1.0f), glm::vec3(0.20f, 0.20f, 0.20f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(0.7f, 0.5f, 0.2f));
	second = Light(glm::vec4(0.0f, 5.0f, 0, 1.0f), glm::vec3(0.1f, 0.1f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(0.7f, 0.5f, 0.2f));
	ShadowLight = Light(glm::vec4(cameraShadow.getPosition(), 1.0f), glm::vec3(0.50f, 0.50f, 0.50f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(0.7f, 0.5f, 0.2f));
	

	skyboxTexture.push_back("Contents/Skybox/sky_c00.bmp");
	skyboxTexture.push_back("Contents/Skybox/sky_c01.bmp");
	skyboxTexture.push_back("Contents/Skybox/sky_c02.bmp");
	skyboxTexture.push_back("Contents/Skybox/sky_c03.bmp");
	skyboxTexture.push_back("Contents/Skybox/sky_c04.bmp");
	skyboxTexture.push_back("Contents/Skybox/sky_c05.bmp");
	skybox = new TextureCube(skyboxTexture);
	glm::mat4 objectSkyboxTransform = objectTransform;
	objectSkyboxTransform = glm::rotate(objectSkyboxTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	SkyboxOBJ = Object(&SkyboxMesh, skybox, glm::scale(objectTransform, glm::vec3(25.0, 25.0, 25.0)), &testMat);



	if (!TreeTex.LoadTexture("Contents/Textures/Debris_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!overlay.LoadTexture("Contents/Textures/testHP.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mapMask.LoadTexture("Contents/Textures/mapBaseMask.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!BaseTex.LoadTexture("Contents/Textures/mapBase_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!Clem.LoadTexture("Contents/Textures/Clem/black.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}
	if (!arrow.LoadTexture("Contents/Textures/arrow.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!test3.LoadTexture("Contents/Textures/river_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!metal.LoadTexture("Contents/Textures/Titanium.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}
	if (!waterNorm.LoadTexture("Contents/Textures/waternormal.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mMetal.LoadTexture("Contents/Textures/Titaniummetallic.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!NormalMap.LoadTexture("Contents/Textures/Titaniumnormal.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!rMetal.LoadTexture("Contents/Textures/Titaniumroughness.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!ambient.LoadTexture("Contents/Textures/TitaniumAmbient.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!IBL_Lookup.LoadTexture("Contents/Textures/ibl_brdf_lut.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!lightColor.LoadTexture("Contents/Textures/Titaniummetallic.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mountColor.LoadTexture("Contents/Textures/Mountain/basecolor.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mountMetal.LoadTexture("Contents/Textures/Mountain/metallic.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mountNormal.LoadTexture("Contents/Textures/Mountain/normal.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mountAO.LoadTexture("Contents/Textures/Mountain/ambientOcclusion.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!mountRough.LoadTexture("Contents/Textures/Mountain/roughness.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!debrisColor.LoadTexture("Contents/Textures/Debris/basecolor.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!debrisMetal.LoadTexture("Contents/Textures/Debris/metallic.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!debrisNormal.LoadTexture("Contents/Textures/Debris/normal.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!debrisAO.LoadTexture("Contents/Textures/Debris/ambientOcclusion.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!debrisRough.LoadTexture("Contents/Textures/Debris/roughness.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!spawnColor.LoadTexture("Contents/Textures/Spawn/basecolor.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!spawnMetal.LoadTexture("Contents/Textures/Spawn/metallic.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!spawnNormal.LoadTexture("Contents/Textures/Spawn/normal.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!spawnAO.LoadTexture("Contents/Textures/Spawn/ambientOcclusion.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!spawnRough.LoadTexture("Contents/Textures/Spawn/roughness.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}
	
	//IDLE ANIMATION AND SKELETON 



	loadAssimpAnim("New/Idle.fbx", &g_Player1Model);
	g_Player1Model.GetAnimation().ID = 0;
	g_Player1Model.GetAnimation().Loopable = true;
	idle = g_Player1Model.GetAnimation();
	g_Player1Model.m_Transition = idle;




	//RUN ANIMATION
	loadAssimpAnim("New/Running.fbx", &g_RunModel);
	g_RunModel.GetAnimation().ID = 1;
	run = g_RunModel.GetAnimation();
	run.Loopable = true;


	//ROLL ANIMATION
	loadAssimpAnim("New/Roll.fbx", &g_RollModel);
	g_RollModel.GetAnimation().ID = 2;
	roll = g_RollModel.GetAnimation();
	roll.Loopable = false;

	//PUNCH ANIMATION
	loadAssimpAnim("New/Throw.fbx", &g_PunchModel);
	g_PunchModel.GetAnimation().ID = 3;
	punch = g_PunchModel.GetAnimation();
	punch.Loopable = false;


	//THROW ANIMATION
	loadAssimpAnim("New/Throw.fbx", &g_ThrowModel);
	g_ThrowModel.GetAnimation().ID = 4;
	Throw = g_ThrowModel.GetAnimation();
	Throw.Loopable = false;

	g_Player1Model.loadHierarchy();

	g_Player2Model = g_Player1Model;



	testmesh.loadFromAnimatedModel("Contents/Models/meshskin.obj2", g_Player1Model);
	testmesh2 = testmesh;

	std::vector<Texture *> debrisVector;
	debrisVector.push_back(&debrisColor);
	debrisVector.push_back(&debrisMetal);
	debrisVector.push_back(&debrisNormal);
	debrisVector.push_back(&debrisAO);
	debrisVector.push_back(&debrisRough);

	std::vector <Texture *> spawnVector;
	spawnVector.push_back(&spawnColor);
	spawnVector.push_back(&spawnMetal);
	spawnVector.push_back(&spawnNormal);
	spawnVector.push_back(&spawnAO);
	spawnVector.push_back(&spawnRough);

	std::vector <Texture *> mountainVector;
	mountainVector.push_back(&mountColor);
	mountainVector.push_back(&mountMetal);
	mountainVector.push_back(&mountNormal);
	mountainVector.push_back(&mountAO);
	mountainVector.push_back(&mountRough);
	

	glm::mat4 tempspear = glm::rotate(360.0f, glm::vec3(0, 1, 0)) * glm::scale(objectTransform, glm::vec3(0.2f));

	testPBR = Object(&testPBRMesh, &metal, glm::translate(objectTransform, glm::vec3(0, 6, 0)), &testMat);
	
	Tree1 = Object(&Debris, debrisVector, glm::scale(objectTransform, glm::vec3(0.003f)), &testMat);
	Aim1 = Object(&Pointer, &arrow, glm::scale(objectTransform, glm::vec3(0.3f)), &testMat);
	Aim2 = Aim1;
	Spear1 = Object(&Spear, &BaseTex, tempspear, &testMat);
	Spear2 = Object(&Spear, &BaseTex, tempspear, &testMat);
	SecondSpear1 = Object(&Spear, &BaseTex, tempspear, &testMat);
	SecondSpear2 = Object(&Spear, &BaseTex, tempspear, &testMat);
	BasePlate = Object(&basemap, &BaseTex, objectTransform, &testMat);
	River = Object(&river, &test3, objectTransform, &testMat);
	Mountain = Object(&mountainMesh, mountainVector, glm::rotate(objectTransform, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)), &testMat);
	healthHUD = Object(&healthHUDMesh, &overlay, glm::rotate(objectTransform, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)), &testMat);
	spawn = Object(&spawnMesh, spawnVector, objectTransform, &testMat);
	TestSpear = Aim1;
	BasePlate.setRadius(5.9f);
	
	Tree1.setRadius(2.0f);
	Tree1.setPosition(glm::vec3(-2.7f, 0.9f, -3.3f));
	Tree2 = Tree1;
	Tree3 = Tree1;
	Tree4 = Tree1;
	Tree2.setPosition(glm::vec3(3.1f, 0.9f, -3.1f));
	Tree2.setOrientation(113.0f);
	Tree3.setPosition(glm::vec3(2.6f, 0.9f, 3.6f));
	Tree3.setOrientation(27.0f);
	Tree4.setPosition(glm::vec3(-3.0f, 0.9f, 3.2f));
	Tree4.setOrientation(299.0f);
	Object::InnerColliders.push_back(&BasePlate);
	Object::OutterColliders.push_back(&Tree1);
	Object::OutterColliders.push_back(&Tree2);
	Object::OutterColliders.push_back(&Tree3);
	Object::OutterColliders.push_back(&Tree4);


	Playerone = Player(&testmesh, &BaseTex, Player1Transform, &testMat, 100, 1.0f, &Aim1);
	Playertwo = Player(&testmesh2, &Clem, Player2Transform, &testMat, 120, 1.0f, &Aim2);
	Playertwo.setPosition(glm::vec3( -3.0f, Playertwo.getPositionV3().y, Playertwo.getPositionV3().z));

	Playerone.setRadius(0.2f);
	Playertwo.setRadius(0.2f);

	tempability = Ability(&Playerone, 3.0f, 5.0f);
	tempability2 = Ability(&Playertwo, 3.0f, 5.0f);
	playoneskillshot = Skillshot(&Playerone, 3.0f, 15.0f, 1.6f, 4.0f, 0.5f, &Spear1);

	playtwoskillshot = Skillshot(&Playertwo, 3.0f, 15.0f, 1.6f, 4.0f, 0.5f, &Spear2);
	
	playoneskillshot2 = Skillshot(&Playerone, 3.0f, 100.0f, 0.5f, 4.0f, 0.5f, &SecondSpear1);
	playtwoskillshot2 = Skillshot(&Playertwo, 3.0f, 100.0f, 0.5f, 4.0f, 0.5f, &SecondSpear2);
	

	Playerone.setAttack(&tempability);
	Playerone.setFirstAbility(&playoneskillshot);
	Playerone.setSecondAbility(&playoneskillshot2);

	Playertwo.setAttack(&tempability2);
	Playertwo.setFirstAbility(&playtwoskillshot);
	Playertwo.setSecondAbility(&playtwoskillshot2);

	
	
	//std::vector<glm::vec3, std::allocator<glm::vec3>> *temp;


	Spear1.setActive(false);
	Spear2.setActive(false);
	SecondSpear1.setActive(false);
	SecondSpear2.setActive(false);
	Aim1.setActive(false);
	Aim2.setActive(false);
	TestSpear.setActive(true);
	//SkyboxOBJ.setActive(false);
	Mover = &spawn;
	glfwGetTime();
	return true;
}

void Engine::shutDown()
{

	Debris.unload();
	TreeTex.Unload();

	//remove the rigidbodies from the dynamics world and delete them
	//for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	//{
	//	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
	//	btRigidBody* body = btRigidBody::upcast(obj);
	//	if (body && body->getMotionState())
	//	{
	//		delete body->getMotionState();
	//	}
	//	dynamicsWorld->removeCollisionObject(obj);
	//	delete obj;
	//}

	////delete collision shapes
	//for (int j = 0; j < collisionShapes.size(); j++)
	//{
	//	btCollisionShape* shape = collisionShapes[j];
	//	collisionShapes[j] = 0;
	//	delete shape;
	//}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

	InputModule::getInstance().shutDown();
	GLFWwindow *window = glfwGetCurrentContext();
	glfwDestroyWindow(window);

	glfwTerminate();
}


//second function that loads animations and converts into tempskele, then one that 
//just loads models with uvs and tangents by passing in mesh class
void Engine::loadAssimpAnim(std::string filename, SA::SkeletalModel * tempskele)
{
	Assimp::Importer tempimporter;
	const aiScene * pscene = tempimporter.ReadFile("Contents/FBX/Animations/" + filename,
		aiProcess_LimitBoneWeights |
		aiProcess_Triangulate |
		aiProcess_CalcTangentSpace|
		aiProcess_SortByPType | 
		aiProcess_Triangulate );
	if (pscene->HasMeshes()) {
		if (pscene->mMeshes[0]->HasTextureCoords(0)) {
			cout << "does have" << endl;
		}
	}
	std::cout << tempimporter.GetErrorString() << std::endl;
	AssimpConverter::Convert(pscene, *tempskele);
}





bool Engine::runAnimation(std::vector<Mesh*> poselist, float incr)
{

	if (currentanimframe < poselist.size()) {
		Pose = poselist[currentanimframe];
		currentlerpparam += incr;

	}
	else if (currentanimframe >= poselist.size()) {
		currentanimframe = 0;
		currentlerpparam = 0;
		return false;
	}
	if (currentlerpparam >= 1.0f) {
		currentanimframe++;
		currentlerpparam = 0.0f;
	}
	return true;
}

float PI = 3.14159265358979323846f;


void Engine::controllerInput(float Dt, int controller, float speed, Player *player, const float*axes, const unsigned char* buttons, Player* otherplayer, SA::SkeletalModel * playersmod)
{
	
	//TestSpear.setTransform(glm::scale(Playerone.getTransform() *  g_Player1Model.m_RightHand, glm::vec3(2/0.007, 2 / 0.007, 2 / 0.007)));
	//TestSpear.setPosition(TestSpear.getTransform() * glm::vec4(0,0,0,0));
	
	if (controller == 1)
	{
		//1 is up/down 0 is left/right
		//std::cout << "0: "<<axes[0] << " 1: " << axes[1] << std::endl;
		//std::cout << "2: " << axes[2] << " 5: " << axes[5] << std::endl;
		//std::cout << axes[2] << std::endl;
		// LEFT TRIGGER: std::cout << axes[3] << std::endl;
		// RIGHT TRIGGER: std::cout << axes[4] << std::endl;
		//left = 17
		//std::cout << 17<< " "<<buttons[17] << std::endl;
		////down = 16
		//std::cout << 16 << " " << buttons[16] << std::endl;
		////right = 15
		//std::cout << 15 << " " << buttons[15] << std::endl;
		////up = 14
		//std::cout << 14 << " " << buttons[14] << std::endl;
		if (!playersmod->m_isPlayingStatic) {
			if ((axes[0] <= -0.3f || axes[0] >= 0.3f) || (axes[1] <= -0.3f || axes[1] >= 0.3f))
			{
				playersmod->setAnimation2(&run);

				player->setOrientation(-player->getOrientation());

				float tempangle;
				if (controllertype == 4) {
					tempangle = 36 * ((atan2(-axes[0], -axes[1]) * PI) / 2 + 5);
				}
				else if (controllertype == 3) {
					tempangle = 36 * ((atan2(-axes[0], axes[1]) * PI) / 2 + 5);
				}


				glm::vec3 tempdir2 = glm::vec3(glm::sin(glm::radians(tempangle)) * speed * Dt, 0, glm::cos(glm::radians(tempangle)) * speed * Dt);

				
				player->setTransform(glm::translate(player->getTransform(), glm::vec3(tempdir2.x, 0, 0)));
				if (player->checkCollisions() || player->checkOutterCollision(otherplayer)) {
					player->setTransform(glm::translate(player->getTransform(), glm::vec3(-tempdir2.x, 0, 0)));
				}

				player->setTransform(glm::translate(player->getTransform(), glm::vec3(0, 0, tempdir2.z)));
				if (player->checkCollisions() || player->checkOutterCollision(otherplayer)) {
					player->setTransform(glm::translate(player->getTransform(), glm::vec3(0, 0, -tempdir2.z) ));
				}



				player->setOrientation(tempangle);
			}
			else {
				playersmod->setAnimation2(&idle);
			}


			if (axes[4] >= 0) {
				Object * tempobj = player->getPointer();
				float aim = tempobj->getOrientation();
				if ((axes[2] <= -0.3f || axes[2] >= 0.3f) || (axes[5] <= -0.3f || axes[5] >= 0.3f))
				{


					//player->setOrientation(-player->getOrientation());

					float tempangle;
					if (controllertype == 4) {
						tempangle = 36 * ((atan2(-axes[2], -axes[5]) * PI) / 2 + 5);
					}
					else if (controllertype == 3) {
						tempangle = 36 * ((atan2(-axes[2], axes[5]) * PI) / 2 + 5);
					}

					
					
					aim = tempangle;
				}
				float temprad = glm::radians(aim);
				
				tempobj->setActive(true);
				tempobj->setPosition(player->getPositionV3() + (glm::vec3(1) * glm::vec3(sin(temprad), 1, cos(temprad))));
				tempobj->setOrientation(-tempobj->getOrientation());
				tempobj->setOrientation(aim);
				

				//SQUARE
				if (GLFW_PRESS == buttons[0]) {
					//std::cout << "SQUARE" << std::endl;
					if (player->skillshotAttack(otherplayer, aim)) {
						player->setOrientation(-player->getOrientation());
						player->setOrientation(aim);

						playersmod->setAnimation2(&Throw);
						tempobj->setActive(false);
					}
				}
			}
			else {
				
				Object * tempobj = player->getPointer();
				tempobj->setOrientation(-tempobj->getOrientation());
				tempobj->setOrientation(player->getOrientation());
				tempobj->setActive(false);
			}
			//X
			if (GLFW_PRESS == buttons[1]) {
				if(!playersmod->m_isBlending){
					playersmod->setAnimation2(&roll);
					player->startRoll(2);
				
				}
			
				//std::cout << "X" << std::endl;
			}

			//O
			if (GLFW_PRESS == buttons[2]) {
				//std::cout << "O" << std::endl;
			}
			//TRIANGLE
			if (GLFW_PRESS == buttons[3]) {
				//std::cout << "tri" << std::endl;
			}


			if (GLFW_PRESS == buttons[4]) {
				//std::cout << "bumper left" << std::endl;
			}
			if (GLFW_PRESS == buttons[5]) {
				//std::cout << "bumper right" << std::endl;
				if(player->BaseAttack(otherplayer))
				playersmod->setAnimation2(&punch);
			}


			if (GLFW_PRESS == buttons[14] && !player->Pressed1) {
				//std::cout << "O" << std::endl;
				player->SwapSkillShot();
				player->Pressed1 = true;
			}
			if (GLFW_PRESS != buttons[14] && player->Pressed1) {

				player->Pressed1 = false;
			}

			if (GLFW_PRESS == buttons[16] && !player->Pressed2) {
				//std::cout << "O" << std::endl;
				player->SwapSkillShot();
				player->Pressed2 = true;
			}
			
			if (GLFW_PRESS != buttons[16] && player->Pressed2) {

				player->Pressed2 = false;
			}
			
		}
	}

}






void Engine::checkAnimation() {
	
	

}

double currentFrame;
double lastFrame;
double deltaTime;
float rotation;
void Engine::runGame()
{
	double lastTime = glfwGetTime();
	//double deltaTime = 1;
	int frames = 0;

	

	/*if (frameBuffer._IsInit == true && GLFWwindowsizefun()) {
		frameBuffer.resize();
	}*/

	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

	while (!glfwWindowShouldClose(glfwGetCurrentContext()))
	{
		currentFrame = glfwGetTime();

		if (lastFrame != NULL) {
			deltaTime = currentFrame - lastFrame;
		}
		else {
			deltaTime = 0;
		}

		lastFrame = currentFrame;

		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (InputModule::getInstance().isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		TotalGameTime += deltaTime;
		timer = TotalGameTime;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			ImGui::Begin("Player 1");
			ImGui::Text("Health = %f", Playerone.getHealth());
			ImGui::Text("Ability 1 = %i", static_cast<int>(playoneskillshot.getTimeLeft()));
			ImGui::SetWindowSize(ImVec2(200, 75));
			ImGui::SetWindowPos(ImVec2(100, 75));
			ImGui::End();

		}

		{
			ImGui::Begin("Player 2");
			ImGui::Text("Health = %f", Playertwo.getHealth());
			ImGui::Text("Ability 1 = %i", static_cast<int>(playtwoskillshot.getTimeLeft()));
			ImGui::SetWindowSize(ImVec2(200, 75));
			ImGui::SetWindowPos(ImVec2(1300,75));
			ImGui::End();

		}

		{
			ImGui::Begin("");
			ImGui::Text("Time: %i", static_cast<int>(timer));
			
			ImGui::SetWindowSize(ImVec2(100, 75));
			ImGui::SetWindowPos(ImVec2(SCREEN_WIDTH / 2.0f - 30.0f, 75));
			ImGui::End();

		}

		
		frames++;
		

		g_Player1Model.Update(deltaTime);
		g_Player2Model.Update(deltaTime);
		playerInput(deltaTime);

		

		//for (int i = 0; i < 150; i++)
		//{
		//	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//	//print positions of all objects
		//	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		//	{
		//		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		//		btRigidBody* body = btRigidBody::upcast(obj);
		//		btTransform trans;
		//		if (body && body->getMotionState())
		//		{
		//			body->getMotionState()->getWorldTransform(trans);
		//		}
		//		else
		//		{
		//			trans = obj->getWorldTransform();
		//		}
		//	}
		//}
		//


		Playerone.update(deltaTime);
		Playertwo.update(deltaTime);
		//float puredist = (Playerone.getPositionV3().x - Playertwo.getPositionV3().x);
		//float actualdist = sqrt(puredist * puredist);
		//_camera->setPositionZ(2 + actualdist * 2);
		Tree1.Rotate(rotation);
		first.setPosition(glm::vec4(cameraShadow.getPosition(), 1.0f));
		ShadowLight.setPosition(glm::vec4(cameraShadow.getPosition(), 1.0f));

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

		depthBiasMVP = biasMatrix * shadowProjection * glm::inverse(cameraShadow.getView()) * _camera->getView();
		cameraShadow.update(deltaTime);
		

	
		
		//std::cout << currentTime - lastTime << std::endl;
		_camera->update(deltaTime);
		InputModule::getInstance().update(deltaTime);
		render();

		

	}
}

void Engine::render()
{
	glm::vec3 cameraPos = _camera->getPosition();
	glm::vec3 lightPos = first.getPosition();


	glEnable(GL_DEPTH_TEST);
	

	shadowFramebuffer.clear();

	frameBuffer.clear();

	postBuffer.clear();

	xrayFramebuffer.clear();

	bloomFramebuffer.clear();

	sobelFramebuffer.clear();

	shadowFramebuffer.bind();
	glViewport(0, 0, 4096, 4096);
	depthPass.use();
	depthPass.sendUniformMat4("projection", shadowProjection);
	depthPass.sendUniformMat4("view", glm::inverse(cameraShadow.getView()));

	
	Tree1.LoadObject(&depthPass);
	Tree2.LoadObject(&depthPass);
	Tree3.LoadObject(&depthPass);
	Tree4.LoadObject(&depthPass);

	
	Spear1.LoadObject(&depthPass);
	Spear2.LoadObject(&depthPass);
	SecondSpear1.LoadObject(&depthPass);
	SecondSpear2.LoadObject(&depthPass);
	testPBR.LoadObject(&depthPass);
	depthPass.unuse();
	//player1
	depthPass2.use();
	depthPass2.sendUniformMat4("projection", shadowProjection);
	depthPass2.sendUniformMat4("view", glm::inverse(cameraShadow.getView()));
	g_Player1Model.sendToShader(&depthPass2);
	Playerone.LoadObject(&depthPass2);
	depthPass2.unuse();
	//player 2
	depthPass2.use();
	depthPass2.sendUniformMat4("projection", shadowProjection);
	depthPass2.sendUniformMat4("view", glm::inverse(cameraShadow.getView()));
	g_Player2Model.sendToShader(&depthPass2);
	Playertwo.LoadObject(&depthPass2);
	depthPass2.unuse();
	shadowFramebuffer.unbind();


	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	mapMask.Bind(5);
	bloomFramebuffer.bind();
	bloomPass.use();
	bloomPass.sendUniformMat4("projection", cameraProjection);
	bloomPass.sendUniformMat4("view", glm::inverse(_camera->getView()));
	BasePlate.LoadObject(&bloomPass);
	bloomPass.unuse();
	mapMask.Unbind();
	bloomFramebuffer.unbind();

	xrayFramebuffer.bind();
	animsh.use();
	animsh.sendUniformMat4("projection", cameraProjection);
	animsh.sendUniformMat4("view", glm::inverse(_camera->getView()));
	g_Player1Model.sendToShader(&animsh);
	//////Lights here
	first.LoadLight(&animsh);
	second.LoadLight(&animsh);
	////
	////
	//////Objects here//
	Playerone.LoadObject(&animsh);
	animsh.unuse();

	animsh.use();
	animsh.sendUniformMat4("projection", cameraProjection);
	animsh.sendUniformMat4("view", glm::inverse(_camera->getView()));
	g_Player2Model.sendToShader(&animsh);
	//////Lights here
	first.LoadLight(&animsh);
	second.LoadLight(&animsh);
	////
	////
	//////Objects here//
	Playertwo.LoadObject(&animsh);
	animsh.unuse();
	xrayFramebuffer.unbind();

	sobelFramebuffer.bind();
	sobelPass.use();
	glm::vec3 sSize = glm::vec3(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);
	sobelPass.sendUniformMat4("projection", cameraProjection);
	sobelPass.sendUniformMat4("view", glm::inverse(_camera->getView()));
	xrayFramebuffer.bindColorAsTexture(0, 30);
	sobelPass.sendUniformVec3("screenSize", sSize);
	//g_Animatedmodel.sendToShader(&sobelPass);
	//Playerone.LoadObject(&sobelPass);
	xrayFramebuffer.drawFSQ();
	xrayFramebuffer.unbindTexture(30);
	sobelPass.unuse();
	sobelFramebuffer.unbind();



	//---------------------------------------------------------
	////TRANSPARENT OBJS HERE
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//sht.use();

	//sht.sendUniformMat4("projection", cameraProjection);
	//sht.sendUniformMat4("view", _camera->getLookMatrix());
	//first.LoadLight(&sht);
	//second.LoadLight(&sht);
	////
	////
	//

	//sht.unuse();
	//glDisable(GL_BLEND);
	//---------------------------------------------------------



	/*frameBuffer.unbind();
	LUTShader.use();
	LUTShader.sendUniformMat4("projection", cameraProjection);
	LUTShader.sendUniformMat4("view", _camera->getLookMatrix());
	LUTShader.sendUniformFloat("uAmount", 0.0f);
	LUTShader.sendUniformFloat("LUTSize", LUT.getSize());
	frameBuffer.bindColorAsTexture(0, 13);
	glDisable(GL_DEPTH_TEST);
	frameBuffer.drawFSQ();
	frameBuffer.unbindTexture(13);
	LUTShader.unuse();
	LUT.unbind3D(12);*/
	//shadowFramebuffer.drawFSQ();
	frameBuffer.bind();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	sh2.use();

	// Compute the MVP matrix from the light's point of view
	glm::vec3 shadowPos = cameraShadow.getPosition();

	//glm::vec4 temp = normalize(glm::vec4(cameraShadow.getPosition(), 1.0f) - BasePlate.getPositionV4());
	/*glm::vec4 cameraForward = normalize(glm::vec4(_camera->getPos(), 1.0f) - BasePlate.getPositionV4());
	glm::vec3 cameraRight = glm::cross(glm::normalize(glm::vec3(0, 1, 0)), glm::vec3(cameraForward.x, cameraForward.y, cameraForward.z));
	glm::vec3 cameraUP = glm::cross(glm::vec3(cameraForward.x, cameraForward.y, cameraForward.z), cameraRight);
	glm::mat4 viewMat =  _camera->getLookMatrix(_camera->getPos(), cameraForward, cameraUP);
	glm::mat4 tempmat = cameraShadow.getLookMatrix();*/

	//glm::vec4 cs = cameraShadow.getLookMatrix()[3];
	glm::mat4 cameraDirection = glm::inverse(_camera->getView()) * cameraShadow.getView();
	glm::vec4 cameraV = glm::vec4(cameraDirection[2].x, cameraDirection[2].y, cameraDirection[2].z, cameraDirection[2].w);
	

	sh2.sendUniformMat4("projection", cameraProjection);
	sh2.sendUniformMat4("view", glm::inverse(_camera->getView()));
	sh2.sendUniformVec4("LightDirection", cameraV);
	sh2.sendUniformMat4("depthBiasMVP", depthBiasMVP);
	shadowFramebuffer.bindDepthAsTexture(13);
	////Lights here
	first.LoadLight(&sh2);
	//second.LoadLight(&sh2);
	//ShadowLight.LoadLight(&sh2);
	//
	//
	////Objects here//

	Aim1.LoadObject(&sh2);
	Aim2.LoadObject(&sh2);
	TestSpear.LoadObject(&sh2);
	Spear1.LoadObject(&sh2);
	Spear2.LoadObject(&sh2);
	SecondSpear1.LoadObject(&sh2);
	SecondSpear2.LoadObject(&sh2);
	BasePlate.LoadObject(&sh2);
	//
	shadowFramebuffer.unbindTexture(13);
	
	sh2.unuse();

	watershader.use();
	waterNorm.Bind(14);
	watershader.sendUniformMat4("projection", cameraProjection);
	watershader.sendUniformMat4("view", glm::inverse(_camera->getView()));
	watershader.sendUniformVec4("LightDirection", cameraV);
	watershader.sendUniformMat4("depthBiasMVP", depthBiasMVP);
	watershader.sendUniformFloat("uTime", TotalGameTime);

	first.LoadLight(&watershader);
	River.LoadObject(&watershader);
	
	
	waterNorm.Unbind();
	
	watershader.unuse();


	glDepthMask(GL_FALSE);
	glDepthFunc(GL_GREATER);
	xrayPass.use();
	xrayPass.sendUniformMat4("projection", cameraProjection);
	xrayPass.sendUniformMat4("view", glm::inverse(_camera->getView()));
	xrayPass.sendUniformFloat("uTime", deltaTime);
	g_Player1Model.sendToShader(&xrayPass);
	Playerone.LoadObject(&xrayPass);
	xrayPass.unuse();

	xrayPass.use();
	xrayPass.sendUniformMat4("projection", cameraProjection);
	xrayPass.sendUniformMat4("view", glm::inverse(_camera->getView()));
	xrayPass.sendUniformFloat("uTime", deltaTime);
	g_Player2Model.sendToShader(&xrayPass);
	Playertwo.LoadObject(&xrayPass);
	xrayPass.unuse();


	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	animsh.use();
	animsh.sendUniformMat4("projection", cameraProjection);
	animsh.sendUniformMat4("view", glm::inverse(_camera->getView()));
	g_Player1Model.sendToShader(&animsh);
	//////Lights here
	first.LoadLight(&animsh);
	second.LoadLight(&animsh);
	////
	////
	//////Objects here//

	Playerone.LoadObject(&animsh);

	animsh.unuse();

	animsh.use();
	animsh.sendUniformMat4("projection", cameraProjection);
	animsh.sendUniformMat4("view", glm::inverse(_camera->getView()));
	g_Player2Model.sendToShader(&animsh);
	//////Lights here
	first.LoadLight(&animsh);
	second.LoadLight(&animsh);
	////
	////
	//////Objects here//

	Playertwo.LoadObject(&animsh);

	animsh.unuse();



	skybox->Bind3D(25);
	SKYShader.use();
	SKYShader.sendUniformMat4("projection", cameraProjection);
	SKYShader.sendUniformMat4("view", glm::inverse(_camera->getView()));
	SkyboxOBJ.LoadObject(&SKYShader);
	SKYShader.unuse();
	skybox->unbind3D(25);

	skybox->Bind3D(25);
	skybox->Bind3D(26);
	IBL_Lookup.Bind(27);


	PBRShader.use();
	glm::vec3 lightCol = glm::vec3(255.0f, 255.0f, 255.0f);
	PBRShader.sendUniformMat4("projection", cameraProjection);
	PBRShader.sendUniformMat4("view", glm::inverse(_camera->getView()));
	PBRShader.sendUniformVec3("uCameraPosition", cameraPos);
	PBRShader.sendUniformVec3("uLightPosition", lightPos);
	PBRShader.sendUniformVec3("uLightColor", lightCol);
	//PBRShader.sendUniformMat4("depthBiasMVP", depthBiasMVP);
	PBRShader.sendUniformMat4("iView", _camera->getView());

	testPBR.LoadObject(&PBRShader);

	Tree1.LoadObject(&PBRShader);
	Tree2.LoadObject(&PBRShader);
	Tree3.LoadObject(&PBRShader);
	Tree4.LoadObject(&PBRShader);

	spawn.LoadObject(&PBRShader);

	//BasePlate.LoadObject(&PBRShader);
	PBRShader.unuse();

	skybox->unbind3D(25);
	skybox->unbind3D(26);
	IBL_Lookup.Unbind();
	lightColor.Unbind();

	frameBuffer.unbind();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	//glDisable(GL_CULL_FACE);
	sh2.use();
	sh2.sendUniformMat4("projection", shadowProjection);
	sh2.sendUniformMat4("view", glm::inverse(_camera->getView()));
	healthHUD.LoadObject(&sh2);
	sh2.unuse();
	//overlay.Unbind();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	//Post process draw

	xrayFramebuffer.bind();
	bloomShader.use();
	sobelFramebuffer.bindColorAsTexture(0, 29);
	frameBuffer.bindColorAsTexture(1, 30);
	sobelFramebuffer.drawFSQ();
	sobelFramebuffer.unbindTexture(29);
	frameBuffer.unbindTexture(30);
	bloomShader.unuse();
	xrayFramebuffer.unbind();

	frameBuffer.bind();
	bloomShader.use();
	xrayFramebuffer.bindColorAsTexture(0, 29);
	frameBuffer.bindColorAsTexture(0, 30);
	xrayFramebuffer.drawFSQ();
	xrayFramebuffer.unbindTexture(29);
	frameBuffer.unbindTexture(30);
	bloomShader.unuse();
	frameBuffer.unbind();



	pass.use();
	frameBuffer.bindColorAsTexture(0, 30);
	postBuffer.drawToPost();
	frameBuffer.unbindTexture(30);
	pass.unuse();

	pass.use();
	postBuffer.draw(30);
	pass.unuse();

	//Adds bloomMap texture and Framebuffer texture together.
	frameBuffer.bind();
	bloomShader.use();
	bloomFramebuffer.bindColorAsTexture(1, 29);
	postBuffer.draw(30);
	bloomFramebuffer.unbindTexture(29);
	bloomShader.unuse();
	frameBuffer.unbind();

	//Does brightPass check
	brightPass.use();
	postBuffer.draw(30);
	brightPass.unuse();

	for (int i = 0; i < 15; i++) {
		bloomBlurX.use();
		bloomBlurX.sendUniformFloat("width", SCREEN_WIDTH);
		postBuffer.draw(30);
		bloomBlurX.unuse();

		bloomBlurY.use();
		bloomBlurY.sendUniformFloat("height", SCREEN_HEIGHT);
		postBuffer.draw(30);
		bloomBlurY.unuse();
	}

	bloomShader.use();
	frameBuffer.bindColorAsTexture(0, 30);
	postBuffer.draw(29);
	frameBuffer.unbindTexture(30);
	bloomShader.unuse();




	LUT.Bind3D(12);
	LUTShader.use();
	LUTShader.sendUniformMat4("projection", cameraProjection);
	LUTShader.sendUniformMat4("view", glm::inverse(_camera->getView()));
	LUTShader.sendUniformFloat("uAmount", 0.0f);
	LUTShader.sendUniformFloat("LUTSize", LUT.getSize());
	glDisable(GL_DEPTH_TEST);
	postBuffer.draw(30);
	LUTShader.unuse();
	LUT.unbind3D(12);


	pass.use();
	//frameBuffer.unbind();
	postBuffer.drawToScreen(30);
	//frameBuffer.unbindTexture(30);
	pass.unuse();

	//dynamicsWorld->debugDrawWorld();
	glBindVertexArray(0);
	TreeTex.Unbind();

	//RenderAnimation();
	//sh2.unuse();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	glfwSwapBuffers(glfwGetCurrentContext());
	glfwPollEvents();
}
float playerspeed = 1150.0f;
void Engine::playerInput(float t)
{
	

	int axesCount;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
	//std::cout << axesCount << endl;
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

	controllerInput(t, glfwJoystickPresent(GLFW_JOYSTICK_1), playerspeed, &Playerone, axes, buttons, &Playertwo, &g_Player1Model);



	int axesCount2;
	const float *axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount2);
	int count2;
	const unsigned char* buttons2 = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &count2);

	controllerInput(t, glfwJoystickPresent(GLFW_JOYSTICK_2), playerspeed, &Playertwo, axes2, buttons2, &Playerone, &g_Player2Model);



	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_1))
	{
		std::cout << "Camera Pos: " << cameraShadow.getPositionX() << ", " << cameraShadow.getPositionY() << ", " << cameraShadow.getPositionZ() << std::endl;

		//_camera = &camera1;
	}
	else if (InputModule::getInstance().isKeyPressed(GLFW_KEY_2))
	{
		std::cout << "Camera Rotation: " << cameraShadow.getRotationX() << ", " << cameraShadow.getRotationY() << ", " << cameraShadow.getRotationZ() << std::endl;
		//_camera = &camera2;
	}

	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_Y)) {

		//first.setPosition(first.getPosition() + glm::vec4(0.0, 0.0, 1.0, 0.0));
		rotation += -1.0f;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_P)) {

		//first.setPosition(first.getPosition() + glm::vec4(0.0, 0.0, 1.0, 0.0));
		rotation += 1.0f;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_W))
	{
		//second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y, second.getPosition().z - 0.1f, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		//Playerone.setPosition(Playerone.getPositionV3() - glm::vec3(0.0f, 0.0f, 0.1f));
		_camera->setPositionZ(_camera->getPositionZ() - 0.2f);
		std::cout << "test" << std::endl;
		
		//_camera->processKeyboard(FORWARD, deltaTime);

		//animation2run = true;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_S))
	{

		_camera->setPositionZ(_camera->getPositionZ() + 0.2f);
		//second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y, second.getPosition().z + 0.1f, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		//Playerone.setPosition(Playerone.getPositionV3() + glm::vec3(0.0f, 0.0f, 0.1f));
		//animation3run = true;
		//_camera->processKeyboard(BACKWARD, deltaTime);
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_A))
	{
		_camera->setPositionX(_camera->getPositionX() - 0.2f);
		//second.setPosition(glm::vec4(second.getPosition().x - 0.1f, second.getPosition().y, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		//Playerone.setPosition(Playerone.getPositionV3() - glm::vec3(0.1f, 0.0f, 0.0f));
		//animation2run = true;
		//_camera->processKeyboard(LEFT, deltaTime);
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_D))
	{
		_camera->setPositionX(_camera->getPositionX() + 0.2f);
		//second.setPosition(glm::vec4(second.getPosition().x + 0.1f, second.getPosition().y, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		//Playerone.setPosition(Playerone.getPositionV3() + glm::vec3(0.1f, 0.0f, 0.0f));
		//animation3run = true;

		//_camera->processKeyboard(RIGHT, deltaTime);
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_R))
	{
		_camera->setPositionY(_camera->getPositionY() + 0.2f);
		second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y + 0.1f, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		//_camera->moveUp();
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_F))
	{
		_camera->setPositionY(_camera->getPositionY() - 0.2f);
		second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y - 0.1f, second.getPosition().z, second.getPosition().w));
		//_camera->moveDown();
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_I))
	{
		//_camera->setRotationX(_camera->getRotationX() + 1.0f);
		//cameraShadow.setRotationX(cameraShadow.getRotationX() + 0.2f);
		//Playertwo.setPosition(Playertwo.getPositionV3() - glm::vec3(0.0f, 0.0f, 0.1f));
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(0, 0, -0.1f));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_K))
	{
		//_camera->setRotationX(_camera->getRotationX() - 1.0f);
		//cameraShadow.setRotationX(cameraShadow.getRotationX() - 0.2f);
		//Playertwo.setPosition(Playertwo.getPositionV3() + glm::vec3(0.0f, 0.0f, 0.1f));
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(0, 0, 0.1f));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_J))
	{
	//	_camera->setRotationY(_camera->getRotationY() - 1.0f);
		//cameraShadow.setRotationY(cameraShadow.getRotationY() - 0.2f);
		//Playertwo.setPosition(Playertwo.getPositionV3() - glm::vec3(0.1f, 0.0f, 0.0f));
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(-0.1f, 0, 0));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_L))
	{
		//cameraShadow.setRotationY(cameraShadow.getRotationY() + 0.2f);
		//_camera->setRotationY(_camera->getRotationY() + 1.0f);
		
		//Playertwo.setPosition(Playertwo.getPositionV3() + glm::vec3(0.1f, 0.0f, 0.0f));
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(0.1f, 0, 0));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_U))
	{
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(0, 0.1f, 0));
		//Playertwo.BaseAttack(&Playerone);
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_O))
	{
		Mover->setPosition(Mover->getPositionV3() + glm::vec3(0, -0.1f, 0));
		//Playertwo.BaseAttack(&Playerone);
	} 
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_SPACE))
	{
		//Trees.setPosition(Trees.getPositionV3() + glm::vec3(0, -0.1f, 0));
		//Playertwo.BaseAttack(&Playerone);
		std::cout << Mover->getPositionV3().x << " " << Mover->getPositionV3().y << " " << Mover->getPositionV3().z << std::endl;
		std::cout << rotation << std::endl;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_E))
	{
		//Playerone.skillshotAttack(&Playertwo);
	}
}
