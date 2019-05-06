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
	void colission_handling(player_struct &plr, rect &obj_rect) {
		if (plr.player_sprite.sprite_rect.x + plr.player_sprite.sprite_rect.width > obj_rect.x && obj_rect.x + obj_rect.width > plr.player_sprite.sprite_rect.x
		&& plr.player_sprite.sprite_rect.y > obj_rect.y - obj_rect.height && obj_rect.y > plr.player_sprite.sprite_rect.y - plr.player_sprite.sprite_rect.height)
		{
			if (plr.speedx > 0) {
				plr.player_sprite.sprite_rect.x = obj_rect.x - plr.player_sprite.sprite_rect.width;
				plr.speedx = 0;
			}
			else if (plr.speedx < 0) {
				plr.player_sprite.sprite_rect.x = obj_rect.x + obj_rect.width;
				plr.speedx = 0;
			}
			if (plr.speedy > 0) {
				plr.player_sprite.sprite_rect.y = obj_rect.y - obj_rect.height;
				plr.speedy = 0;
			}
			else if (plr.speedy < 0) {
				plr.player_sprite.sprite_rect.y = obj_rect.y + plr.player_sprite.sprite_rect.height;
				plr.speedy = 0;
			}
		}
	}
}