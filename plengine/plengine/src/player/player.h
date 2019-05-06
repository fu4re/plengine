#pragma once
#include "graphics/graphics.h"

struct player_struct {
	sprite player_sprite;
	int speedx = 0;
	int speedy = 0;
	bool onGround = false;
	bool collision_x = false;
	bool collision_y = false;
};

namespace player {
	void handle_input(GLFWwindow *window, player_struct &plr);
	void player_update(player_struct &plr);
	void colission_handling(player_struct &plr, rect &obj_rect);
}

