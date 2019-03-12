#include "graphics.h"

namespace graphics {
	//Variables
	GLFWwindow *window = nullptr;
	const GLFWvidmode *video_mode;
	GLuint texture_buffer = 0;
	int width = 0;
	int height = 0;
	int x_pos = 0;
	int y_pos = 0;
	//Functions
	bool graphics_init(int window_width, int window_height, const char *title) {
		if (!glewInit()) {
			printf("GLEW initialization failed");
			return false;
		}
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
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBind
		glfwSwapBuffers(window);
	}
	bool create_sprite(const char *filepath) {
		int image_width = 0;
		int image_height = 0;
		unsigned char *image = SOIL_load_image(filepath, &image_width, &image_height, NULL, NULL);
		if (image == nullptr) {
			printf("Image not found");
			return false;
		}
		else {
			glGenTextures(1, &texture_buffer);
			glBindTexture(GL_TEXTURE_2D, texture_buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return true;
	}
}