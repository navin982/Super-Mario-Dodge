#pragma once 
#include "player.h"

class Star {
public: 
	int x;
	int y;
	double velocity_x;
	int x_size;
	int y_size;
	void update();
	bool visible;
};