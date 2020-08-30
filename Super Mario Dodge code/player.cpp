#include "player.h"

void Player::update() {
	x = x + velocity_x;
	y = y + velocity_y;
	velocity_x = velocity_x + acceleration_x;
	velocity_y = velocity_y + acceleration_y;

	if (y > ground) {
		y = ground;
		velocity_y = 0;
	}
}