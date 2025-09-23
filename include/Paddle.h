#pragma once 
#include<SDL3/SDL.h>
#include"Vector2D.h"
class Paddle {
public:
	Paddle();
	~Paddle();

	void update();
	void render(SDL_Renderer *mainRenderer);
	void inputHandler();
	void clean();

private:

	Vector2D position;
	SDL_FRect thePaddle;

};