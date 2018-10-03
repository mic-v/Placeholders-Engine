#pragma once

// GAME.H
// DOn't do stuff in main
// This will be the main hub . This should really be called the core
// Any major systems that need to interact with one another will occur here.

#include "Engine/Window.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"

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

private:
	Game();

	/***/	
	static Game* instance_;
	Window* window_;

	Mesh monkey;
	Shader program;
	//Window
	

	// Don't know what to include yet

};