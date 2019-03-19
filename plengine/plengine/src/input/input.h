#pragma once
#include "graphics/graphics.h"

namespace input {
	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void input_setup(GLFWwindow *window);
}