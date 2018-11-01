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
#include "Game.h"



#include "Engine/Math/math.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
using namespace plaho;
using namespace graphics;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char *path);



int main()
{
	Game::instance().startUp();
	Game::instance().update();
	Game::instance().shutDown();
}

/*
	Above is the good shit, its clean
	Below is the old stuff
*/


//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
//vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
//vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
//
//Camera camera(cameraPos);
//
//bool firstMouse = true;
//float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0f / 2.0;
//float fov = 45.0f;
//
//// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;
//
///*
//	Need to make a math utilities header file
//	Reminder for me or someone else to do it
//	- Michael
//*/
//
//float toRadii3(float degrees)
//{
//	return degrees * (PI / 180.0f);
//}
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile our shader zprogram
//	// ------------------------------------
//	Shader ourShader("Shaders/4.2.texture.vs", "Shaders/4.2.texture.fs");
//	
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//	// world space positions of our cubes
//	vec3 cubePositions[] = {
//		vec3(0.0f,  0.0f,  0.0f),
//		vec3(2.0f,  5.0f, -15.0f),
//		vec3(-1.5f, -2.2f, -2.5f),
//		vec3(-3.8f, -2.0f, -12.3f),
//		vec3(2.4f, -0.4f, -3.5f),
//		vec3(-1.7f,  3.0f, -7.5f),
//		vec3(1.3f, -2.0f, -2.5f),
//		vec3(1.5f,  2.0f, -2.5f),
//		vec3(1.5f,  0.2f, -1.5f),
//		vec3(-1.3f,  1.0f, -1.5f)
//	};
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// texture coord attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//
//	// load and create a texture 
//	// -------------------------
//	std::string my_str = "container2.png";
//	unsigned int diffuseMap = loadTexture(my_str.c_str());
//	std::string my_str2 = "container2_specular.png";
//	unsigned int specularMap = loadTexture(my_str2.c_str());
//
//	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//	// -------------------------------------------------------------------------------------------
//	ourShader.use();
//	ourShader.setInt("texture1", 0);
//	ourShader.setInt("texture2", 1);
//
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// bind textures on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, specularMap);
//
//		// activate shader
//		ourShader.use();
//
//		// pass projection matrix to shader (note that in this case it could change every frame)
//		//mat44 projection = mat44::perspective(45, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		//ourShader.setMat4("projection", projection);
//		//// camera/view transformation
//		//mat44 view = mat44::lookAt2(camera.position, camera.position + camera.front, camera.up);
//		////std::cout << view << std::endl;
//		//ourShader.setMat4("view", view);
//		mat4 projection = mat4::perspective(toRadii3(45), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		ourShader.setMat4("projection", projection);
//
//		mat4 view = camera.getLookMatrix3();
//		ourShader.setMat4("view", view);
//
//		// render boxes
//		glBindVertexArray(VAO);
//
//		for (int i = 0; i < 10; i++)
//		{
//			mat4 model = mat4::translation(cubePositions[i]);
//			//mat44 model = mat44::identity();
//			//model = mat44::translation(cubePositions[i]);
//			//float angle = 20.0f * i;
//			//model = mat44::rotation(model,angle, vec3(1.0f, 0.3f, 0.5f));
//			ourShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.processKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.processKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.processKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.processKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.1f; // change this value to your liking
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	camera.processMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if (fov >= 1.0f && fov <= 45.0f)
//		fov -= yoffset;
//	if (fov <= 1.0f)
//		fov = 1.0f;
//	if (fov >= 45.0f)
//		fov = 45.0f;
//}
