#include "player.h"

namespace player {
	map map1;
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
	void colission_handling(player_struct &plr, sprite &obj_rect, map map) {
		for (int i = map.map_height; i > 0; i--) {
			for (int j = 0; j < map.map_width; j++) {
				obj_rect.sprite_rect.x = j * obj_rect.sprite_rect.width;
				obj_rect.sprite_rect.y = i * obj_rect.sprite_rect.height;
				if (map.map_arr[i][j] == 1) {
					int left = plr.player_sprite.sprite_rect.x;
					int right = plr.player_sprite.sprite_rect.x + plr.player_sprite.sprite_rect.width;
					int top = plr.player_sprite.sprite_rect.y;
					int bottom = plr.player_sprite.sprite_rect.y - plr.player_sprite.sprite_rect.height;
					if (right > obj_rect.sprite_rect.x && obj_rect.sprite_rect.x + obj_rect.sprite_rect.width > left&& top > obj_rect.sprite_rect.y - obj_rect.sprite_rect.height && obj_rect.sprite_rect.y > bottom)
					{
						if (plr.speedx > 0) {
								plr.player_sprite.sprite_rect.x = obj_rect.sprite_rect.x - plr.player_sprite.sprite_rect.width;
								plr.speedx = 0;
						}
						else if (plr.speedx < 0) {
							plr.player_sprite.sprite_rect.x = obj_rect.sprite_rect.x + obj_rect.sprite_rect.width;
							plr.speedx = 0;
						}
						if (plr.speedy > 0) {
							plr.player_sprite.sprite_rect.y = obj_rect.sprite_rect.y - obj_rect.sprite_rect.height;
							plr.speedy = 0;
						}
						else if (plr.speedy < 0) {
							plr.player_sprite.sprite_rect.y = obj_rect.sprite_rect.y + plr.player_sprite.sprite_rect.height;
							plr.speedy = 0;
						}
					}
				}
			}
		}
	}
}