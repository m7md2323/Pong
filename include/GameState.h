#pragma once
#include<string>
//#include<SDL3/SDL.h>
#include"InputHandler.h"

using namespace std;
enum Game_State {
	MENU,
	PAUSE,
	MODE_SELECTING,
	PLAYING,
	EXIT
};
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual Game_State getStateID() const = 0;

	GameState() = default;
};