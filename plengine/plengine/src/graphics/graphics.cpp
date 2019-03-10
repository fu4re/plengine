#include "graphics.h"

namespace graphics {
	//Variables
	GLFWwindow *window = nullptr;
	const GLFWvidmode *video_mode;
	int width = 0;
	int height = 0;
	int x_pos = 0;
	int y_pos = 0;
	//Functions
	bool graphics_init(int window_width, int window_height, const char *title) {
		if (!glfwInit()) {
			printf("GLFW initialization failed");
			return false;
		}
		window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
		if (window == nullptr) {
			printf("Window creation failed");
		}
		glfwMakeContextCurrent(window);
		//Setting window position
		glfwGetFramebufferSize(window, &width, &height);
		video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		x_pos = (video_mode->width - window_width) / 2;
		y_pos = (video_mode->height - window_height) / 2;
		glfwSetWindowPos(window, x_pos, y_pos);
		//Viewport
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, 0, height, -10, 10);
		glDepthRange(-10, 10);
		glMatrixMode(GL_MODELVIEW);
		//Alpha
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		return true;
	}
	void update() {
		glfwPollEvents();
	}
	void render() {
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
}