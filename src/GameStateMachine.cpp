#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* state)
{
	gameStates.push(state);
}

void GameStateMachine::changeState(GameState* state)
{
	if (!gameStates.empty()) {
		if (state->getStateID() != gameStates.top()->getStateID()) {
			delete gameStates.top();
			gameStates.pop();
		}
		else return;
	}
	gameStates.push(state);
}

void GameStateMachine::popState()
{
	if (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}
