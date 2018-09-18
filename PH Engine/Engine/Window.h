#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace plaho {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
	namespace graphics {
		class Window
		{
		public:
			//static Window* INSTANCE;
		private:
			const char* _name;
			int _width, _height;
			GLFWwindow* _window;
			bool _closed;

			static bool _keys[1024];
			static bool _mouseButtons[MAX_BUTTONS];
			static double _mx, _my;
		public:
			Window(const char*, int, int);
			~Window();

			bool closed() const;
			void clear() const;
			void update();
			//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }

			static bool isKeyPressed(unsigned int keycode); 
			static bool isMouseButtonPressed(unsigned int button);
		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_callback(GLFWwindow* window, int button, int action, int mods);

		};
	}
}