#include <iostream>

#include "Engine/Window.h"
#include "Engine/Math/math.h"
using namespace plaho;
using namespace graphics;

int main()
{
	Window window("Plaho", 1280, 720);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vec3 vec1(1, 2, 3);
	//vec3 vec2(0, 1, 3);
	//vec2 *= 2;
	//std::cout << vec2 << std::endl;
	mat44 mat1(2);
	mat44 mat2(2);
	mat1 *= 2;
	std::cout << mat1 << std::endl;
	while (!window.closed())
	{
		window.clear();
		
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "PRESSED!" << std::endl;
		}
		//window.getMousePos();

		window.update();

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
	}

	return 0;
}