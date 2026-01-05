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
	InputHandler::Instance().update();
	switch (GameStateMachine::topState()->getStateID()) {
		case MENU:
			if (UIHandler::instance().onButtonClicked(PLAY_BUTTON)) {
				GameStateMachine::changeState(new SelectState());
				SDL_Delay(250);
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
				SDL_Delay(500);
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