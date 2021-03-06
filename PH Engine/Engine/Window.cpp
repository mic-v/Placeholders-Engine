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
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		void processInput(GLFWwindow * window);
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
			firstMouse = true;
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
			_camera = nullptr;
			_mx = 1280.f / 2.f;
			_my = 720.f / 2.f;
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

			/*
				COMMENT

			*/
			glfwMakeContextCurrent(_window);
			glfwSetWindowUserPointer(_window, this);
			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			glfwSetWindowSizeCallback(_window, framebuffer_size_callback);
			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, mouse_callback);
			glfwSetCursorPosCallback(_window, cursor_position_callback);
			//glfwSetJoystickCallback(joystick_callback);

			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// glad: load all OpenGL function pointers
			// ---------------------------------------
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}

			glEnable(GL_DEPTH_TEST);

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
			processInput(_window);
		}

		void Window::poll()
		{

		}

		void Window::setCamera(Camera & camera)
		{
			_camera = &camera;
			_camera->update();
		}

		/*
			Checks if the window should close
			@return true if the window should close
		*/
		void Window::clear() const
		{
		}

		/*
			COMMENT
			
		*/

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		/*
			COMMENT
		
		*/


		bool Window::isKeyPressed(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
			{
				return false;
			}

			return _keys[keycode];
		}

		/*
			COMMENT

		*/


		bool Window::isMouseButtonPressed(unsigned int button)
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
			}
			return _mouseButtons[button];
		}

		/*
			COMMENT

		*/


		void Window::getMousePos()
		{
			std::cout << _mx << " " << _my << std::endl;
		}

		/*
			COMMENT	
		
		*/

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->_keys[key] = action != GLFW_RELEASE;
		}

		/*
			COMMENT
		
		*/

		void mouse_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_mouseButtons[button] = action != GLFW_RELEASE;
		}

		/*
			COMMENT
		
		*/

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->firstMouse)
			{
				win->_mx = xpos;
				win->_my = ypos;
				win->firstMouse = false;
			}
			float xoff = xpos - win->_mx;
			float yoff = win->_my - ypos;

			win->_mx = xpos;
			win->_my = ypos;
			win->_camera->processMouseMovement(xoff, yoff);
		}
		void processInput(GLFWwindow * window)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			//	win->_camera->processKeyboard(FORWARD, win->deltaTime);
			//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			//	win->_camera->processKeyboard(BACKWARD, win->deltaTime);
			//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			//	win->_camera->processKeyboard(LEFT, win->deltaTime);
			//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			//	win->_camera->processKeyboard(RIGHT, win->deltaTime);
		}
		void joystick_callback(int joy, int event)
		{
			if (event == GLFW_CONNECTED)
			{
				// The joystick was connected
			}
			else if (event == GLFW_DISCONNECTED)
			{
				// The joystick was disconnected
			}
		}
	}

}
