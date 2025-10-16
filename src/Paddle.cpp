#include "Paddle.h"
#include "GraphicsHandler.h"
//to be updated after (the initial position)
Paddle::Paddle(float width,float height,int x,int y):position(x,y),width{width},height{height},score{0}
{

}

Paddle::~Paddle()
{
	clean();
}

void Paddle::update()
{

}



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
		
		
		cout << GraphicsHandler::instance().getTextureById("fancyPaddle")->w<<"\n";
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
		position.setY(position.getY() - 6);
	}
}
void Paddle::moveDown()
{
	if (position.getY()+height <= 583) {
		position.setY(position.getY() + 6);
	}
}

