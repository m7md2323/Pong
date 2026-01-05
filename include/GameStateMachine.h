#pragma once

#include"GameState.h"
#include<stack>
using namespace std;
class GameStateMachine
{
public:
	static GameState* topState() {if(!gameStates.empty())return gameStates.top(); };
	static void pushState(GameState* state);
	static void changeState(GameState* state);
	static void popState();
private:
	static stack<GameState*> gameStates;
};