#include "Game.h"

/*
This is the Asssignment 1 Cube Loader stuff. I've been trying to load the monkey
*/

Game* Game::_instance = nullptr;







float toRadii(float degrees)
{
	return degrees * (PI / 180.0f);
	
}




Game::Game()
{
}

Game::~Game()
{
}

/*
	This is the Singleton Pattern. Read more here:
	http://gameprogrammingpatterns.com/singleton.html
	Essentially, make sures there is only one instance of a certain class
	I wanted to practice it so I decided to use this pattern for Game. You don't have to follow thi
	for every class
*/
Game & Game::instance()
{
	// TODO: insert return statement here
	if (_instance == nullptr)
	{
		_instance = new Game();
		return *_instance;
	}
	else
	{
		return *_instance;
	}
}
//
void Game::startUp()
{
	_window = new Window("Plaho", 1280, 720);
	cameras.push_back(Camera(vec3(0.0, 10.0f, 30.0f)));
	cameras.push_back(Camera(vec3(0.0, 5.0f, 20.0f)));
	cameras.push_back(Camera(vec3(0.0, 10.0f, 10.0f)));
	cameras.push_back(Camera(vec3(0.0, 5.0f, 5.0f)));
	cameras.push_back(Camera(vec3(20.0, 0.0f, 30.0f)));
	_camera = &cameras[0];

	_window->setCamera(*_camera);

	cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));
	cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);
	
	sh = Shader("Shaders/passthrough.vs", "Shaders/passthrough.fs");

	object = Mesh();
	object.loadFromFile("Contents/Map2.obj");


	

	
}

void Game::shutDown()
{
	delete _window;
}

void Game::update()
{
	while (true)
	{
		if (_window->isKeyPressed(GLFW_KEY_ESCAPE))
			break;

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

void Game::render()
{
	sh.use();
	sh.setMat4("model", cameraTransform);
	sh.setMat4("projection", cameraProjection);
	sh.setMat4("view", _camera->getLookMatrix());

	glBindVertexArray(object.VAO);
	glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices());

	glBindVertexArray(0);
	glUseProgram(0);

	_window->poll();
}
