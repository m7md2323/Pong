#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {

	GameStateMachine::topState()->update();

}

void Game::render()
{
	
	GameStateMachine::topState()->render();

	SDL_RenderPresent(GraphicsHandler::instance().getRenderer());
}
Game::Game()
{
}

Game::~Game()
{
	clean();
}

bool Game::init()
{
	//initialize Media and Graphics
	if (!GraphicsHandler::instance().init(800, 600)) {
		SDL_Log("init GraphicsHandler object went wrong SDL error: %s\n", SDL_GetError());
		return false;
	}
	// User interface initialization
	if (!UIHandler::instance().init()) {
		SDL_Log("initializing user interface went wrong SDL error: %s\n", SDL_GetError());
		return false;
	}
	InputHandler::Instance().init();

	GameStateMachine::pushState(new MenuState());
	// if everything went right, return true 
	return true;
}

void Game::inputHandler()
{
	InputHandler::Instance().update();
	switch (GameStateMachine::topState()->getStateID()) {
		case MENU:
			if (UIHandler::instance().onButtonClicked(PLAY_BUTTON)) {
				GameStateMachine::changeState(new SelectState());
			}
			else if (UIHandler::instance().onButtonClicked(EXIT_BUTTON)) {
				InputHandler::Instance().exit();
				return;
			}
			
			break;
		case PLAYING:
			if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)|| UIHandler::instance().onButtonClicked(PAUSE_BUTTON)) {
				GameStateMachine::pushState(new PauseState());
			}
			break;
		case PAUSE:
			if (UIHandler::instance().onButtonClicked(PLAY_BUTTON)) {
				GameStateMachine::popState();
			}
			else if (UIHandler::instance().onButtonClicked(MENU_BUTTON)) {
				GameStateMachine::changeState(new MenuState());
			}
			else if (UIHandler::instance().onButtonClicked(EXIT_BUTTON)) {
				InputHandler::Instance().exit();
				return;
			}
			break;
		case MODE_SELECTING:
			if (UIHandler::instance().onButtonClicked(FANCY_MAP_SEL_BUTTON)) {
				PlayState::setMapMode(FANCY);
				GameStateMachine::changeState(new PlayState());
			}
			else if (UIHandler::instance().onButtonClicked(CLASSIC_MAP_SEL_BUTTON)) {
				PlayState::setMapMode(CLASSIC);
				GameStateMachine::changeState(new PlayState());
			}
			break;
		default:break;
	}

}

void Game::clean()
{
	cout << "cleaned game\n";
}