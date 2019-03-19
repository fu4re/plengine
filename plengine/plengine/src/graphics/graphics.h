#pragma once
#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include "stbi_image.h"

struct rect {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};
struct sprite {
	rect sprite_rect;
	GLuint texture_buffer;
};
namespace graphics {
	bool graphics_init(GLFWwindow **window, int window_width, int window_height, int x_pos, int y_pos, const char *title);
	void update();
	void clear();
	void render(GLFWwindow **window);
	GLuint load_texture(const char *filepath);
	void display_sprite(sprite spr);
	void close_opengl(GLFWwindow **window);
}
