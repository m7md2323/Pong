#pragma once
#include"GameState.h"
//#include"PlayState.h"
#include"GraphicsHandler.h"
#include"UIHandler.h"
using namespace std;

class PauseState :public GameState {
public:
	PauseState(){}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual Game_State getStateID() const { return pauseID; }
private:
	static const Game_State pauseID;
};