#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include"Paddle.h"
#include"InputHandler.h"
#include"GraphicsHandler.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<numeric>
#include<algorithm>
#include <random>
#include<chrono>
#include<numbers>
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
	bool loadMedia();

	bool checkCollision(Paddle* p);

	void initSpeedForBall();
	//void renderScore(int score,bool player);//left 0 right 1
	void updateScore();

protected:
	Game();
	~Game();
private:

	vector<vector<vector<Uint8>>> storeImageAsMatrix(string filePath);
	float speed;

	int graphicsOffset;
	int leftPlayerScore;
	int rightPlayerScore;

	//Game objects:
	//2 Paddles
	Paddle *leftPlayer, *rightPlayer;//clean
	//and one ball (singleton instance)

};