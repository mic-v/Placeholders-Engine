#include "InputModule.h"
#include <iostream>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

namespace plaho
{
	namespace module
	{
		InputModule & InputModule::getInstance()
		{
			static InputModule* instance = nullptr;
			if (instance == nullptr)
			{
				instance = new InputModule();
				return *instance;
			}
			return *instance;
		}

		void InputModule::startUp()
		{
			glfwSetWindowUserPointer(glfwGetCurrentContext(), this);


			glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
			glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_callback);
			glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);

			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			_lastX = 0; _lastY = 0;
			_offsetX = 0; _offsetY = 0;

			for (int i = 0; i < MAX_KEYS; i++)
			{
				_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				_mouseButtons[i] = false;
			}
		}

		void InputModule::update(float dt)
		{
			if (isKeyPressed(GLFW_KEY_1))
			{
				std::cout << "yes you pressed it" << std::endl;
			}
		}

		void InputModule::shutDown()
		{
		}

		bool InputModule::isKeyPressed(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
			{
				return false;
			}

			return _keys[keycode];
		}

		bool InputModule::isMouseButtonPressed(unsigned int button)
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
			}
			return _mouseButtons[button];
		}

		glm::vec2 InputModule::getMousePos()
		{
			return glm::vec2(_lastX,_lastY);
		}

		void InputModule::phkey_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			//Window* win = (Window*)glfwGetWindowUserPointer(window);
			//win->_keys[key] = action != GLFW_RELEASE;
			
			getInstance()._keys[key] = action != GLFW_RELEASE;
		}

		void InputModule::phmouse_callback(GLFWwindow * window, int button, int action, int mods)
		{
			_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void InputModule::phcursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			_offsetX = xpos - _lastX;
			_offsetY = _lastY - ypos;

			_lastX = xpos;
			_lastY = ypos;
		}

		void InputModule::processInput(GLFWwindow * window)
		{
		}

		void InputModule::joystick_callback(int joy, int event)
		{
		}



	}


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "yes you pressed it" << std::endl;
	plaho::module::InputModule::getInstance().phkey_callback(window,key,scancode,action,mods);
}
void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	plaho::module::InputModule::getInstance().phmouse_callback(window, button, action, mods);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	plaho::module::InputModule::getInstance().phcursor_position_callback(window, xpos, ypos);
}
