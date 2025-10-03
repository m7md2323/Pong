#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include"Paddle.h"
#include"InputHandler.h"
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

	bool init(int windowWidth, int windowHeight);
	void inputHandler();
	void update();
	void render();
	void clean();
	bool loadMedia();
	void renderLine(int start, int end,int width,int height,bool dashed, bool VerOrHor);//1 for vertical 0 for horizontal, 1 for dashed line 0 for not

	bool checkCollision(Paddle* p);
	void renderMap();

	void initSpeedForBall();
	void renderScore();
	void updateScore();

protected:
	Game();
	~Game();
private:

	vector<vector<vector<Uint8>>> storeImageAsMatrix(string filePath);
	float speed;

	int windowHeight;
	int windowWidth;

	int graphicsOffset;
	int leftPlayerScore;
	int rightPlayerScore;

	string ballFilePath;

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	//Game textures
	SDL_Texture* ballTexture;
	SDL_Texture* scoreTexture;
	//Game objects:
	//2 Paddles
	Paddle *leftPlayer, *rightPlayer;//clean
	//and one ball (singleton instance)

};