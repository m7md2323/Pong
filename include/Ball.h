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

	Vector2D position;
	Vector2D velocity;
protected:
	Ball();
	~Ball();
private:
	//SDL_FPoint ballEdges;
	//SDL_Texture* ballImage;//clean

};