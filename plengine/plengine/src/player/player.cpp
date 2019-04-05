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
	void colission_handling(player_struct &player, rect obj_rect) {
		if ((player.player_sprite.sprite_rect.x > obj_rect.x && player.player_sprite.sprite_rect.x < obj_rect.x + obj_rect.width)
		&& (player.player_sprite.sprite_rect.y > obj_rect.y - obj_rect.height && player.player_sprite.sprite_rect.y < obj_rect.y))
		{
			if (player.speedx > 0) {
				player.player_sprite.sprite_rect.x = obj_rect.x;
			}
			else if (player.speedx < 0) {
				player.player_sprite.sprite_rect.x = obj_rect.x + obj_rect.width;
			}
			if (player.speedy > 0) {
				player.player_sprite.sprite_rect.y = obj_rect.y - obj_rect.height;
			}
			else if (player.speedy < 0) {
				player.player_sprite.sprite_rect.y = obj_rect.y;
			}
		}
	}
}