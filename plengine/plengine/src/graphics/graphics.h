#pragma once
#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include "stbi_image.h"
#include <assert.h>
#include <math.h>

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
	extern const GLFWvidmode *video_mode;
	extern int width;
	extern int height;
	extern int x_position;
	extern int y_position;
	extern double last_time;
	extern double delta_time;
	extern double current_time;
	extern double fps;
	extern double period;
	bool graphics_init(GLFWwindow **window, int window_width, int window_height, int x_pos, int y_pos, const char *title);
	void update();
	void clear();
	void render(GLFWwindow **window);
	GLuint load_texture(const char *filepath);
	void display_sprite(sprite spr);
	void display_sprite(sprite spr, int offset_x, int offset_y);
	void close_opengl(GLFWwindow **window);
	void graphics_main();
}
