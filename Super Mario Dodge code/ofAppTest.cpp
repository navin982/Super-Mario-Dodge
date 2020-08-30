/*
//uncomment all this out and comment out main.cpp to run tests
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "player.h"
#include "star.h"
#include "obstacle.h"


TEST_CASE("Makes sure various sprites can move") {
	SECTION("Makes sure Mario's properties are correctly loaded") {
		Player test_player;
		test_player.y = 10;
		test_player.velocity_y = 5;
		test_player.acceleration_y = 0;
		test_player.ground = 100;
		test_player.update();
		REQUIRE(test_player.y == 15);
	}

	SECTION("Makes sure star properties are correctly loaded") {
		Star test_star;
		test_star.x = 5;
		test_star.y = 10;
		test_star.velocity_x = 5;
		test_star.y_size = 5;
		test_star.update();
		REQUIRE(test_star.x == 10);
		REQUIRE(test_star.y == 10);
		REQUIRE(test_star.y_size == 5);
	}

	SECTION("Makes sure pipe properties are correctly loaded") {
		Obstacle test_obstacle;
		test_obstacle.x = 5;
		test_obstacle.y = 10;
		test_obstacle.velocity_x = 5;
		test_obstacle.y_size = 5;
		test_obstacle.update();
		REQUIRE(test_obstacle.x == 10);
		REQUIRE(test_obstacle.y == 10);
		REQUIRE(test_obstacle.y_size == 5);

	}
}
*/
