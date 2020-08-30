#pragma once 

class Player {
public: 
	int x;
	int y;
	double velocity_x;
	double velocity_y;
	double acceleration_x;
	double acceleration_y;
	int ground;
	int x_Size;
	int y_Size;
	int invincible;

	void update();

	Player() {};

	//initializer list
	//code derived from: https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
	Player(int ground, int x, int y, int x_Size, int y_Size) :
		 x(x),
		 y(y),
		 ground(ground),
		 x_Size(x_Size), 
		 y_Size(y_Size),
		 velocity_x(0),
		 velocity_y(0),
		 acceleration_x(0),
	     acceleration_y(1),
		invincible(0)
		 {}
};