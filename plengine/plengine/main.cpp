#include "graphics/graphics.h"
//Delete variables from headers
int main() {
	GLFWwindow *window;
	sprite player;
	player.sprite_rect.x = 100;
	player.sprite_rect.y = 450;
	player.sprite_rect.width = 400;
	player.sprite_rect.height = 400;
	graphics::graphics_init(&window, 640, 480, 1000, 500, "plengine");
	player.texture_buffer = graphics::load_texture("assets/drochim.png");
	while (1) {
		graphics::update();
		graphics::clear();
		//Start of the area where you need to draw objects
		graphics::display_sprite(player);
		//End of the area where you need to draw objects
		graphics::render(&window);
	}
	graphics::close_opengl(&window);
	return 0;
}