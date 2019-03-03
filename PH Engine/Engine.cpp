#include "Engine.h"
#include <glm/gtc/constants.hpp>

#define NAME "Projite"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900


int controllertype = 4;


Engine* Engine::_instance = nullptr;
float currentAngle = 135.0f;

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
	camera1 = FPSCamera(glm::vec3(0.0f, 5.0f, 30.0f));
	camera2 = Camera(glm::vec3(0.0, 11.0f, 5.0f));
	camera2.setYDirection(-60.f);
	_camera = &camera2;

	Framebuffer::initFrameBuffers();
	frameBuffer.addDepthTarget();
	frameBuffer.addColorTarget(GL_RGB8);
	frameBuffer.addColorTarget(GL_R11F_G11F_B10F);
	frameBuffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	position = glm::vec3(-4.0f, 0.1f, 0.0f);
	objectTransform = glm::mat4(1.0f);
	Player1Transform = glm::mat4(1.0f);
	objectTransform = glm::translate(objectTransform, glm::vec3(0.0f, 0.0f, 0.0f));
	Player1Transform = glm::translate(Player1Transform, position);
	Player1Transform = glm::rotate(Player1Transform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Player2Transform = glm::scale(Player1Transform, glm::vec3(0.2f, 0.2f, 0.2f));
	Player1Transform = glm::scale(Player1Transform, glm::vec3(0.01f, 0.01f, 0.01f));
	cameraProjection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);
	_draw.projection = cameraProjection;





	
	//Shader ex = Shader("Engine/Point.vs", "Engine/Point.fs");
	//_draw.line = ex;
	sh2 = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/texture.fs");
	sht = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/water.fs");
	/*LUTShader.load("Contents/Shaders/PassThrough.vert","Contents/Shaders/Post/LUTPost.frag");
	
	object = Mesh();
	object.loadFromFile("Contents/Models/Derbis.obj");
	object2.loadFromFile("Contents/Models/untitled.obj");
	rockMesh.loadFromFile("Contents/Models/rock.obj");
	testMat.loadFile("Contents/Materials/Final Map.mtl");

	
	basemap.loadFromFile("Contents/Models/mapBase.obj");

	
	river.loadFromFile("Contents/Models/river.obj");

	LUT.loadLUT("Contents/CUBE/Zeke.CUBE");
	LUT.loadTexture();*/
	







	
	//idleframe1.loadFromFile("Contents/Models/Idle/frame1.obj");



	//Pose = &idleframe1;

	first = Light(glm::vec4(4.0f, 5.0f, 0, 1.0f), glm::vec3(0.0f, 0.0f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(0.7f, 0.5f, 0.2f));
	second = Light(glm::vec4(0.0f, 5.0f, 0, 1.0f), glm::vec3(0.1f, 0.1f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(0.7f, 0.5f, 0.2f));
	

	if (!TreeTex.LoadTexture("Contents/Textures/Debris_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!BaseTex.LoadTexture("Contents/Textures/mapBase_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!test3.LoadTexture("Contents/Textures/river_UV.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	Assimp::Importer tempimporter;
	const aiScene * pscene = tempimporter.ReadFile("Contents/FBX/look1.fbx",
		aiProcess_LimitBoneWeights |
		aiProcess_Triangulate |
		aiProcess_SortByPType);

	std::cout << tempimporter.GetErrorString() << std::endl;
	AssimpConverter::Convert(pscene, g_Animatedmodel);

	const SA::sAnimatedMesh& AnimMesh = g_Animatedmodel.GetMesh(0);
	//testmesh.loadFromFile("Contents/Models/meshskin.obj");
	//std::cout << testmesh.getNumVertices() << std::endl;
	
	//std::cout << g_Animatedmodel << std::endl;
	//g_Animatedmodel.Update(0.1);
	g_Animatedmodel.loadHierarchy();
	
	testmesh.loadFromAnimatedModel("Contents/Models/meshskin.obj2", g_Animatedmodel);
	

	Trees = Object(&object, &TreeTex, objectTransform, &testMat);
	rockObject = Object(&rockMesh, &BaseTex, glm::scale(objectTransform, glm::vec3(0.5f)), &testMat);
	rockObject2 = Object(&rockMesh, &BaseTex, glm::scale(objectTransform, glm::vec3(0.5f)), &testMat);
	BasePlate = Object(&basemap, &BaseTex, objectTransform, &testMat);
	Playerone = Player(&testmesh, &BaseTex, Player1Transform, &testMat, 100, 1.0f);
	Playertwo = Player(Pose, &BaseTex, glm::translate(Player2Transform, glm::vec3(45, 0, 0)), &testMat, 120, 1.0f);

	River = Object(&river, &test3, objectTransform, &testMat);

	tempability = Ability(&Playerone, 3.0f, 5.0f);
	tempability2 = Ability(&Playertwo, 3.0f, 5.0f);
	playoneskillshot = Skillshot(&Playerone, 3.0f, 15.0f, 0.005f, 10.0f, 0.5f, &rockObject);

	playtwoskillshot = Skillshot(&Playertwo, 3.0f, 15.0f, 0.005f, 10.0f, 0.5f, &rockObject2);

	Playerone.setAttack(&tempability);
	Playerone.setAbility(&playoneskillshot);

	Playertwo.setAttack(&tempability2);
	Playertwo.setAbility(&playtwoskillshot);

	
	
	//std::vector<glm::vec3, std::allocator<glm::vec3>> *temp;


	rockObject.setActive(false);
	glfwGetTime();
	return true;
}

void Engine::shutDown()
{

	object.unload();
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

void Engine::controllerInput(int controller, float speed, Player *player, const float*axes, const unsigned char* buttons, Player* otherplayer)
{
	

	if (controller == 1)
	{
		


		

		
		if ((axes[0] <= -0.3f || axes[0] >= 0.3f) || (axes[1] <= -0.3f || axes[1] >= 0.3f))
		{


			player->setOrientation(-player->getOrientation());

			float tempangle;
			if (controllertype == 4) {
				tempangle = 36 * ((atan2(-axes[0], -axes[1]) * PI) / 2 + 5);
			}
			else if (controllertype == 3) {
				tempangle = 36 * ((atan2(-axes[0], axes[1]) * PI) / 2 + 5);
			}


			glm::vec3 tempdir2 = glm::vec3(glm::sin(glm::radians(tempangle)) * speed, 0, glm::cos(glm::radians(tempangle)) * speed);


			player->setTransform(glm::translate(player->getTransform(), glm::vec3(tempdir2.x, 0, tempdir2.z)));




			player->setOrientation(tempangle);
		}
		
		//SQUARE
		if (GLFW_PRESS == buttons[0]) {
			//std::cout << "SQUARE" << std::endl;
		}
		//X
		if (GLFW_PRESS == buttons[1]) {
			player->skillshotAttack(otherplayer);
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
			player->BaseAttack(otherplayer);
		}
		
	}

}



void Engine::checkAnimation() {
	
	
	if (animation1run) {
		animation1run = runAnimation(animation1, 0.2f);
	}
	else if (animation2run) {
		animation2run = runAnimation(animation2, 0.2f);
	}
	else if (animation3run) {
		animation3run = runAnimation(animation3, 0.2f);
	}
	else if (animation4run) {
		animation4run = runAnimation(animation4, 0.1f);
	}
	else {
		runAnimation(animationidle, 0.05f);
	}
}

double currentFrame;
double lastFrame;
double deltaTime;
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
		//cout <<"DT: " << deltaTime << endl;
		// Start the Dear ImGui frame
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (InputModule::getInstance().isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		double currentTime = glfwGetTime();
		timer = currentTime;
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
		
		if (currentTime - lastTime >= 1.0f)
		{
			
			frames = 0;
			lastTime += 1.0;
		}
		playerInput(skillshotT);

		

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


		Playerone.update();
		Playertwo.update();

		g_Animatedmodel.Update(deltaTime);

		//std::cout << currentTime - lastTime << std::endl;
		_camera->update();
		InputModule::getInstance().update((currentTime - lastTime));
		render();

		

	}
}

void Engine::render()
{
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	//const SA::sAnimatedMesh& AnimMesh = g_Animatedmodel.GetMesh(0);
	//std::cout << "X: "<<AnimMesh.pTransformedVertices[0].x<< "Y: " << AnimMesh.pTransformedVertices[0].y << "z: " << AnimMesh.pTransformedVertices[0].z << std::endl;
	
	//testmesh.loadFromAnimatedModel("Contents/Models/meshskin.obj2", g_Animatedmodel.GetMesh(0));
	
	//testmesh.loadFromVector2("Contents/Models/meshskin.obj", AnimMesh);
	//LUT.Bind3D(12);
	//frameBuffer.clear();
	//frameBuffer.bind();*/
	glEnable(GL_DEPTH_TEST);
	sh2.use();
	sh2.sendUniformMat4("projection", cameraProjection);
	sh2.sendUniformMat4("view", _camera->getLookMatrix());
	g_Animatedmodel.sendToShader(&sh2);
	////Lights here
	first.LoadLight(&sh2);
	second.LoadLight(&sh2);
	//
	//
	////Objects here//
	//Trees.LoadObject(&sh2);
	//BasePlate.LoadObject(&sh2);
	Playerone.LoadObject(&sh2);
	//Playertwo.LoadObject(&sh2);
	//rockObject.LoadObject(&sh2);
	//rockObject2.LoadObject(&sh2);
	//
	sh2.unuse();

	//---------------------------------------------------------
	////TRANSPARENT OBJS HERE
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//sht.use();

	//sht.sendUniformMat4("projection", cameraProjection);
	//sht.sendUniformMat4("view", _camera->getLookMatrix());
	//first.LoadLight(&sht);
	//second.LoadLight(&sht);
	//
	//
	//River.LoadObject(&sht);

	//sht.unuse();
	//glDisable(GL_BLEND);
	//---------------------------------------------------------
	/*frameBuffer.unbind();
	LUTShader.use();
	LUTShader.sendUniformMat4("projection", cameraProjection);
	LUTShader.sendUniformMat4("view", _camera->getLookMatrix());
	LUTShader.sendUniformFloat("uAmount", 1.0f);
	LUTShader.sendUniformFloat("LUTSize", LUT.getSize());
	frameBuffer.bindColorAsTexture(0, 13);
	glDisable(GL_DEPTH_TEST);
	frameBuffer.drawFSQ();
	frameBuffer.unbindTexture(13);
	LUTShader.unuse();

	LUT.unbind3D(12);*/

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

void Engine::playerInput(float t)
{
	

	int axesCount;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
	//std::cout << axesCount << endl;
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

	controllerInput(glfwJoystickPresent(GLFW_JOYSTICK_1), 0.25f, &Playerone, axes, buttons, &Playertwo);
	


	int axesCount2;
	const float *axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount2);
	int count2;
	const unsigned char* buttons2 = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &count2);

	controllerInput(glfwJoystickPresent(GLFW_JOYSTICK_2), 0.25f, &Playertwo, axes2, buttons2, &Playerone);



	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_1))
	{
		_camera = &camera1;
	}
	else if (InputModule::getInstance().isKeyPressed(GLFW_KEY_2))
	{
		_camera = &camera2;
	}

	
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_W))
	{
		//second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y, second.getPosition().z - 0.1f, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		Playerone.setPosition(Playerone.getPositionV3() - glm::vec3(0.0f, 0.0f, 0.1f));
		//animation2run = true;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_S))
	{
		//second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y, second.getPosition().z + 0.1f, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		Playerone.setPosition(Playerone.getPositionV3() + glm::vec3(0.0f, 0.0f, 0.1f));
		//animation3run = true;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_A))
	{
		//second.setPosition(glm::vec4(second.getPosition().x - 0.1f, second.getPosition().y, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		Playerone.setPosition(Playerone.getPositionV3() - glm::vec3(0.1f, 0.0f, 0.0f));
		//animation2run = true;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_D))
	{
		//second.setPosition(glm::vec4(second.getPosition().x + 0.1f, second.getPosition().y, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
		Playerone.setPosition(Playerone.getPositionV3() + glm::vec3(0.1f, 0.0f, 0.0f));
		//animation3run = true;
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_R))
	{
		second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y + 0.1f, second.getPosition().z, second.getPosition().w));
		//Player.setPosition(glm::vec3(second.getPosition()));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_F))
	{
		second.setPosition(glm::vec4(second.getPosition().x, second.getPosition().y - 0.1f, second.getPosition().z, second.getPosition().w));
		
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_I))
	{
		
		Playertwo.setPosition(Playertwo.getPositionV3() - glm::vec3(0.0f, 0.0f, 0.1f));
		
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_K))
	{
		
		Playertwo.setPosition(Playertwo.getPositionV3() + glm::vec3(0.0f, 0.0f, 0.1f));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_J))
	{

		Playertwo.setPosition(Playertwo.getPositionV3() - glm::vec3(0.1f, 0.0f, 0.0f));

	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_L))
	{
		
		Playertwo.setPosition(Playertwo.getPositionV3() + glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_O))
	{

		Playertwo.BaseAttack(&Playerone);
	} 
	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_E))
	{
		Playerone.skillshotAttack(&Playertwo);
	}
}
