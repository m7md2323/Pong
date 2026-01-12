#pragma once 
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<string>
#include<algorithm>
#include <ctime>
#include"Vector2D.h"
#include"Paddle.h"
using namespace std;
enum BallState {
	COLLIDING,
	MOVING,
	LEFT_OUT_OF_BOUND,
	RIGHT_OUT_OF_BOUND,
	RESET
};
//this class instance is created using the Meyers’ singleton creational design pattern 
class Ball {
public:
	static Ball& instance() {
		static Ball instance;
		return instance;
	}
	void update(Paddle *p1,Paddle* p2);
	bool loadMedia(SDL_Renderer* mainRenderer,string strPath);
	void render(SDL_Renderer* mainRenderer, SDL_Texture* ballTexture);
	void clean();

	bool checkAndHandleCollision(Paddle* p);
	bool wallCollision();
	bool checkOutOfBound();
	//void handleCollision(const Paddle& p);
	float getCenterX() { return position.getX() + width / 2.0f; }
	float getCenterY() { return position.getY() + height / 2.0f; }
	float getRadis(){return width / 2.0f; }
	//To start or reset the ball to default state(when moving from RESET to MOVING state);
	void resetBall();
	BallState getBallState() { return state; }

	Vector2D position;
	Vector2D velocity;
protected:
	Ball();
	~Ball();
private:
	BallState state=MOVING;
	float width = 25;
	float height = 25;

	float speed;
	//SDL_FPoint ballEdges;
	//SDL_Texture* ballImage;//clean

};