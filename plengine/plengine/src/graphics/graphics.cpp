#define STB_IMAGE_IMPLEMENTATION
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
		if (glfwInit() == false) {
			printf("GLFW initialization failed");
			return false;
		}
		window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
		if (window == nullptr) {
			printf("Window creation failed");
		}
		glfwMakeContextCurrent(window);
		if (glewInit() != 0) {
			printf("GLEW initialization failed");
			return false;
		}
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
	void clear() {
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void render() {
		glfwSwapBuffers(window);
	}
	void create_rect(int x, int y, int width, int height, GLuint texture_buffer) {
		glBindTexture(GL_TEXTURE_2D, texture_buffer);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 0); glVertex2d(x, y); //Left down corner
		glTexCoord2d(0, 0); glVertex2d(x + width, y); //Right down corner
		glTexCoord2d(0, 1); glVertex2d(x + width, y - height); // Right down corner
		glTexCoord2d(1, 1); glVertex2d(x, y - height); // Left down corner
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	GLuint load_texture(const char *filepath) {
		GLuint texture_buffer;
		int image_width = 0;
		int image_height = 0;
		unsigned char *image = stbi_load(filepath, &image_width, &image_height, NULL, NULL);
		if (image == nullptr) {
			printf("Image not found");
		}
		else {
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &texture_buffer);
			glBindTexture(GL_TEXTURE_2D, texture_buffer);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
		return texture_buffer;
	}
	void close_opengl() {
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}