#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {
	cout << "Inside Game Update\n";
	Ball::instance().update();
}
void Game::render()
{

	SDL_SetRenderDrawColor(mainRenderer, 50, 50, 50, 255);
	SDL_RenderClear(mainRenderer);
	player1->render(mainRenderer);
	/*SDL_FRect rect1, rect2, rect3;
	rect1.x = rect1.y = 0;
	rect1.w = windowWidth;
	rect1.h = windowHeight;

	rect2.x = rect2.y = 5;
	rect2.w = windowWidth -10;
	rect2.h = windowHeight -10;

	rect3.x = 0; rect3.y = 150;
	rect3.w = windowWidth;
	rect3.h = windowHeight - 300;

	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(mainRenderer, &rect1);

	SDL_SetRenderDrawColor(mainRenderer, 123, 321, 123, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(mainRenderer, &rect2);

	SDL_SetRenderDrawColor(mainRenderer, 123, 321, 123, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(mainRenderer, &rect3);
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	SDL_RenderLine(mainRenderer, windowWidth/2,0, windowWidth / 2, windowHeight);*/

	Ball::instance().render(mainRenderer,ballTexture);
	
	renderDashedLine(windowWidth/2, windowHeight-graphicsOffset, 1);
	renderDashedLine(graphicsOffset, windowWidth - graphicsOffset,0);
	renderDashedLine(windowHeight-graphicsOffset, windowWidth - graphicsOffset, 0);
	SDL_RenderPresent(mainRenderer);
}
Game::Game():mainWindow{ NULL },mainRenderer{NULL},player1{NULL},player2{NULL}
{
	windowWidth = 1200;
	windowHeight = 800;
	graphicsOffset = 43;
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
	
	//if initialization went right, create main window and create renderer
	SDL_CreateWindowAndRenderer("Pong Game", windowWidth, windowHeight, NULL,&mainWindow,&mainRenderer);
	if (mainWindow == NULL) {
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//if creating the main window went right, create main renderer
	//and renderer is the class where you will be able to upload graphics (sprit sheets) using the GPU
	if (mainRenderer == NULL) {
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
	}
	//initialize Media
	if (loadMedia() == false) {
		SDL_Log("Media could not be loaded ! SDL error: %s\n", SDL_GetError());
	}
	//initialize graphics
	initGraphics();
	player1 = new Paddle();
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
	ballTexture = IMG_LoadTexture(mainRenderer, "../assets/theBall.png");
	if (ballTexture == NULL) {
		SDL_Log("image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
}

void Game::renderDashedLine(int start,int end, bool VerOrHor)
{
	SDL_FRect rectForDashedLine;

	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	if (VerOrHor == true) {
		//vertical dem
		rectForDashedLine.x = start+15;
		rectForDashedLine.y = graphicsOffset;
		rectForDashedLine.w = 10;
		rectForDashedLine.h = 35;
	}
	else {
		rectForDashedLine.x = graphicsOffset;
		rectForDashedLine.y = start;
		rectForDashedLine.w = 35;
		rectForDashedLine.h = 10;
	}
	int offset = 35 + 35 / 4;
	while(rectForDashedLine.y<=end && rectForDashedLine.x <=end){
		SDL_RenderFillRect(mainRenderer, &rectForDashedLine);
		if (VerOrHor)rectForDashedLine.y += offset;
		else rectForDashedLine.x += offset;
	}

}

void Game::initGraphics()
{
	//for the dashedLines
	//each line is 5 width and 30 in height
}
