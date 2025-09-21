#pragma once 
#include<SDL3/SDL.h>
#include"/Pong/PongGame/include/Vector2D.h"
//this class its instance is created using the singleton creational design pattern 
class Ball {
public:
	static Ball* instance();
	void clean();

protected:
	Ball();
	~Ball();
private:
	static Ball* _instance;
	Vector2D position;

};