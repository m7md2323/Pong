#pragma once
#include"GameState.h"
//#include"PlayState.h"
#include"GraphicsHandler.h"
#include"UIHandler.h"
#include"PlayState.h"
using namespace std;

class WinState :public GameState {
public:
	WinState() {}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual Game_State getStateID() const { return winID; }
private:
	static const Game_State winID;
};