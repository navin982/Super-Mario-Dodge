#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	star.visible = false;
	deep_sea_timer = 100;
	ofSetWindowTitle("Super Mario Dodge");
	state = START;
	spawn_delay = 0;
	loadThings();
	start_up_sound.play();

	//for obstacle (including star) generation
	generator_ = std::mt19937(rand());
	spawner = std::uniform_int_distribution<>(0, 100000);
}

//--------------------------------------------------------------
void ofApp::update() {
	musicTimer();
	if (state == RUNNING) {
		noki_bay.stop();
		star.update();
		player.update();
		collision();
		spawnPipe();
		spawnStar();

		if (player.invincible > 0) {
			player.invincible--;
		}
		//memory storage
		while (obstacles.size() > 0 && obstacles.front().x < -100) {
			obstacles.pop_front();
			score++;
		}

		//makes sure star does not spawn when invincible
		if (star.x < -100) {
			star.visible = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	running_game_background();
	instructions_background();
	score_background();
	start_background();
	game_over_background();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	int upper_key = toupper(key);

	if (state == START && upper_key == 'I') {
		noki_bay.stop();
		game_over_sound.stop();
		deep_sea.stop();
		instructions.play();
		state = HELP;
	}
	else if (state == HELP && upper_key == 'I') {
		instructions.stop();
		noki_bay.play();
		state = START;
	}
	else if (state == START && upper_key == 'S') {
		noki_bay.stop();
		game_over_sound.stop();
		deep_sea.stop();
		score_music.play();
		state = SCORE;
	}
	else if (state == SCORE && upper_key == 'S') {
		score_music.stop();
		noki_bay.play();
		state = START;
	}
	else if (state == START) {
		deep_sea.play();
		star.visible = false;
		score = 0;
		player = Player(ofGetWindowHeight() - 100, 100, ofGetWindowHeight() * 0.5, 50, 100);
		player.acceleration_y = 1;
		state = RUNNING;
		obstacles.clear();
	} 
	else if (state == RUNNING && player.y == player.ground && upper_key == ' ') {
		jump.play();
		player.velocity_y = -25;
	}
	else if  (upper_key == 'P' && state == PAUSE) {
		if (player.invincible > 0) {
			invincible.play();
		}
		state = RUNNING;
	}
	else if (player.invincible == false && upper_key == 'P' && state == RUNNING) {
		pause_music.play();
		invincible.stop();
		state = PAUSE;
	}
	else if (state == OVER) {
		state = START;
	}
}

void ofApp::musicTimer() {
	if (deep_sea_timer > 0) {
		deep_sea_timer -= 1;
	}
	else if (deep_sea_timer == 0) {
		deep_sea.play();
		deep_sea.setLoop(true);
		deep_sea_timer = -1;
	}
}

ofColor ofApp::colorTimer() {
	if (color_timer == 0) {
		color_timer = 30;
		background_color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	}
	color_timer--;
	return background_color;
}

void ofApp::loadThings() {
	deep_sea.load("deep sea.mp3");
	start_up_sound.load("start up sound project.mp3");
	game_over_sound.load("game over sound.mp3");
	main_screen_font.load("CHLORINP.TTF", 80);
	press_key_screen_font.load("CHLORINP.TTF", 50);
	small_screen_font.load("monster.otf", 30);
	go_back_font.load("monster.otf", 50);
	help_font.load("monster.otf", 25);
	main_screen_image.load("images/snake.png");
	jump.load("jump.wav");
	invincible.load("invincible.mp3");
	instructions.load("instructions.mp3");
	score_music.load("score.mp3");
	pause_music.load("pause.mp3");
	noki_bay.load("noki bay.mp3");
	//draws mario
	mario.load("images/mario.png");
	//draws pipe
	pipe.load("images/pipe.png");
	//draws star
	star_image.load("images/star.png");
	star_image.setImageType(OF_IMAGE_COLOR_ALPHA);
	//code blowed derived from 
	//https://forum.openframeworks.cc/t/set-white-pixels-to-transparent/23792
	ofPixelsRef pixels = star_image.getPixels();
	for (int y = 0; y < star_image.getHeight(); y++) {
		for (int x = 0; x < star_image.getWidth(); x++) {
			ofColor color = star_image.getColor(x, y);
			int threshold = 150;
			if (color.r > threshold && color.g > threshold && color.b > threshold) {
				pixels.setColor(x, y, ofColor(0, 0, 0, 0));
			}
		}
	}
	star_image.setFromPixels(pixels);
}

void ofApp::collision() {
	//collision for player
	ofRectangle player_rect_collision(player.x + player.x_Size * 0.1, player.y + player.y_Size *0.1, player.x_Size * 0.7, player.y_Size * 0.7);
	//star intersection 
	ofRectangle star_rect_collision(star.x, star.y, star.x_size, star.y_size);
	if (star.visible && star_rect_collision.intersects(player_rect_collision)) {
		//10 seconds
		player.invincible = 600;
		star.visible = false;
		color_timer = 0;
		invincible.play();
	}
	//derived from https://stackoverflow.com/questions/6953128/need-iterator-when-using-ranged-based-for-loops
	for (Obstacle& i : obstacles) {
		i.update();
		//collision for object
		ofRectangle object_rect_collision(i.x, i.y, i.x_size, i.y_size);
		if (player.invincible == 0 && object_rect_collision.intersects(player_rect_collision)) {
			prev_score.push_back(score);
			deep_sea.stop();
			game_over_sound.play();
			Sleep(3000);
			state = OVER;
		}
	}
}


void ofApp::spawnPipe() {
	if (spawn_delay == 0 && spawner(generator_) < 3000) {
		Obstacle o;
		if (score > 10) {
			o.velocity_x = -(log(score) * 6);
		}
		else {
			o.velocity_x = -10;
		}
		if (spawner(generator_) % 2 == 0) {
			o.y = ofGetWindowHeight() - 100;
		}
		else {
			o.y = ofGetWindowHeight() - 350;
		}
		o.x = ofGetWindowWidth();
		o.x_size = 50;
		o.y_size = 100;
		spawn_delay = 38;
		obstacles.push_back(o);
	}

	if (spawn_delay > 0) {
		spawn_delay--;
	}
}

void ofApp::spawnStar() {
	if (player.invincible == 0 && !star.visible && spawner(generator_) < 40) {
		star.visible = true;
		star.x = ofGetWindowWidth();
		star.y = ofGetWindowHeight() - 300;
		star.velocity_x = -10;
		star.x_size = 50;
		star.y_size = 50;
	}
}

void ofApp::running_game_background() {
	if ((state == RUNNING || state == PAUSE) && player.invincible) {
		ofSetColor(colorTimer());
		main_screen_image.draw(0, -10);
	}
	else {
		ofSetColor(255, 255, 255);
		main_screen_image.draw(0, -10);
	}
}

void ofApp::instructions_background() {
	if (state == HELP) {
		ofSetColor(0, 0, 0);
		help_font.drawString("In this game, pipes will be coming at Mario. \nMario needs to dodge them, otherwise he dies. \nPress 'space' to jump. \nPress 'P' to pause the game. \nTry to get stars, they give Mario special powers, \nFor a short time.", 45, 150);
		go_back_font.drawString("Press I to go back", 175, 550);
	}
}

void ofApp::score_background() {
	if (state == SCORE) {
		stringstream ss;
		ofSetColor(0, 0, 0);
		go_back_font.drawString("Press S to go back", 175, 700);
		ss << "Scores : \n";
		for (int i = 0; i < prev_score.size(); i++) {
			ss << prev_score[i] << "\n";
		}
		small_screen_font.drawString(ss.str(), 425, 100);
	}
}

void ofApp::start_background() {
	if (state == START) {
		ofSetColor(153, 66, 255);
		main_screen_font.drawString("Super", 385, 190);
		main_screen_font.drawString("Mario Dodge", 175, 300);
		press_key_screen_font.drawString("Press any key to start", 100, 400);
		small_screen_font.drawString("Press I for instructions", 275, 600);
		small_screen_font.drawString("Press S for scores", 300, 675);
	}
	if (state == RUNNING || state == PAUSE) {
		if (star.visible) {
			star_image.draw(star.x, star.y, star.x_size, star.y_size);
		}
		stringstream ss;
		ss << score;
		main_screen_font.drawString(ss.str(), 50, 100);

		mario.draw(player.x, player.y, player.x_Size, player.y_Size);

		for (Obstacle& i : obstacles) {
			pipe.draw(i.x, i.y, i.x_size, i.y_size);
		}
	}
}

void ofApp::game_over_background() {
	if (state == OVER) {
		stringstream ss;
		ss << score;
		ofSetColor(0, 0, 0);
		main_screen_font.drawString(ss.str(), 300, 350);
		ofSetColor(0, 0, 0);
		small_screen_font.drawString("Game Over! \n Press any key to restart", 300, 400);
	}
}

