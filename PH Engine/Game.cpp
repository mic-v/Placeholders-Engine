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
	object.unload();
	test.Unload();
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

	glEnable(GL_DEPTH_TEST);

	object = Mesh();

	if (!passthrough.Load("Shaders/passthrough.vs", "Shaders/passthrough.fs")) {
		cout << "Shaders failed to load" << endl;
		system("Pause");
		exit(0);
	}


	if (!object.loadFromFile("Contents/Map2.obj")) {
		cout << "Object failed to load" << endl;
		system("Pause");
		exit(0);
	}

	if (!test.LoadTexture("Contents/container2.png")) {
		cout << "Texture failed to load" << endl;
		system("Pause");
		exit(0);
	}




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

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//std::cout << "MYSHIT1 " << cameraTransform.rawdata() << std::endl;
	//std::cout << "MYSHIT2 " << _camera->getLookMatrix().rawdata() << std::endl;
	//std::cout << "MYSHIT3 " << cameraProjection.rawdata() << std::endl;


	passthrough.sendUniformMat4("model", cameraTransform, false);
	passthrough.sendUniformMat4("view", _camera->getLookMatrix(), false);
	passthrough.sendUniformMat4("projection", cameraProjection, false);
	

	glBindVertexArray(object.VAO);
	glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices());
	glBindVertexArray(0);
	
	passthrough.Unbind();
	//test.Bind(0);
	_window->poll();
}
