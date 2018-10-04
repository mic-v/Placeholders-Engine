#include "Game.h"

Game* Game::instance_ = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

Game & Game::instance()
{
	// TODO: insert return statement here
	if (instance_ == nullptr)
	{
		instance_ = new Game();
		return *instance_;
	}
	else
	{
		return *instance_;
	}
}

void Game::startUp()
{
	window_ = new Window("Plaho", 1280, 720);

	//Shader program("Shaders/passthrough.vs","Shaders/passthrough.fs");
	//monkey.loadFromFile("Monkey.obj");
}

void Game::shutDown()
{
	delete window_;
}

void Game::update()
{
	while (true)
	{
		window_->clear();
		if (window_->isKeyPressed(GLFW_KEY_ESCAPE))
			break;
		window_->update();

		render();
	}
}

void Game::render()
{
	window_->poll();
}
