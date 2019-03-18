#include "graphics/graphics.h"

int main() {
	graphics::graphics_init(640, 480, "plengine");
	GLuint texture = graphics::load_texture("assets/drochim.png");
	while (1) {
		graphics::update();
		graphics::clear();
		//Start of the area where you need to draw objects
		graphics::create_rect(100, 450, 400, 400, texture);
		//
		graphics::render();
	}
	graphics::close_opengl();
	return 0;
}