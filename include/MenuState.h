#pragma once
#include"GameState.h"
//#include"PlayState.h"
#include"GraphicsHandler.h"
#include"UIHandler.h"
using namespace std;

class MenuState :public GameState {
public:
	MenuState(){
	}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return menuID; }
private:
	static const string menuID;
};