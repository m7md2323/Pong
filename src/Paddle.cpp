#include "Paddle.h"
#include "GraphicsHandler.h"
#include "InputHandler.h"

//to be updated after (the initial position)
Paddle::Paddle(int x,int y,string _playerSide):position(x,y),score{0},playerSide{_playerSide}
{
	width = 10;
	height = 100;
}

Paddle::~Paddle()
{
	clean();
}
bool Paddle::init() {
	return true;
}
void Paddle::update()
{
	if (playerSide == "left") {
		
		if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_W)) {
			moveUp();
		}
		if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) {
			moveDown();
		}
	}
	if (playerSide == "right") {
		if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_UP)) {
			moveUp();
		}
		if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN)) {
			moveDown();
		}
	}
}


// 0--> classic  1-->fancy
void Paddle::render(SDL_Renderer* mainRenderer,bool mode)
{
	if (mode == false) {
		SDL_FRect thePaddle;
		thePaddle.x = position.getX();
		thePaddle.y = position.getY();
		thePaddle.w = width;
		thePaddle.h = height;
		SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(mainRenderer, &thePaddle);
	}
	else {
		SDL_FRect sourceRect, destRect;
		
		sourceRect.x =0;
		sourceRect.y =0;
		sourceRect.w = GraphicsHandler::instance().getTextureById("fancyPaddle")->w;
		sourceRect.h = GraphicsHandler::instance().getTextureById("fancyPaddle")->h;

		destRect.x = position.getX();
		destRect.y = position.getY();
		destRect.w = sourceRect.w;
		destRect.h = sourceRect.h;

		SDL_RenderTexture(mainRenderer, GraphicsHandler::instance().getTextureById("fancyPaddle"), &sourceRect, &destRect);

		//SDL_DestroyTexture(GraphicsHandler::instance().getTextureById("fancyPaddle"));
		//fancyPaddle = nullptr;
	}
}

void Paddle::inputHandler()
{

}

void Paddle::clean()
{
}

void Paddle::moveUp()
{
	if (position.getY()>= 15) {
		position.setY(position.getY() - 8);
	}
}
void Paddle::moveDown()
{
	if (position.getY()+height <= 583) {
		position.setY(position.getY() + 8);
	}
}

