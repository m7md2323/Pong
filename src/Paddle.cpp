#include "Paddle.h"

//to be updated after (the initial position)
Paddle::Paddle():position(141,400)
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
	thePaddle.x = position.getX();
	thePaddle.y = position.getY();
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

void Paddle::moveUp()
{
	if (position.getY() > 50&&position.getY()<760) {
		position.setY(position.getY() - 15.5);
	}
}
void Paddle::moveDown()
{
	if (position.getY() > 50 && position.getY() < 760) {
		position.setY(position.getY() + 15.5);
	}
}

