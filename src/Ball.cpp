#include "Ball.h"
#include"GraphicsHandler.h"
#include<iostream>

void Ball::update(Paddle *p1,Paddle*p2)
{
	
	//cout << "Inside Ball Update\n";
	//state machine for ball
	position += velocity;
	switch (state) {
	case MOVING:
		if (checkAndHandleCollision(p1)|| checkAndHandleCollision(p2) || wallCollision()) {
			state = COLLIDING;
		}
		else if (checkOutOfBound()) {
			if (state == LEFT_OUT_OF_BOUND)
				p2->updateScore();
			if(state == RIGHT_OUT_OF_BOUND)
				p1->updateScore();
		}
		break;
	case COLLIDING:
		if (!checkAndHandleCollision(p1)&&!checkAndHandleCollision(p2) &&!wallCollision()) {
			state = MOVING;
		}
		break;
	case LEFT_OUT_OF_BOUND:
		state = RESET;
		break;
	case RIGHT_OUT_OF_BOUND:
		state = RESET;
		break;
	case RESET :
		position = Vector2D(GraphicsHandler::instance().getWindowWidth() / 2, GraphicsHandler::instance().getWindowHeight() / 2);
		resetBall();
		state = MOVING;
		break;
	}
	//velocity +=(velocity.length() * 0.04f);
}

bool Ball::loadMedia(SDL_Renderer *mainRenderer,string strPath)
{
	SDL_Texture* ballImage = IMG_LoadTexture(mainRenderer, strPath.c_str());
	if (ballImage == NULL) {
		SDL_Log("SDL_Image could not Load texture ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	SDL_DestroyTexture(ballImage);
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
	cout << velocity.length() << "\n";
}

void Ball::clean()
{

}
bool Ball::checkAndHandleCollision(Paddle* p)
{

	//ball collision
	//paddle
	float px1 = p->position.getX();
	float py1 = p->position.getY();
	float px2 = p->position.getX() + p->getWidth();
	float py2 = p->position.getY() + p->getHeight();
	float cx = getCenterX();
	float cy = getCenterY();
	float r = getRadis();
	//ball
	float closestX = clamp(cx, px1, px2);
	float closestY = clamp(cy, py1, py2);

	float dx = cx - closestX;
	float dy = cy - closestY;

	//Vector2D N(dx, dy);
	Vector2D* V = &velocity;
	//N.normalize();
	//v' = v - (1 + e) * (v · n) * n
	// dx,dy from closest point to center
	// 
	//-----Gemini modified version-----//
	if ((dx * dx + dy * dy <= r * r)) {
		// 1. Resolve penetration (keep your existing code for this)
		float dist = sqrtf(dx * dx + dy * dy);
		Vector2D N(dx, dy);
		if (dist == 0) { N = Vector2D(0, 1); dist = 1; }
		else { N /= dist; }
		float penetration = r - dist;
		position += N * penetration;

		// 2. Calculate Hit Factor (-1.0 to 1.0)
		// 0 is the middle of the paddle, 1 is the top, -1 is the bottom
		float paddleCenterY = p->position.getY() + p->getHeight() / 2.0f;
		float ballCenterY = position.getY() + r;
		float hitFactor = (ballCenterY - paddleCenterY) / (p->getHeight() / 2.0f);

		// 3. Apply Steering
		float speed = velocity.length(); // Get current speed magnitude
		float newVelX = (position.getX() < p->position.getX()) ? -1.0f : 1.0f;
		float newVelY = hitFactor * 1.5f; // Adjust 1.5f for "intensity" of steering

		// 4. Update Velocity
		velocity = Vector2D(newVelX, newVelY);
		velocity.normalize();
		velocity *= speed * 1.05f; // Slightly increase speed on each hit (1.05 = 5% boost)

		return true;
	}
	return false;
}
bool Ball::wallCollision()
{
	if (position.getY() <= 15) {
		position.setY(15);
		velocity.setY(-velocity.getY());
		return true;
	}
	else if (position.getY() + 25 >= GraphicsHandler::instance().getWindowHeight() - 15) {
		position.setY(GraphicsHandler::instance().getWindowHeight() - 15-25);
		velocity.setY(-1 * velocity.getY());
		return true;
	}
	return false;
}
bool Ball::checkOutOfBound()
{
	int ballX = position.getX();
	int ballY = position.getY();

	bool leftSideGoal = ballX + 25 < 0;
	bool rightSideGoal = ballX > GraphicsHandler::instance().getWindowWidth();

	if (leftSideGoal || rightSideGoal) {
		if (leftSideGoal) {
			state=LEFT_OUT_OF_BOUND;
		}
		if (rightSideGoal) {
			state=RIGHT_OUT_OF_BOUND;
		}
		return true;
	}
	return false;
}
//to be updated after (the initial position)
Ball::Ball() :position(GraphicsHandler::instance().getWindowWidth() / 2, GraphicsHandler::instance().getWindowHeight() / 2), 
	velocity(-5, 0)
{
}

Ball::~Ball()
{
}

