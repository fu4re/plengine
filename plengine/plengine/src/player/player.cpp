#include "player.h"

namespace player {
	map map1;
	void handle_input(GLFWwindow *window, player_struct &plr) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			plr.speedx = 1;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			plr.speedx = -1;
		}
		else {
			plr.speedx = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (plr.onGround) {
				plr.speedy = 1;
			}
		}
		else {
			plr.speedy = 0;
		}
	}
	void player_update(player_struct &plr, sprite &obj, map map1) {
		plr.player_sprite.sprite_rect.x += plr.speedx;
		colission_handling_x(plr, obj, map1);
		if (!plr.onGround) {
			plr.speedy = -2;
		}
		plr.player_sprite.sprite_rect.y += plr.speedy;
		colission_handling_y(plr, obj, map1);
	}
	void colission_handling_x(player_struct &plr, sprite &obj, map map) {
		for (int i = 0; i <= map1.map_height; i++) {
			for (int j = 0; j <= map.map_width; j++) {
				obj.sprite_rect.x = j * obj.sprite_rect.width;
				obj.sprite_rect.y = (map.map_height - i) * obj.sprite_rect.height;
				if (map.map_arr[i][j] == 1) {
					int left = plr.player_sprite.sprite_rect.x;
					int right = plr.player_sprite.sprite_rect.x + plr.player_sprite.sprite_rect.width;
					int top = plr.player_sprite.sprite_rect.y;
					int bottom = plr.player_sprite.sprite_rect.y - plr.player_sprite.sprite_rect.height;
					if (right > obj.sprite_rect.x && obj.sprite_rect.x + obj.sprite_rect.width > left && top > obj.sprite_rect.y - obj.sprite_rect.height && obj.sprite_rect.y > bottom)
					{
						if (plr.speedx > 0) {
							plr.player_sprite.sprite_rect.x = obj.sprite_rect.x - plr.player_sprite.sprite_rect.width;
							plr.speedx = 0;
						}
						else if (plr.speedx < 0) {
							plr.player_sprite.sprite_rect.x = obj.sprite_rect.x + obj.sprite_rect.width;
							plr.speedx = 0;
						}
					}
				}
			}
		}
	}
	void colission_handling_y(player_struct &plr, sprite &obj, map map) {
		for (int i = 0; i <= map1.map_height; i++) {
			for (int j = 0; j <= map.map_width; j++) {
				obj.sprite_rect.x = j * obj.sprite_rect.width;
				obj.sprite_rect.y = (map1.map_height - i) * obj.sprite_rect.height;
				if (map.map_arr[i][j] == 1) {
					int left = plr.player_sprite.sprite_rect.x;
					int right = plr.player_sprite.sprite_rect.x + plr.player_sprite.sprite_rect.width;
					int top = plr.player_sprite.sprite_rect.y;
					int bottom = plr.player_sprite.sprite_rect.y - plr.player_sprite.sprite_rect.height;
					if (right > obj.sprite_rect.x && obj.sprite_rect.x + obj.sprite_rect.width > left&& top > obj.sprite_rect.y - obj.sprite_rect.height && obj.sprite_rect.y > bottom)
					{
						if (plr.speedy > 0) {
							plr.player_sprite.sprite_rect.y = obj.sprite_rect.y - obj.sprite_rect.height;
						}
						else if (plr.speedy < 0) {
							plr.player_sprite.sprite_rect.y = obj.sprite_rect.y + plr.player_sprite.sprite_rect.height;
							plr.speedy = 0;
							plr.onGround = true;
						}
						plr.onGround = false;
					}
				}
			}
		}
	}
}