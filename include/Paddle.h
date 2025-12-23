#pragma once 
#include<SDL3/SDL.h>
#include"Vector2D.h"
#include<string>
using namespace std;
class Paddle {
public:
	Paddle(int x,int y,string playerSide);
	~Paddle();
	bool init();

	void update();
	void render(SDL_Renderer *mainRenderer,bool mode);
	void inputHandler();
	void clean();

	void moveUp();
	void moveDown();
	
	float getWidth() { return width;};
	float getHeight() { return height; };

	int getScore() { return score; }
	void updateScore() { score++;}

	string getPlayerSide() { return playerSide; }
	Vector2D position;
private:

	float width;
	float height;

	string playerSide;//left or right
	int score;

};