#pragma once 
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<string>
#include"Vector2D.h"
using namespace std;

//this class instance is created using the Meyers’ singleton creational design pattern 
class Ball {
public:
	static Ball& instance() {
		static Ball instance;
		return instance;
	}
	void update();
	bool loadMedia(SDL_Renderer* mainRenderer,string strPath);
	void render(SDL_Renderer* mainRenderer, SDL_Texture* ballTexture);
	void clean();

	float getCenterX() { return position.getX() + width / 2.0f; }
	float getCenterY() { return position.getY() + height / 2.0f; }
	float getRadis(){return width / 2.0f; }

	Vector2D position;
	Vector2D velocity;

	void speedUp(float factor, float maxSpeed);
protected:
	Ball();
	~Ball();
private:

	float width = 25;
	float height = 25;
	//SDL_FPoint ballEdges;
	//SDL_Texture* ballImage;//clean

};