#pragma once 
#include "player.h"

class Obstacle {
public: 
	int x;
	int y;
	double velocity_x;
	int x_size;
	int y_size;
	void update();
};