#include "/Pong/PongGame/include/Ball.h"

Ball* Ball::_instance = NULL;

Ball* Ball::instance()
{
	if (_instance == NULL) {
		_instance = new Ball();
	}
	return _instance;
}

void Ball::clean()
{

}

Ball::Ball()
{
}

Ball::~Ball()
{
}

