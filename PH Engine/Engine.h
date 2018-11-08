#pragma once

// GAME.H
// DOn't do stuff in main
// This will be the main hub . This should really be called the core
// Any major systems that need to interact with one another will occur here.

#include "Engine/Window.h"
#include "Engine/Texture.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include "Engine/Math/math.h"
#include "Engine/Camera.h"
#include "Engine/Light.h"

//#include "SOIL2.h"
//
using namespace plaho;
using namespace graphics;

class Engine
{
public:
	~Engine();
	static Engine& instance();

	void startUp();
	void shutDown();
	void update();
	void render();
	void cameraMovement();
	Window* _window;
private:
	Engine();

	/***/
	static Engine* _instance;
	Camera *_camera;
	std::vector<Camera> cameras;
	Mesh object;
	Shader sh;
	Shader sh2;
	Light first;
	Light second;
	Light third;
	Texture test;
	mat4 objectTransform;
	mat4 cameraProjection;
	
	unsigned int VBO, VAO;
	unsigned int diffuseMap, specularMap;
	
	unsigned int shaderProgram = GL_NONE;
	unsigned int vertShader = GL_NONE;
	unsigned int fragShader = GL_NONE;


	// Don't know what to include yet
};