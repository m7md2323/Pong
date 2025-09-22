#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {
	cout << "Inside Game Update\n";
	Ball::instance().update();
}
void Game::render()
{
	SDL_RenderClear(mainRenderer);
	Ball::instance().render(mainRenderer,ballTexture);
	SDL_RenderPresent(mainRenderer);
}
Game::Game():mainWindow{ NULL },mainRenderer{NULL},player1{NULL},player2{NULL}
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
	SDL_CreateWindowAndRenderer("Pong Game", 640, 480, NULL,&mainWindow,&mainRenderer);
	if (mainWindow == NULL) {
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}

	//if creating the main window went right, create main renderer
	//and renderer is the class where you will be able to upload graphics (sprit sheets) using the GPU
	//mainRenderer = SDL_CreateRenderer(mainWindow,NULL);
	if (mainRenderer == NULL) {
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
	}
	if (loadMedia() == false) {
		SDL_Log("Media could not be loaded ! SDL error: %s\n", SDL_GetError());
	}
	// if everything went right, return true 
	return true;
}

void Game::inputHandler(bool &quit)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			quit = true;
			break;
		}

	}
}

void Game::clean()
{
	//to avoid memory leaks

	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	player1->clean();
	player2->clean();
	//delete _instance;
	delete player1;
	delete player2;
	//to avoid dangling pointers
	player1 = NULL;
	player2 = NULL;
	mainRenderer = NULL;
	mainWindow = NULL;
	//_instance = NULL;
}

bool Game::loadMedia()
{
	ballTexture = IMG_LoadTexture(mainRenderer, "D:/Pong/PongGame/assets/theBall.png");
	if (ballTexture == NULL) {
		SDL_Log("image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
}
