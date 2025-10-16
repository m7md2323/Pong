#pragma

#include"GameState.h"
#include<stack>
using namespace std;

class GameStateMachine
{
public:
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
private:
	stack<GameState*> gameStates;
};