#pragma once
#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include "stbi_image.h"

namespace graphics {
	//Variables
	extern GLFWwindow *window;
	extern int width;
	extern int height;
	extern int x_pos;
	extern int y_pos;
	//Functions
	bool graphics_init(int window_width, int window_height, const char *title);
	void update();
	void clear();
	void render();
	void create_rect(int x, int y, int width, int height, GLuint texture_buffer);
	GLuint load_texture(const char *filepath);
	void close_opengl();
}
