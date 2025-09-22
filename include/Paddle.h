#pragma once 
#include<SDL3/SDL.h>
#include"Vector2D.h"
class Paddle {
public:
	Paddle();
	~Paddle();

	void update();
	void clean();

private:

	Vector2D position;

};