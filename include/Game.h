#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include"Paddle.h"
#include<iostream>
#include<vector>
//this class instance is created using the Meyers’ singleton creational design pattern 
enum LineGraph {
	DASHED_LINE_VERTICAL,
	DASHED_LINE_HORIZANTAL
};
class Game {
public:

	static Game& instance() {
		static Game instance;
		return instance;
	}

	bool init();
	void inputHandler(bool& quit);
	void update();
	void render();
	void clean();
	bool loadMedia();

	void renderDashedLine(int start, int end, bool VerOrHor);//1 for vertical 0 for horizontal
	void initGraphics();
protected:
	Game();
	~Game();
private:

	int windowHeight;
	int windowWidth;

	int graphicsOffset;

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	//Game textures
	SDL_Texture* ballTexture;
	SDL_Texture* player1Texture;
	SDL_Texture* player2Texture;
	//Game objects:
	//2 Paddles
	Paddle *player1, *player2;//clean
	//and one ball

};