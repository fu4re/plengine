#include "player/player.h"

namespace graphics {
	void graphics_main() {
		GLFWwindow *window;
		player_struct player1;
		sprite block;
		int screen_width = 640;
		int screen_height = 480;
		int map_width = 16;
		int map_height = 16;
		//Players rectangle setup
		player1.player_sprite.sprite_rect.x = 100;
		player1.player_sprite.sprite_rect.y = 450;
		player1.player_sprite.sprite_rect.width = 100;
		player1.player_sprite.sprite_rect.height = 100;
		//Block rectangle setup
		block.sprite_rect.x = 300;
		block.sprite_rect.y = 400;
		block.sprite_rect.width = 225;
		block.sprite_rect.height = 225;
		graphics::graphics_init(&window, screen_width, screen_height, 1000, 500, "plengine");
		player1.player_sprite.texture_buffer = graphics::load_texture("assets/drochim.png");
		block.texture_buffer = graphics::load_texture("assets/texture_brick.jpg");
		while (1) {
			graphics::update();
			graphics::clear();
			player::handle_input(window, player1);
			player::player_update(player1);
			//Start of the area where you need to draw objects
			//for (int i = 0; i < map_height; i++) {
				//for (int j = 0; j < map_width; j++) {
					//block.sprite_rect.x = j * block.sprite_rect.width;
					//block.sprite_rect.y = i * block.sprite_rect.height;
					graphics::display_sprite(block);
					player::colission_handling(player1, block.sprite_rect);
				//}
			//}
			graphics::display_sprite(player1.player_sprite);
			//End
			graphics::render(&window);
		}
		graphics::close_opengl(&window);
	}
}