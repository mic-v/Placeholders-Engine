#include <iostream>

#include "Engine/Window.h"
using namespace plaho;
using namespace graphics;

int main()
{
	Window window("Plaho", 1280, 720);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed())
	{
		window.clear();
		
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "PRESSED!" << std::endl;
		}

		window.update();

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
	}

	return 0;
}