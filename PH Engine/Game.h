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
#include "Engine/stb_image.h"

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
	void test();

private:
	Game();

	/***/	
	static Game* instance_;
	Window* window_;

	Mesh monkey;
	Shader sh;
	Shader *sh2;
	mat4 cameraTransform;
	mat4 cameraProjection;
	mat4 monkeyTransform;
	unsigned int VBO, VAO;
	unsigned int diffuseMap, specularMap;
	//vec3 position(0, 0, 3);
	Camera *camera;
	//Window
	

	// Don't know what to include yet

};