#include "graphics/graphics.h"

int main() {
	graphics::graphics_init(640, 480, "plengine");
	while (1) {
		graphics::update();
		graphics::render();
	}
	return 0;
}