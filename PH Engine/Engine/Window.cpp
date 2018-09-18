#include "Window.h"

namespace plaho {
	namespace graphics
	{
		bool Window::_keys[1024];
		bool Window::_mouseButtons[MAX_BUTTONS];
		double Window::_mx;
		double Window::_my;

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_callback(GLFWwindow* window, int button, int action, int mods);
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

			for (int i = 0; i < MAX_KEYS; i++)
			{
				_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				_mouseButtons[i] = false;
			}

			//Window::INSTANCE = this;
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
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
			if (_window == NULL)
			{
				std::cout << "Failed to create a GLFW window" << std::endl;
				glfwTerminate();
				return false;
			}

			glfwMakeContextCurrent(_window);
			glfwSetWindowUserPointer(_window, this);
			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			glfwSetWindowSizeCallback(_window, framebuffer_size_callback);
			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, mouse_callback);

			// glad: load all OpenGL function pointers
// ---------------------------------------
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return false;
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
			//std::cout << _width << " " << _height << std::endl;
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_mouseButtons[button] = action != GLFW_RELEASE;
		}


		bool Window::isKeyPressed(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
			{
				return false;
			}

			return _keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button)
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
			}
			return _mouseButtons[button];
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
