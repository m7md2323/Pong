#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {

	GameState* gameState = GameStateMachine::topState();
	gameState->update();
	if (gameState->getStateID() == "PLAY") {
		Ball::instance().update(leftPlayer, rightPlayer);
		leftPlayer->update();
		rightPlayer->update();
	}
	else if (gameState->getStateID() == "MENU") {

	}

}

void Game::render()
{
	
	if (GameStateMachine::topState()->getStateID() == "MENU") {
		GameStateMachine::topState()->render();
	}
	else {
		SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 50, 50, 50, 255);
		//
		SDL_RenderClear(GraphicsHandler::instance().getRenderer());
		GraphicsHandler::instance().renderFancyMap();
		leftPlayer->render(GraphicsHandler::instance().getRenderer(), 1);
		rightPlayer->render(GraphicsHandler::instance().getRenderer(), 1);



		//GraphicsHandler::instance().renderClassicMap();
		//GraphicsHandler::instance().renderFancyMap();
		//Ball::instance().render(GraphicsHandler::instance().getRenderer());
		GraphicsHandler::instance().renderScore(leftPlayer->getScore(), 1);
		GraphicsHandler::instance().renderScore(rightPlayer->getScore(), 0);
	}
	SDL_RenderPresent(GraphicsHandler::instance().getRenderer());
}
Game::Game():leftPlayer{NULL}, rightPlayer{NULL}
{
	leftPlayer = new Paddle(40, GraphicsHandler::instance().getWindowHeight()/2,"left");
	rightPlayer = new Paddle(800-60, GraphicsHandler::instance().getWindowHeight() / 2,"right");
}

Game::~Game()
{
	clean();
}
//this function is not used yet, I think its just cool function.
vector<vector<vector<Uint8>>> Game::storeImageAsMatrix(string filePath)
{
	SDL_Surface* tempCopy = IMG_Load(filePath.c_str());
	//creates a 3D matrix to store the pixels values RGBA
	//A image.h X image.w X 4 3D matrix
	vector<vector<vector<Uint8>>> imageMatrix(tempCopy->h, vector<vector<Uint8>>(tempCopy->w, vector<Uint8>(4)));
	for (int i = 0; i < tempCopy->h; ++i) {
		for (int j = 0; j < tempCopy->w; ++j) {
			imageMatrix[i][j][0] = 0; // Initialize
			imageMatrix[i][j][1] = 0;
			imageMatrix[i][j][2] = 0;
			imageMatrix[i][j][3] = 0;
		}
	}
	SDL_LockSurface(tempCopy);

	for (int i = 0; i < tempCopy->h; ++i) {
		for (int j = 0; j < tempCopy->w; ++j) {
			// Get the color at (x, y)
			Uint32 pixelColor = *(Uint32*)((Uint8*)tempCopy->pixels + i * tempCopy->pitch + j * SDL_GetPixelFormatDetails(tempCopy->format)->bytes_per_pixel);

			// Convert to RGBA
			SDL_Color color;
			SDL_GetRGBA(pixelColor, SDL_GetPixelFormatDetails(tempCopy->format), NULL, &color.r, &color.g, &color.b, &color.a);

			// Store in your matrix
			imageMatrix[i][j][0] = color.r;
			imageMatrix[i][j][1] = color.g;
			imageMatrix[i][j][2] = color.b;
			imageMatrix[i][j][3] = color.a;
		}
	}
	SDL_UnlockSurface(tempCopy);
	return imageMatrix;
}


bool Game::init()
{
	//initialize Media and Graphics
	if (!GraphicsHandler::instance().init(800, 600)) {
		SDL_Log("init GraphicsHandler object went wrong SDL error: %s\n", SDL_GetError());
		return false;
	}
	// Paddle init function always returs true because its only the Graphics handler passing the right dimenstions for Paddles
	if (!leftPlayer->init() || !rightPlayer->init()) {
		SDL_Log("init Players objects went wrong SDL error: %s\n", SDL_GetError());
		return false;
	}
	// User interface initialization
	if (!UIHandler::instance().init()) {
		SDL_Log("initializing user interface went wrong SDL error: %s\n", SDL_GetError());
		return false;
	}
	GameStateMachine::pushState(new MenuState());
	// if everything went right, return true 
	return true;
}

void Game::inputHandler()
{
	if(UIHandler::instance().onPlayClicked()){
		GameStateMachine::changeState(new PlayState());
	}
	InputHandler::Instance().update();
}

void Game::clean()
{
	//to avoid memory leaks
	leftPlayer->clean();
	rightPlayer->clean();
	delete leftPlayer;
	delete rightPlayer;
	//to avoid dangling pointers
	leftPlayer = NULL;
	rightPlayer = NULL;
	cout << "cleaned game\n";
}