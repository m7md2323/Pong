#include"MenuState.h"

const Game_State MenuState::menuID = MENU;
const Game_State SelectState::selectID = MODE_SELECTING;
void MenuState::update() {
	//GraphicsHandler::instance().renderButton(PLAY_BUTTON,200,50);
	//GraphicsHandler::instance().renderButton(EXIT_BUTTON);
}
void MenuState::render() {
	SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(GraphicsHandler::instance().getRenderer());
	UIHandler::instance().renderMenu();
	//GraphicsHandler::instance().renderButton(EXIT_BUTTON);
}
bool MenuState::onEnter() { 
	
	cout << "Entering Menu state\n";
	return false; 
}
bool MenuState::onExit() { return false; }

///////////////////////////////////////////////////////////////
void SelectState::update() {
	//GraphicsHandler::instance().renderButton(PLAY_BUTTON,200,50);
	//GraphicsHandler::instance().renderButton(EXIT_BUTTON);
}
void SelectState::render() {
	SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(GraphicsHandler::instance().getRenderer());
	UIHandler::instance().renderModeSelect();
	//GraphicsHandler::instance().renderButton(EXIT_BUTTON);
}
bool SelectState::onEnter() {

	cout << "Entering Select state state\n";
	return false;
}
bool SelectState::onExit() { return false; }