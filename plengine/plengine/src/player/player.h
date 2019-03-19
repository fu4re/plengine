#pragma once
#include "graphics/graphics.h"

struct player {
	sprite player_sprite;
	int speedx = 0;
	int speedy = 0;
	bool onGround = false;
};

namespace player {
	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void input_setup(GLFWwindow *window);
}

