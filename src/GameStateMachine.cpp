#include "GameStateMachine.h"
stack<GameState*> GameStateMachine::gameStates;
void GameStateMachine::pushState(GameState* state)
{
	
	gameStates.push(state);
	gameStates.top()->onEnter();
}

void GameStateMachine::changeState(GameState* state)
{
	if (!gameStates.empty()) {
		if (state->getStateID() != gameStates.top()->getStateID()) {
			gameStates.top()->onExit();
			delete gameStates.top();
			gameStates.pop();
		}
		else return;
	}
	gameStates.push(state);
	gameStates.top()->onEnter();
}

void GameStateMachine::popState()
{
	if (!gameStates.empty()) {
		gameStates.top()->onExit();
		delete gameStates.top();
		gameStates.pop();
	}
}
