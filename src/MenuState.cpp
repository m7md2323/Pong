#include"MenuState.h"

const string MenuState::menuID = "MENU";
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