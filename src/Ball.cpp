#include "Ball.h"
#include<iostream>

void Ball::update()
{
	//cout << "Inside Ball Update\n";
	position += velocity;
	//velocity +=(velocity.length() * 0.04f);
}

bool Ball::loadMedia(SDL_Renderer *mainRenderer,string strPath)
{
	SDL_Texture* ballImage = IMG_LoadTexture(mainRenderer, strPath.c_str());
	if (ballImage == NULL) {
		SDL_Log("SDL_Image could not Load texture ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void Ball::render(SDL_Renderer * mainRenderer,SDL_Texture * ballTexture)
{

	SDL_FRect sourceRect, destRect;
	sourceRect.y = sourceRect.x = 0;
	sourceRect.w = destRect.w =ballTexture->w;
	sourceRect.h = destRect.h = ballTexture->h;
	destRect.x = position.getX();
	destRect.y = position.getY();

	SDL_RenderTexture(mainRenderer, ballTexture, &sourceRect, &destRect);
}
void Ball::speedUp(float factor, float maxSpeed)
{
	float currentSpeed = velocity.length();
	if (currentSpeed < maxSpeed)
	{
		// normalize velocity (direction stays the same)
		Vector2D direction = velocity;
		direction.normalize();
		// scale it up
		velocity = direction * (currentSpeed * factor);
	}
}

void Ball::clean()
{

}
//to be updated after (the initial position)
Ball::Ball() :position(1200/2,800/2), velocity(-6, 0)
{

}

Ball::~Ball()
{
}

