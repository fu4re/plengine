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
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			if (plr.onGround == true) {
				plr.player_sprite.sprite_rect.y += 10;
				plr.speedy = 20;
				plr.onGround = false;
			}
		}
	}
	void player_update(player_struct &plr, sprite &obj, map map1) {
		plr.player_sprite.sprite_rect.x += plr.speedx;
		collission_handling(plr, obj, map1, 0);
		if (!plr.onGround) {
			plr.speedy -= 1;
		}
		plr.player_sprite.sprite_rect.y += plr.speedy;
		collission_handling(plr, obj, map1, 1);
	}
	void collission_handling(player_struct &plr, sprite &obj, map map, int dir) {
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
						if ((plr.speedx > 0) && (dir == 0)) {
							plr.player_sprite.sprite_rect.x = obj.sprite_rect.x - plr.player_sprite.sprite_rect.width;
							plr.speedx = 0;
						}
						if ((plr.speedx < 0) && (dir == 0)) {
							plr.player_sprite.sprite_rect.x = obj.sprite_rect.x + obj.sprite_rect.width;
							plr.speedx = 0;
						}
						if ((plr.speedy > 0) && (dir == 1)) {
							plr.player_sprite.sprite_rect.y = obj.sprite_rect.y - obj.sprite_rect.height;
							plr.speedy = 0;
						}
						if ((plr.speedy < 0) && (dir == 1)) {
							plr.player_sprite.sprite_rect.y = obj.sprite_rect.y + plr.player_sprite.sprite_rect.height;
							plr.onGround = true;
						}
					}
				}
			}
		}
	}
}