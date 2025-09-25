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

	void moveUp();
	void moveDown();
	
	Vector2D position;
private:

	
	SDL_FRect thePaddle;

};