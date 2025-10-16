#pragma
#include"GameState.h"
using namespace std;

class MenuState:GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return menuID; }
private:
	static const string menuID;
};