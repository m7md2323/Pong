#pragma once
#include"GameState.h"
//#include"PlayState.h"
#include"GraphicsHandler.h"
#include"UIHandler.h"
using namespace std;

class SelectState :public GameState {
public:
	SelectState() {
	}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual Game_State getStateID() const { return selectID; }
private:
	static const Game_State selectID;

};
class MenuState :public GameState {
public:
	MenuState(){
	}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual Game_State getStateID() const { return menuID; }
private:
	static const Game_State menuID;
};