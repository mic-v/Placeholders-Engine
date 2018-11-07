#include "Engine.h"

/*
This is the Asssignment 1 Cube Loader stuff. I've been trying to load the monkey
*/

Engine* Engine::_instance = nullptr;







float toRadii(float degrees)
{
	return degrees * (PI / 180.0f);
	
}

void Engine::cameraMovement() {
	while (true)
	{
		if (_window->isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		if (_window->isKeyPressed(GLFW_KEY_SPACE))
		{
			_camera->moveUp();
		}

		if (_window->isKeyPressed(GLFW_KEY_1))
		{
			_camera = &cameras[0];
			_window->setCamera(*_camera);
		}
		else if (_window->isKeyPressed(GLFW_KEY_2))
		{
			_camera = &cameras[1];
			_window->setCamera(*_camera);
		}
		else if (_window->isKeyPressed(GLFW_KEY_3))
		{
			_camera = &cameras[2];
			_window->setCamera(*_camera);
		}
		else if (_window->isKeyPressed(GLFW_KEY_4))
		{
			_camera = &cameras[3];
			_window->setCamera(*_camera);
		}
		else if (_window->isKeyPressed(GLFW_KEY_5))
		{
			_camera = &cameras[4];
			_window->setCamera(*_camera);
		}

		_window->clear();
		_window->update();
		_camera->update();


		cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);
		cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));

		

		render();
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
	
	_window = new Window("Plaho", 1280, 720);
	cameras.push_back(Camera(vec3(0.0, 19.0f, 13.0f)));
	cameras[0].setYDirection(-56.f);
	cameras.push_back(Camera(vec3(0.0, 5.0f, 20.0f)));
	cameras.push_back(Camera(vec3(0.0, 10.0f, 10.0f)));
	cameras.push_back(Camera(vec3(0.0, 5.0f, 5.0f)));
	cameras.push_back(Camera(vec3(20.0, 0.0f, 30.0f)));
	_camera = &cameras[0];

	_window->setCamera(*_camera);

	cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));
	cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);
	glEnable(GL_DEPTH_TEST);
	sh = Shader("Contents/Shaders/texture.vs", "Contents/Shaders/texture.fs");

	object = Mesh();
	object.loadFromFile("Contents/Models/Map2.obj");

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

void Engine::update()
{
	cameraMovement();
}

void Engine::render()
{
	
	
	sh.use();
	sh.sendUniformMat4("model", cameraTransform);
	sh.sendUniformMat4("projection", cameraProjection);
	sh.sendUniformMat4("view", _camera->getLookMatrix());
	sh.sendUniformVec4("LightPosition", vec4(4.0f, 0, 0, 1.0f));
	sh.sendUniformVec3("LightAmbient",  vec3(0, 0, 0.15f));
	sh.sendUniformVec3("LightDiffuse",  vec3(0.7f, 0.5f, 0.2f));
	sh.sendUniformVec3("LightSpecular", vec3(1.0f, 0.1f, 0.1f));
	sh.sendUniformFloat("LightSpecularExponent", 1.0f);
	sh.sendUniformFloat("Attenuation_Constant", 0.0f);
	sh.sendUniformFloat("Attenuation_Linear", 0.1f);
	sh.sendUniformFloat("Attenuation_Quadratic", 0.01f);
	test.Bind(0);

	glBindVertexArray(object.VAO);
	glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices());

	glBindVertexArray(0);
	
	test.Unbind();
	sh.unuse();
	_window->poll();
}
