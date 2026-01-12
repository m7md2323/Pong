#pragma once

#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<numeric>
#include<algorithm>
#include <random>
#include<chrono>
#include<numbers>

#include"Ball.h"
#include"Paddle.h"
#include"InputHandler.h"
#include"GraphicsHandler.h"
#include"GameStateMachine.h"
#include"MenuState.h"
#include"PlayState.h"
#include"PauseState.h"
#include"UIHandler.h"

using namespace std;
//this class instance is created using the Meyers’ singleton creational design pattern 
class Game {
public:

	static Game& instance() {
		static Game instance;
		return instance;
	}

	bool init();
	void inputHandler();
	void update();
	void render();
	void clean();

protected:
	Game();
	~Game();
private:

};