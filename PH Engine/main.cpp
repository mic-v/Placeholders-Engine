////
////
//// Placeholders Engine
//// - By Placeholders Studio
//// - Version 1.0 Beta
////
////

/*

	Explanations:
	// Mesh comes from the Emillian series. Don't ask me about that

	// Camera and Shader class comes from https://learnopengl.com/Getting-started/Camera
	https://learnopengl.com/Getting-started/Shaders
	We might need to completely remove this and make our own shader class, but for now they work
	and we need to make sure important stuff works.
	// Camera is FPS, WASD, mouse to aim around, etc.

	// Using a picture library called stbi_image https://github.com/nothings/stb/blob/master/stb_image.h
	to load in pictures for texture

	//Mat4 class is created by Michael. VecX classes provided by First year Tutorial which we might need to create our own.
	Mat4 class has no new stuff

	//We are using GLFW and not GLUT. What's the difference? None, most of what I saw in Emilians base projects for assignments
	they do the similar thing. It's just that there are a bunch of resources like learnopegnl or cherno that uses
	glfw compare to GLUT. I also emaied emillian and he said it was fine.

	//GLAD just tells the compilar what version of OPENGL we are using

	//Window class wraps the functions of GLFW. It setups the important glfw callbacks for input, the color of the screen, etc.

	//Game is where we do the heavy initializing stuff. We could further to have another class that handles what objects load in
	when we start play but initializeGame() works for now.

	//Window::poll() is just way to swap frames every millisecond to make sure that the next image comes up.

	//.vs for vertex shader, .fs is for fragment shader It doesn't really matter, it could be .vert and/or .frag. Doesn't really matter.
	Ask me any other questions
*/

// test

#include <iostream>
#include "Engine.h"



#include "Engine/Math/math.h"
#include "Engine/Shader.h"
using namespace plaho;
using namespace graphics;

int main()
{
	Engine::instance().startUp();
	//float deltaTime = 0.0f;
	//float lastFrame = 0.0f;
	//while (Engine::instance().isActive)
	//{
	//	float currentFrame = glfwGetTime();
	//	deltaTime = currentFrame - lastFrame;
	//	lastFrame = currentFrame;
	//	Engine::instance().update(deltaTime);
	//	Engine::instance().render();
	//}
	Engine::instance().update(50.0f);
	Engine::instance().shutDown();
}
