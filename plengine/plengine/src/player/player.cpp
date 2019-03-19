#include "player.h"

namespace player {
	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		rect coord_changes;
		if (key == GLFW_KEY_D) {
			coord_changes.x += 5;
		}
		else if (key == GLFW_KEY_A) {
			coord_changes.x -= 5;
		}
	}
	void input_setup(GLFWwindow *window) {
		glfwSetKeyCallback(window, keyCallback);
	}
}