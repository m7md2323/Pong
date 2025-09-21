#include "/Pong/PongGame/include/Game.h"
Game* Game::_instance = NULL;

Game* Game::instance()
{
	if (_instance == NULL) {
		_instance=new Game();
	}
	return _instance;
}

Game::Game():mainWindow{ NULL },mainRenderer{NULL}
{

}

Game::~Game()
{
	clean();
}


bool Game::init()
{
	//initialize the SDL library
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) == false) {
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return false;
	}
	
	//if initialization went right, create main window
	mainWindow = SDL_CreateWindow("Pong Game", 640, 480, NULL);
	if (mainWindow == NULL) {
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}

	//if creating the main window went right, create main renderer
	//and renderer is the class where you will be able to upload graphics (sprit sheets) using the GPU
	mainRenderer = SDL_CreateRenderer(mainWindow,NULL);
	if (mainRenderer == NULL) {
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
	}

	// if everything went right, return true 
	return true;
}

void Game::clean()
{
	//to avoid memory leaks
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	delete _instance;
	//to avoid dangling pointers
	mainRenderer = NULL;
	mainWindow = NULL;
	_instance = NULL;
}
