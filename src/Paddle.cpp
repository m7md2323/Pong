#include "Paddle.h"

//to be updated after (the initial position)
Paddle::Paddle():position(0,0)
{

}

Paddle::~Paddle()
{
	clean();
}

void Paddle::update()
{

}



void Paddle::render(SDL_Renderer* mainRenderer)
{
	thePaddle.x = thePaddle.y = 100;
	thePaddle.w =10;
	thePaddle.h = 100;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(mainRenderer, &thePaddle);
}

void Paddle::inputHandler()
{

}

void Paddle::clean()
{
}
