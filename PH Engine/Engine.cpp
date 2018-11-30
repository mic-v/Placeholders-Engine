#include "Engine.h"
#include <glm/gtc/constants.hpp>

#define NAME "Projite"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

Engine* Engine::_instance = nullptr;
float currentAngle = 135.0f;


/*
	This is the Singleton Pattern. Read more here:
	http://Engineprogrammingpatterns.com/singleton.html
	Essentially, make sures there is only one instance of a certain class
	I wanted to practice it so I decided to use this pattern for Engine. You don't have to follow thi
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

	glEnable(GL_DEPTH_TEST);

	//PHYSICS
	//bullet here

	isActive = true;
	//_camera = nullptr;
	camera1 = FPSCamera(glm::vec3(0.0f, 5.0f, 30.0f));
	camera2 = Camera(glm::vec3(0.0, 11.0f, 5.0f));
	camera2.setYDirection(-60.f);
	_camera = &camera2;


	position = glm::vec3(-4.0f, 0.1f, 0.0f);
	objectTransform = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	objectTransform = glm::translate(objectTransform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 0.25f));
	cameraProjection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);

	sh = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/texture.fs");
	sh2 = Shader("Contents/Shaders/textureanim.vs", "Contents/Shaders/texture.fs");
	sh3 = Shader("Contents/Shaders/passthrough.vs", "Contents/Shaders/passthrough.fs");
	object.loadFromFile("Contents/Models/Map2.obj");
	object2.loadFromFile("Contents/Models/Attack/frame1.obj");
	object2.loadSecondFromFile("Contents/Models/Attack/frame2.obj");
	//Animtest.loadFromFile("Contents/Models/Attack/frame1.obj");
//	Animtest.loadSecondFromFile("Contents/Models/Attack/frame1.obj");



	attackframe1.loadFromFile("Contents/Models/Attack/frame1.obj");
	attackframe1.loadSecondFromFile("Contents/Models/Attack/frame2.obj");

	attackframe2.loadFromFile("Contents/Models/Attack/frame2.obj");
	attackframe2.loadSecondFromFile("Contents/Models/Attack/frame3.obj");

	attackframe3.loadFromFile("Contents/Models/Attack/frame3.obj");
	attackframe3.loadSecondFromFile("Contents/Models/Attack/frame4.obj");

	attackframe4.loadFromFile("Contents/Models/Attack/frame4.obj");
	attackframe4.loadSecondFromFile("Contents/Models/Attack/frame5.obj");

	attackframe5.loadFromFile("Contents/Models/Attack/frame5.obj");
	attackframe5.loadSecondFromFile("Contents/Models/Attack/frame4.obj");

	attackframe6.loadFromFile("Contents/Models/Attack/frame4.obj");
	attackframe6.loadSecondFromFile("Contents/Models/Attack/frame3.obj");

	attackframe7.loadFromFile("Contents/Models/Attack/frame3.obj");
	attackframe7.loadSecondFromFile("Contents/Models/Attack/frame2.obj");

	attackframe8.loadFromFile("Contents/Models/Attack/frame2.obj");
	attackframe8.loadSecondFromFile("Contents/Models/Attack/frame1.obj");

	attackframe9.loadFromFile("Contents/Models/Attack/frame1.obj");
	attackframe9.loadSecondFromFile("Contents/Models/Attack/frame1.obj");

	animation1.push_back(&attackframe1);
	animation1.push_back(&attackframe2);
	animation1.push_back(&attackframe3);
	animation1.push_back(&attackframe4);
	animation1.push_back(&attackframe5);
	animation1.push_back(&attackframe6);
	animation1.push_back(&attackframe7);
	animation1.push_back(&attackframe8);
	animation1.push_back(&attackframe9);

	Pose = &attackframe1;

	//obj.push_back(new Entity(&sh2, "Contents/Models/untitled.obj", glm::vec3(-4.0f, 0.1f, 0.0f)));
	//obj.push_back(new Entity(&sh2, "Contents/Models/untitled.obj", glm::vec3(-2.0f, 0.1f, 0.0f)));
	//obj.push_back(new Entity(&sh2, "Contents/Models/untitled.obj", glm::vec3(0.0f, 0.1f, 0.0f)));
	//obj.push_back(new Entity(&sh2, "Contents/Models/untitled.obj", glm::vec3(2.0f, 0.1f, 0.0f)));
	//obj.push_back(new Entity(&sh2, "Contents/Models/untitled.obj", glm::vec3(4.0f, 0.1f, 0.0f)));

	first = Light(&sh2, glm::vec4(4.0f, 5.0f, 0, 1.0f), glm::vec3(0.0f, 0.0f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(1.0f, 0.1f, 0.1f));
	second = Light(&sh2, glm::vec4(0.0f, 5.0f, 0, 1.0f), glm::vec3(0.1f, 0.1f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(1.0f, 0.1f, 0.1f));
	
	
	if (!test.LoadTexture("Contents/Textures/container2.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}

	return true;
}

void Engine::shutDown()
{

	sh.unload();
	object.unload();
	test.Unload();


	InputModule::getInstance().shutDown();
	GLFWwindow *window = glfwGetCurrentContext();
	glfwDestroyWindow(window);

	glfwTerminate();
}

void Engine::runGame()
{
	double lastTime = glfwGetTime();
	double deltaTime = 0.0;
	int frames = 0;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(glfwGetCurrentContext()))
	{
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

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		double currentTime = glfwGetTime();
		frames++;
		
		if (currentTime - lastTime >= 1.0f)
		{
			//std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			lastTime += 1.0;
		}
		playerInput();
		if (animation1run) {
			if (currentanimframe < animation1.size()) {
				Pose = animation1[currentanimframe];
				currentlerpparam += 0.2f;

			}
			else if (currentanimframe >= animation1.size()) {
				animation1run = false;
				currentanimframe = 0;
			}
			if (currentlerpparam >= 1.0f) {
				currentanimframe++;
				currentlerpparam = 0.0f;
			}
		}
		for (int i = 0; i < obj.size(); i++)
		{
			obj[i]->update(ImGui::GetIO().Framerate);
		}

		_camera->update();
		InputModule::getInstance().update(currentTime - lastTime);
		render();

		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
}

void Engine::render()
{
	sh2.use();
	sh2.sendUniformMat4("projection", cameraProjection);
	sh2.sendUniformMat4("view", _camera->getLookMatrix());
	
	second.LoadLight();
	first.LoadLight();
	
	test.Bind(0);

	//Battlefield
	glBindVertexArray(object.VAO);
	sh2.sendUniformFloat("lerpParam", 0);
	sh2.sendUniformMat4("model", objectTransform);
	
	glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices());

	//for (int i = 0; i < obj.size(); i++)
	//{
	//	obj[i]->draw();
	//}
	//Entity
	glBindVertexArray(Pose->VAO);
	sh2.sendUniformMat4("model", transform);
	sh2.sendUniformFloat("lerpParam", currentlerpparam);
	glDrawArrays(GL_TRIANGLES, 0, Pose->getNumVertices());
	//glBindVertexArray(obj[0]->getMesh().VAO);
	//obj[0]->getShader().sendUniformMat4("model", obj[0]->getMatrixPosition());
	//glDrawArrays(GL_TRIANGLES, 0, obj[0]->getMesh().getNumVertices());


	glBindVertexArray(0);
	test.Unbind();
	sh2.unuse();
	
	sh.use();
	test.Bind(0);
	//glBindVertexArray(Animtest.VAO);
	sh.sendUniformMat4("model", transform);
	sh.sendUniformFloat("lerpParam", 1.0f);
	//glDrawArrays(GL_TRIANGLES, 0, Animtest.getNumVertices());

	glBindVertexArray(0);
	test.Unbind();
	sh.unuse();



	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(glfwGetCurrentContext());
	glfwPollEvents();
}

void Engine::playerInput()
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present == 1)
	{
		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		int count;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

		if (axes[2] != 0.0f && axes[3] != 0.0f)
		{
			transform = glm::rotate(transform, glm::radians(-currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			//glm::vec3 temp = glm::rotateY(glm::vec3(axes[0] * 0.10f, 0.f, -axes[1] * 0.10f), glm::radians(180.0f));
			//transform = glm::translate(transform, temp);
			transform = glm::translate(transform, glm::vec3(axes[0] * 0.10f, 0.f, -axes[1] * 0.10f));
			if (axes[3] < 0.0f && axes[2] < 0.0f)
				currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 180.0f + 90.0f;
			else if (axes[2] < 0.0f)
				currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 180.0f + 90.0f;
			else if (axes[3] < 0.0f)
				currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 360.0f + 90.0f;
			else if (axes[3] && axes[2] == 0.0f)
				currentAngle = 0.0f + 90.0f;
			else
				currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 90.0f;

			transform = glm::rotate(transform, glm::radians(currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			//currentAngle = glm::atan(axes[3] / axes[2]);
		}
		else
		{
			//std::cout << "yeet" << std::endl;
			transform = glm::rotate(transform, glm::radians(-currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
/*			glm::vec3 temp = glm::rotateY(glm::vec3(axes[0] * 0.10f, 0.f, -axes[1] * 0.10f), glm::radians(180.0f));
			transform = glm::translate(transform, temp)*/;
			transform = glm::translate(transform, glm::vec3(axes[0] * 0.10f, 0.f, -axes[1] * 0.10f));

			//if (axes[3] < 0.0f && axes[2] < 0.0f)
			//	currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 180.0f;
			//else if (axes[2] < 0.0f)
			//	currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 180.0f;
			//else if (axes[3] < 0.0f)
			//	currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f) + 360.0f;
			//else if (axes[3] && axes[2] == 0.0f)
			//	currentAngle = 0.0f;
			//else
			//	currentAngle = glm::atan(axes[3] / axes[2]) * (180.0f / 3.14159265358979323846f);

			transform = glm::rotate(transform, glm::radians(currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		std::cout << "x: " << axes[2] << " y: " << axes[3] << std::endl;
		std::cout << currentAngle << std::endl;
		//transform = glm::translate(transform, glm::vec3(0.0f, 0.f, -axes[1] * 0.03 ));
		//float bangle = axes[3] / axes[2];
		glm::vec2 anglevec(axes[2], axes[3]);

		//std::cout << "x: " << axes[2] << "y: " << axes[3] << " angle : " << glm::atan(axes[3]/axes[2]) * (180.0f / 3.14159265) <<  std::endl;
	}

	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_1))
	{
		_camera = &camera1;
	}
	else if (InputModule::getInstance().isKeyPressed(GLFW_KEY_2))
	{
		_camera = &camera2;
	}

	if (InputModule::getInstance().isKeyPressed(GLFW_KEY_D))
	{
		//obj[0]->translate(glm::vec3(0.1f, 0.0f, 0.0f));
		//runAnimation(animation1);
		animation1run = true;
	}


}

void Engine::runAnimation(std::vector<Mesh*> poselist)
{
	
	
	
}
