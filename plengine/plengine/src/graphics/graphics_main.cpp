#include "player/player.h"

namespace graphics {
	void graphics_main() {
		map map1;
		int map_offset_x = 0;
		GLFWwindow *window;
		player_struct player1;
		sprite block;
		sprite empty_block;
		int screen_width = 640;
		int screen_height = 480;
		//Players rectangle setup
		player1.player_sprite.sprite_rect.x = 100;
		player1.player_sprite.sprite_rect.y = 300;
		player1.player_sprite.sprite_rect.width = 100;
		player1.player_sprite.sprite_rect.height = 100;
		//Block rectangle setup
		block.sprite_rect.width = empty_block.sprite_rect.width = screen_width / 10;
		block.sprite_rect.height = empty_block.sprite_rect.height = screen_height / 10;
		graphics::graphics_init(&window, screen_width, screen_height, 1000, 500, "plengine");
		player1.player_sprite.texture_buffer = graphics::load_texture("assets/background.png");
		block.texture_buffer = graphics::load_texture("assets/block.png");
		empty_block.texture_buffer = graphics::load_texture("assets/back.jpg");
		while (1) {
			current_time = glfwGetTime();
			delta_time = (current_time - last_time) * fps;
			if (delta_time >= 1.0f) {
				graphics::clear();
				player::handle_input(window, player1);
				//Start of the area where you need to draw objects
				graphics::display_sprite(player1.player_sprite);
				for (int i = 0; i <= map1.map_height; i++) {
					for (int j = 0; j <=   map1.map_width; j++) {
						block.sprite_rect.x = empty_block.sprite_rect.x = j * block.sprite_rect.width;
						block.sprite_rect.y = empty_block.sprite_rect.y = (map1.map_height - i) * block.sprite_rect.height;
						if (map1.map_arr[i][j] == 1) {
							graphics::display_sprite(block);
						}
						else if (map1.map_arr[i][j] == 0) {
							graphics::display_sprite(empty_block);
						}
					}
				}
				//End
				player::player_update(player1, block, map1);
				graphics::update();
				graphics::render(&window);
				delta_time--;
			}
		}
		graphics::close_opengl(&window);
	}
}