#pragma
#include"GameState.h"
using namespace std;
class PlayState:GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return playID; }
private:
	static const string playID;

};