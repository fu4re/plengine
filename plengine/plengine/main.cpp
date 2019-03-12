#include "graphics/graphics.h"

int main() {
	graphics::graphics_init(640, 480, "plengine");
	graphics::create_sprite("images.png");
	while (1) {
		graphics::update();
		graphics::render();
	}
	return 0;
}