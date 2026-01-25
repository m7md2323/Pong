#include"PauseState.h"

const Game_State PauseState::pauseID = PAUSE;
void PauseState::update() {
	//GraphicsHandler::instance().renderButton(PLAY_BUTTON,200,50);
	//GraphicsHandler::instance().renderButton(EXIT_BUTTON);
}
void PauseState::render() {
	//SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 255, 255, 255, 255);
	//SDL_RenderClear(GraphicsHandler::instance().getRenderer());
	UIHandler::instance().renderPause();
}
bool PauseState::onEnter() {
	UIHandler::instance().setPauseLayout();
	cout << "Entering Pause state\n";
	return true;
}
bool PauseState::onExit() { return false; }