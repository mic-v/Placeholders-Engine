#include "Window.h"

namespace plaho {
	namespace graphics
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		/*
			@Constructor for the window class
			@param name The title for the window
			@param width The width/x of the window
			@param height The height/y of the window
		
		*/

		Window::Window(const char* name, int width, int height)
		{
			_name = name;
			_width = width;
			_height = height;
			if (!init())
			{
				glfwTerminate();
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		/*
			initailizes the Window class
		*/

		bool Window::init()
		{
			if (glfwInit() == NULL)
			{
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
			if (_window == NULL)
			{
				std::cout << "Failed to create a GLFW window" << std::endl;
				glfwTerminate();
				return false;
			}

			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			glfwMakeContextCurrent(_window);

			// glad: load all OpenGL function pointers
// ---------------------------------------
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}

			return true;
		}

		/*
			 Checks if the window should close
			 @return true if the window should close
		*/

		bool Window::closed() const
		{
			return glfwWindowShouldClose(_window);
		}


		/*
			Checks if the window should close
			@return true if the window should close
		*/
		void Window::update()
		{
			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		/*
			Checks if the window should close
			@return true if the window should close
		*/
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}

}
