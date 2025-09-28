#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include"Paddle.h"
#include"InputHandler.h"
#include<iostream>
#include<vector>
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
	void renderLine(int start, int end,bool dashed, bool VerOrHor);
	//1 for vertical 0 for horizontal, 1 for dashed line 0 for not
	bool checkCollision(Paddle* p);
	void renderMap();

protected:
	Game();
	~Game();
private:

	vector<vector<vector<Uint8>>> storeImageAsMatrix(string filePath);

	int windowHeight;
	int windowWidth;

	int graphicsOffset;

	string ballFilePath;

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	//Game textures
	SDL_Texture* ballTexture;
	SDL_Texture* player1Texture;
	SDL_Texture* player2Texture;
	//Game objects:
	//2 Paddles
	Paddle *player1, *player2;//clean
	//and one ball (singleton instance)

};