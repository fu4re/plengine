#pragma once
#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include "stbi_image.h"

namespace graphics {
	//Variables
	extern GLFWwindow *window;
	extern GLuint texture_buffer;
	extern int width;
	extern int height;
	extern int x_pos;
	extern int y_pos;
	//Functions
	bool graphics_init(int window_width, int window_height, const char *title);
	void update();
	void render();
	bool create_sprite(const char *filepath);
}
