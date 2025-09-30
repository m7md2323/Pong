#include "Paddle.h"

//to be updated after (the initial position)
Paddle::Paddle(float width,float height):position(50,400),width{width},height{height}
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
	SDL_FRect thePaddle;
	thePaddle.x = position.getX();
	thePaddle.y = position.getY();
	thePaddle.w =width;
	thePaddle.h = height;
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
	if (position.getY()>= 58) {
		position.setY(position.getY() - 8);
	}
}
void Paddle::moveDown()
{
	if (position.getY()+height <= 754) {
		position.setY(position.getY() + 8);
	}
}

