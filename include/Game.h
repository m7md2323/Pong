#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include"Paddle.h"
#include<iostream>
//this class instance is created using the Meyers’ singleton creational design pattern 
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
protected:
	Game();
	~Game();
private:

	int windowHeight;
	int windowWidth;

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