#include "Game.h"

/*
This is the Asssignment 1 Cube Loader stuff. I've been trying to load the monkey
*/

Game* Game::_instance = nullptr;


const float mesh[] = {
	// Vertices start here:
	-1.0f, 	-1.0f, 	-1.0f, 	 // triangle 1, Vertex 1
	-1.0f, 	-1.0f, 	 1.0f, 	 // triangle 1, Vertex 2
	-1.0f, 	 1.0f, 	 1.0f, 	 // triangle 1, Vertex 3
	1.0f, 	 1.0f, 	-1.0f, 	 // triangle 2, Vertex 1
	-1.0f, 	-1.0f, 	-1.0f, 	 // triangle 2, Vertex 2
	-1.0f, 	 1.0f, 	-1.0f, 	 // triangle 2, Vertex 3
	1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	// Colors start here:
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

const char* vertexShaderSource =
"#version 330\n"
"layout(location = 0) in vec3 mesh_position;\n"
"layout(location = 1) in vec3 mesh_color;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"	gl_Position = u_projection * u_view * u_model * vec4(mesh_position, 1.0);\n"
"	color = mesh_color;\n"
"}\n";

const char* fragmentShaderSource =
"#version 330\n"
"in vec3 color;\n"
"out vec4 pixelColor;\n"
"void main() { pixelColor = vec4(color, 1.0f); }\n";


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

	monkey = Mesh();
	monkey.loadFromFile("Contents/Map2.obj");
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

	glBindVertexArray(monkey.VAO);
	glDrawArrays(GL_TRIANGLES, 0, monkey.getNumVertices());

	glBindVertexArray(0);
	glUseProgram(0);

	_window->poll();
}
