#include "player.h"

namespace player {
	void handle_input(GLFWwindow *window, player_struct &plr) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			plr.speedx = 5;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			plr.speedx = -5;
		}
		else {
			plr.speedx = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			plr.speedy = 5;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			plr.speedy = -5;
		}
		else {
			plr.speedy = 0;
		}
	}
	void player_update(player_struct &plr) {
		plr.player_sprite.sprite_rect.x += plr.speedx;
		plr.player_sprite.sprite_rect.y += plr.speedy;
	}
}