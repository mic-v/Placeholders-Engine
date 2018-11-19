#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

/// InputModule class
//	
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace plaho
{
	namespace module
	{
		class InputModule
		{
		public:
			 bool _keys[MAX_KEYS];
			 bool _mouseButtons[MAX_BUTTONS];
			 double _lastX, _lastY;
			 double _offsetX, _offsetY;

			static InputModule& getInstance();
			void startUp();
			void update(float dt);
			void shutDown();

			/// Getter functions
			bool isKeyPressed(unsigned int keycode);
			bool isMouseButtonPressed(unsigned int button);
			glm::vec2 getMousePos();


			/// Callback Functions
			void phkey_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			void phmouse_callback(GLFWwindow* window, int button, int action, int mods);
			void phcursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			void processInput(GLFWwindow * window);
			void joystick_callback(int joy, int event);

		private:
			InputModule() {}
			~InputModule() {}
		};
	}

}