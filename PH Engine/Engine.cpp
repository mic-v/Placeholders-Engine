#include "Engine.h"

/*
This is the Asssignment 1 Cube Loader stuff. I've been trying to load the monkey
*/

Engine* Engine::_instance = nullptr;


void Engine::cameraMovement()
{

	if (_window->isKeyPressed(GLFW_KEY_1))
	{
		_camera = &camera1;
		_window->setCamera(*_camera);
	}
	else if (_window->isKeyPressed(GLFW_KEY_2))
	{
		_camera = &camera2;
		_window->setCamera(*_camera);
	}

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present == 1)
	{
		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		int count;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

		std::cout << "Right stick X axis: " << axes[2] << std::endl;
		std::cout << "Right stick Y axis: " << axes[3] << std::endl;
		transform = glm::translate(transform, glm::vec3(axes[0] * 0.03, 0.f, 0.f));
		transform = glm::translate(transform, glm::vec3(0.0f, 0.f, -axes[1] * 0.03));
		transform = glm::rotate(transform, glm::radians(axes[2]), glm::vec3(0.0f, 1.0f, 0.0f));
		//transform = glm::translate(transform, glm::vec3(0.1f, 0.f, 0.0f));
		//std::cout << glm::to_string(transform) << std::endl;
		////position += glm::vec3(axes[0] / 2, 0, axes[1]);
		//glm::mat4 temp = glm::translate(temp, glm::vec3(0.1f, 0.0f, 0.0f));
		//transform += temp;
		//std::cout << glm::to_string(transform) << std::endl;
	}


}


Engine::Engine()
{
}

Engine::~Engine()
{
	sh.unload();
	object.unload();
	test.Unload();

}

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
void Engine::startUp()
{
	isActive = true;
	_window = new Window("Plaho", 1280, 720);
	//_camera = nullptr;
	camera1 = FPSCamera(glm::vec3(0.0f, 5.0f, 13.0f));
	camera2 = Camera(glm::vec3(0.0, 11.0f, 5.0f));
	camera2.setYDirection(-60.f);
	_camera = &camera2;

	_window->setCamera(*_camera);

	position = glm::vec3(-4.0f, 2.0f, 0.0f);
	objectTransform = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	objectTransform = glm::translate(objectTransform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::translate(transform, position);
	cameraProjection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);

	glEnable(GL_DEPTH_TEST);
	sh = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/texture.fs");
	sh2 = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/texture.fs");
	sh3 = Shader("Contents/Shaders/passthrough.vs", "Contents/Shaders/passthrough.fs");
	object = Mesh();
	object.loadFromFile("Contents/Models/Map2.obj");
	object2 = Mesh();
	object2.loadFromFile("Contents/Models/Cube.obj");
	first = Light(&sh, glm::vec4(4.0f, 0.0f, 0, 1.0f), glm::vec3(0.0f, 0.0f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(1.0f, 0.1f, 0.1f));
	second = Light(&sh2, glm::vec4(0.0f, 5.0f, 0, 1.0f), glm::vec3(0.1f, 0.1f, 0.15f), glm::vec3(0.7f, 0.5f, 0.2f), glm::vec3(1.0f, 0.1f, 0.1f));
	
	
	if (!test.LoadTexture("Contents/Textures/container2.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}


}

void Engine::shutDown()
{
	delete _window;
}

void Engine::update(float dt)
{
	while (true)
	{
		if (_window->isKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}


		cameraMovement();
		_window->clear();
		_window->update();
		_camera->update();

		render();
	}

}

void Engine::render()
{

	sh2.use();
	sh2.sendUniformMat4("projection", cameraProjection);
	sh2.sendUniformMat4("view", _camera->getLookMatrix());
	second.LoadLight();
	
	test.Bind(0);

	glBindVertexArray(object.VAO);
	sh2.sendUniformMat4("model", objectTransform);
	glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices());
	glBindVertexArray(object2.VAO);
	sh2.sendUniformMat4("model", transform);
	glDrawArrays(GL_TRIANGLES, 0, object2.getNumVertices());

	glBindVertexArray(0);

	test.Unbind();
	sh2.unuse();
	_window->poll();
}