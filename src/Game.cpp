#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {

	
	Ball::instance().update(leftPlayer,rightPlayer);
	//Ball::instance().update(leftPlayer);

	leftPlayer->update();
	rightPlayer->update();

	//updateScore();
}

void Game::render()
{
	SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 50, 50, 50, 255);
	//
	SDL_RenderClear(GraphicsHandler::instance().getRenderer());
	GraphicsHandler::instance().renderClassicMap();
	leftPlayer->render(GraphicsHandler::instance().getRenderer(),0);
	rightPlayer->render(GraphicsHandler::instance().getRenderer(),0);
	
	
	
	//GraphicsHandler::instance().renderClassicMap();
	//GraphicsHandler::instance().renderFancyMap();
	//Ball::instance().render(GraphicsHandler::instance().getRenderer());
	GraphicsHandler::instance().renderScore(leftPlayer->getScore(), 1);
	GraphicsHandler::instance().renderScore(rightPlayer->getScore(), 0);

	SDL_RenderPresent(GraphicsHandler::instance().getRenderer());
}
Game::Game():leftPlayer{NULL}, rightPlayer{NULL}
{
	leftPlayer = new Paddle(40, GraphicsHandler::instance().getWindowHeight()/2,"left");
	rightPlayer = new Paddle(800-60, GraphicsHandler::instance().getWindowHeight() / 2,"right");
	//rightPlayer->position.setX(rightPlayer->position.getX() + 1000);
	rightPlayerScore = 0;
	leftPlayerScore = 0;
	speed =6;
}

Game::~Game()
{
	clean();
}

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
	GraphicsHandler::instance().init(800,600);
	leftPlayer->init();
	rightPlayer->init();
	//initialize Media and Graphics
	initSpeedForBall();
	// if everything went right, return true 
	return true;
}

void Game::inputHandler()
{
	InputHandler::Instance().update();

}


void Game::initSpeedForBall()
{
	/*random_device rd;*/
	// Non-deterministic random number generator
	//std::mt19937 gen(rd()); // Seed with random_device
	// Alternatively, for reproducible sequences or if random_device is not available:
	mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<> distrib(-30.0f, 30.0f); // Numbers between -30.0 and 30.0 (inclusive)
	float randomNumber = distrib(gen);
	float angle = randomNumber*numbers::pi / 180.0f;

	int dir = rand() % 2 == 0 ? 1 : -1;
	Vector2D velocity(dir * speed * cos(angle), speed * sin(angle));
	Ball::instance().velocity = velocity;

}
/**/
void Game::mainMenu()
{
	//load media
	//show play and quit buttons 
	//after play show modes (fancy, classic, more than two players)
	//enter the game after that
	//build state machine class
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