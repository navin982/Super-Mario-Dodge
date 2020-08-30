#pragma once

#include "ofMain.h"
#include "..\player.h"
#include "..\obstacle.h"
#include "..\star.h"
#include <random>


class ofApp : public ofBaseApp{

	enum GameState {
		START,
		RUNNING, 
		OVER,
		PAUSE,
		HELP,
		SCORE
	};

	//tracks previous game's scores
	std::vector<int> prev_score;

	public:
		void loadThings();
		void setup();
		void update();
		void draw();
		void collision();
		void spawnPipe();
		void spawnStar();

		//draws all the screens
		void running_game_background();
		void instructions_background();
		void score_background();
		void start_background();
		void game_over_background();

		void keyPressed(int key);

		//to make main music play
		void musicTimer();
		int deep_sea_timer;

		//change background color 
		ofColor colorTimer();
		int color_timer;
		ofColor background_color; 

		//sounds in game
		ofSoundPlayer start_up_sound;
		ofSoundPlayer deep_sea;
		ofSoundPlayer game_over_sound;
		ofSoundPlayer jump;
		ofSoundPlayer invincible;
		ofSoundPlayer instructions;
		ofSoundPlayer score_music;
		ofSoundPlayer pause_music;
		ofSoundPlayer noki_bay;

		//various fonts
		ofTrueTypeFont main_screen_font;
		ofTrueTypeFont press_key_screen_font;
		ofTrueTypeFont help_font;
		ofTrueTypeFont go_back_font;
		ofTrueTypeFont small_screen_font;

		//background image
		ofImage main_screen_image;

		//draws mario
		ofImage mario;

		//draws pipe
		ofImage pipe;

		//draws star
		ofImage star_image;

		//player object
		Player player;

		//obstacles
		std::list<Obstacle> obstacles;
		std::mt19937 generator_;
		std::uniform_int_distribution<> spawner;
		int spawn_delay;

		//tracks gamestate
		GameState state;

		//keeps track of pipes passed
		int score;

		//Star formation
		Star star;
	
	
};
