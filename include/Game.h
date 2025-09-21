#pragma once
#include<SDL3/SDL.h>
#include<iostream>
//this class its instance is created using the singleton creational design pattern 
class Game {
public:
	

	static Game* instance();

	bool init();
	void clean();
protected:
	Game();
	~Game();
private:
	static Game* _instance;

	int windowHeight;
	int windowWidth;

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

};