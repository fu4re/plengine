#include "player/player.h"

namespace graphics {
	void graphics_main() {
		const int map_width = 20;
		const int map_height = 10;
		int map[map_height][map_width] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
		};
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
		empty_block.texture_buffer = graphics::load_texture("assets/brick.png");
		while (1) {
			graphics::clear();
			player::handle_input(window, player1);
			//Start of the area where you need to draw objects
			graphics::display_sprite(player1.player_sprite);
			for (int i = map_height; i > 0; i--) {
				for (int j = 0; j < map_width; j++) {
					block.sprite_rect.x = empty_block.sprite_rect.x = j * block.sprite_rect.width;
					block.sprite_rect.y = empty_block.sprite_rect.y = i * block.sprite_rect.height;
					if (map[i][j] == 1) {
						graphics::display_sprite(block);
					}
					else if (map[i][j] == 0) {
						graphics::display_sprite(empty_block);
					}
				}
			}
			//End
			player::player_update(player1);
			player::colission_handling(player1, block, player::map1);
			graphics::update();
			graphics::render(&window);
		}
		graphics::close_opengl(&window);
	}
}