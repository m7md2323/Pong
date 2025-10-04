#pragma once 
#include<SDL3/SDL.h>
#include"Vector2D.h"
class Paddle {
public:
	Paddle(float width,float height,int x,int y);
	~Paddle();

	void update();
	void render(SDL_Renderer *mainRenderer);
	void inputHandler();
	void clean();

	void moveUp();
	void moveDown();
	
	float getWidth() { return width;};
	float getHeight() { return height; };
	Vector2D position;
private:

	float width;
	float height;

	int score;

};