#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace plaho {
	namespace graphics {
		class Window
		{
		private:
			const char* _name;
			int _width, _height;
			GLFWwindow* _window;
			bool _closed;
		public:
			Window(const char*, int, int);
			~Window();

			bool closed() const;
			void clear() const;
			void update();
			//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }
		private:
			bool init();
		};
	}
}