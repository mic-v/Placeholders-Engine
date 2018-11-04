#pragma once

// GAME.H
// DOn't do stuff in main
// This will be the main hub . This should really be called the core
// Any major systems that need to interact with one another will occur here.

#include "Engine/Window.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include "Engine/Math/math.h"
#include "Engine/Camera.h"

//#include "SOIL2.h"
//
using namespace plaho;
using namespace graphics;

class Game
{
public:
	~Game();
	static Game& instance();

	void startUp();
	void shutDown();
	void update();
	void render();
	Window* _window;
private:
	Game();

	/***/
	static Game* _instance;
	Camera *_camera;
	std::vector<Camera> cameras;
	Mesh object;
	Shader sh;
	Shader *sh2;
	mat4 cameraTransform;
	mat4 cameraProjection;
	mat4 monkeyTransform;
	unsigned int VBO, VAO;
	unsigned int diffuseMap, specularMap;
	//vec3 position(0, 0, 3);
	//Window
	//unsigned int VBO = GL_NONE;
	//unsigned int VAO = GL_NONE;
	unsigned int shaderProgram = GL_NONE;
	unsigned int vertShader = GL_NONE;
	unsigned int fragShader = GL_NONE;


	// Don't know what to include yet
};