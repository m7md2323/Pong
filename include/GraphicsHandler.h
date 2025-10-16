#pragma
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Ball.h"
#include<string>
#include<iostream>
#include<map>
using namespace std;
//this class instance is created using the Meyers’ singleton creational design pattern 
class GraphicsHandler {
public:
	static GraphicsHandler& instance() {
		static GraphicsHandler instance;
		return instance;
	}
	bool init(int windowWidth, int windowHeight);
	void renderFancyMap();
	void renderClassicMap();
	bool loadMedia(string filePath,string id);
	void drawLine(int start, int end, int width, int height, bool dashed, bool VerOrHor);
	void renderGraphics();
	void clean();
	void renderScore(int score,bool player);
	int getWindowWidth() { return windowWidth; }
	int getWindowHeight() { return windowHeight; }
	SDL_Texture* getTextureById(string id) { return id_texture[id]; }

	SDL_Renderer* getRenderer() { return mainRenderer; }
protected:

	GraphicsHandler();
	~GraphicsHandler();

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	int windowWidth;
	int windowHeight;

	map<string, SDL_Texture*> id_texture;
	//Game objects:
	//2 Paddles
	//Paddle* leftPlayer, * rightPlayer;//clean
};