#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {
	Ball::instance().update();
	if (checkCollision())cout << "Ball Col\n";
}
void Game::render()
{

	SDL_SetRenderDrawColor(mainRenderer, 50, 50, 50, 255);
	SDL_RenderClear(mainRenderer);
	player1->render(mainRenderer);
	player2->render(mainRenderer);
	Ball::instance().render(mainRenderer,ballTexture);
	renderMap();
	SDL_RenderPresent(mainRenderer);
}
Game::Game():mainWindow{ NULL },mainRenderer{NULL},player1{NULL},player2{NULL}
{
	player1 = new Paddle();
	player2 = new Paddle();
	player2->position.setX(player1->position.getX() + 900);
	windowWidth = 1200;
	windowHeight = 800;
	graphicsOffset = 43;
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
	//and renderer is the class where you will be able to upload graphics (sprit sheets) using the GPU
	if (mainRenderer == NULL) {
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//initialize Media and Graphics
	if (loadMedia() == false) {
		SDL_Log("Media could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//build characters
	//player1 = new Paddle();
	
	// if everything went right, return true 
	checkCollision();
	return true;
}

void Game::inputHandler()
{
	InputHandler::Instance().update(player1);
	InputHandler::Instance().update(player2);
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
	ballFilePath = "../assets/theBall.png";
	ballTexture = IMG_LoadTexture(mainRenderer, ballFilePath.c_str());
	if (ballTexture == NULL) {
		SDL_Log("image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
}

void Game::renderMap()
{

	//render vertical dashed line in the middle
	renderLine(windowWidth / 2, windowHeight - graphicsOffset, true, true);
	//render the upper horizontal non-dashed line 
	renderLine(graphicsOffset, windowWidth - graphicsOffset, false, false);
	//render the lower horizontal non-dashed line 
	renderLine(windowHeight - graphicsOffset, windowWidth - graphicsOffset, false, false);
}

void Game::renderLine(int start,int end,bool dashed, bool VerOrHor)
{
	SDL_FRect rectForLine;

	//the color of the line is white
	SDL_SetRenderDrawColor(mainRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	if (VerOrHor == true) {
		//vertical 
		rectForLine.x = start;
		rectForLine.y = graphicsOffset;
		rectForLine.w = 15;
		rectForLine.h = 35;
	}
	else {
		//horizontal 
		rectForLine.x = graphicsOffset;
		rectForLine.y = start;
		rectForLine.w = 35;
		rectForLine.h = 15;
	}
	//the offset for making a space between the dashes or no dashes in the case of a straight line
	int offset;
	if (dashed)offset = 35 + 35 / 4;
	else offset = 35;
	while(rectForLine.y<=end && rectForLine.x <=end){
		SDL_RenderFillRect(mainRenderer, &rectForLine);
		if (VerOrHor)rectForLine.y += offset;
		else rectForLine.x += offset;
	}

}
bool Game::checkCollision()
{
	//vector<vector<vector<Uint8>>> ballAsMatrix = storeImageAsMatrix(ballFilePath);
	int x1Ball = Ball::instance().position.getX() + 2;
	int y1Ball = Ball::instance().position.getY() + 1;
	int x2Ball = Ball::instance().position.getX() + 24;
	int y2Ball = Ball::instance().position.getY() +24;

	int x1Player1 =player1->position.getX();
	int y1Player1 =player1->position.getY();
	int x2Player1 = player1->position.getX()+10;
	int y2Player1 = player1->position.getY() + 100;

	int x1Player2 = player2->position.getX();
	int y1Player2 = player2->position.getY();
	int x2Player2 = player2->position.getX()+10;
	int y2Player2 = player2->position.getY()+100;


	if (x1Ball <= x1Player1&& y1Ball >= y1Player1 && y1Ball <= y2Player1) {
		Ball::instance().velocity *= -1;
		return true;
	}
	if (x1Ball >= x1Player2 && y1Ball >= y1Player2 && y1Ball <= y2Player2) {
		Ball::instance().velocity *= -1;
		return true;
	}
	return false;
}


