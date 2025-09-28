#include "Game.h"
#include<cmath>
#include<numeric>
#include<algorithm>
//Game* Game::_instance = NULL;
void Game::update() {
	Ball::instance().update();
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_W)) {
		player1->moveUp();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) {
		player1->moveDown();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_UP)) {
		player2->moveUp();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN)) {
		player2->moveDown();
	}
	checkCollision(player1);
	checkCollision(player2);
	// wall collision
	if (Ball::instance().position.getY() <= 58 || Ball::instance().position.getY() + 25 >= 730) {
		Ball::instance().velocity.setY(-1 * Ball::instance().velocity.getY());
	}

}
void Game::render()
{

	SDL_SetRenderDrawColor(mainRenderer, 50, 50, 50, 255);
	SDL_RenderClear(mainRenderer);
	player1->render(mainRenderer);
	player2->render(mainRenderer);
	renderMap();
	Ball::instance().render(mainRenderer,ballTexture);
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
	return true;
}

void Game::inputHandler()
{
	InputHandler::Instance().update();
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
float dotProduct(Vector2D v1,Vector2D v2) {
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}
bool Game::checkCollision(Paddle *p)
{
	//vector<vector<vector<Uint8>>> ballAsMatrix = storeImageAsMatrix(ballFilePath);
	//ball collision
	float px1 = p->position.getX();
	float py1 = p->position.getY();
	float px2 = p->position.getX()+10;
	float py2 = p->position.getY() + 100;

	float cx = Ball::instance().position.getX() +25/ 2.0f;
	float cy = Ball::instance().position.getY() +25 / 2.0f;
	float r = 25 / 2.0f;

	float closestX = clamp(cx, px1, px2);
	float closestY = clamp(cy, py1, py2);

	float dx = cx - closestX;
	float dy = cy - closestY;

	Vector2D N(dx, dy);
	Vector2D *V = &Ball::instance().velocity;
	N.normalize();
	//v' = v - (1 + e) * (v · n) * n
	// dx,dy from closest point to center
	if (dx * dx + dy * dy <= r * r) {
		*V = *V - N*2 * dotProduct(N, *V);
		return true;
	}
	return false;
}


