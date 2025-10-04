#include "GraphicsHandler.h"
void GraphicsHandler::drawLine(int start, int end, int width, int height, bool dashed, bool VerOrHor)
{
	SDL_FRect rectForLine;

	//the color of the line is white
	SDL_SetRenderDrawColor(mainRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	if (VerOrHor == true) {
		//vertical 
		rectForLine.x = start;
		rectForLine.y = 0;
		rectForLine.w = width;
		rectForLine.h = height;
	}
	else {
		//horizontal 
		rectForLine.x = 0;
		rectForLine.y = start;
		rectForLine.w = width;
		rectForLine.h = height;
	}
	//the offset for making a space between the dashes or no dashes in the case of a straight line
	int offset;
	if (dashed)offset = height + height / 4;
	else offset = height;
	while (rectForLine.y <= end && rectForLine.x <= end) {
		SDL_RenderFillRect(mainRenderer, &rectForLine);
		if (VerOrHor)rectForLine.y += offset;
		else rectForLine.x += offset;
	}

}
void GraphicsHandler::renderScore(int score,bool player)
{
	//left player score
	SDL_FRect sourceRect, destRect;

	sourceRect.x = (scoreTexture->w / 10) * score;
	sourceRect.y = 0;
	sourceRect.w = scoreTexture->w / 10;
	sourceRect.h = scoreTexture->h;
	if(player==0)destRect.x = 500;
	else destRect.x = windowWidth-500;

	destRect.y = 100;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(mainRenderer, scoreTexture, &sourceRect, &destRect);

}
void GraphicsHandler::renderGraphics()
{

		SDL_SetRenderDrawColor(mainRenderer, 50, 50, 50, 255);
		SDL_RenderClear(mainRenderer);

		renderClassicMap();
		Ball::instance().render(mainRenderer, ballTexture);
		//SDL_RenderPresent(mainRenderer);
}
bool GraphicsHandler::init(int _windowWidth, int _windowHeight)
{
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
	//initialize the SDL library
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) == false) {
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return false;
	}

	//if initialization went right, create main window and create renderer
	SDL_CreateWindowAndRenderer("Pong Game", windowWidth, windowHeight, NULL, &mainWindow, &mainRenderer);
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
	//initSpeedForBall();
	// if everything went right, return true 
	return true;
}
bool GraphicsHandler::loadMedia()
{
	string ballFilePath = "../assets/theBall.png";
	string fancyBall = "../assets/fancy-ball.png";
	string scoreFilePath = "../assets/0To9_Score(1).png";

	ballTexture = IMG_LoadTexture(mainRenderer, fancyBall.c_str());
	if (ballTexture == NULL) {
		SDL_Log("image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
	scoreTexture = IMG_LoadTexture(mainRenderer, scoreFilePath.c_str());
	if (scoreTexture == NULL) {
		SDL_Log("image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
void GraphicsHandler::renderClassicMap()
{

	//render vertical dashed line in the middle
	drawLine(windowWidth / 2, windowHeight, 5, 35, true, true);
	//render the upper horizontal non-dashed line 
	drawLine(0, windowWidth, 35, 15, false, false);
	//render the lower horizontal non-dashed line 
	drawLine(windowHeight-15, windowWidth, 35, 15, false, false);
	Ball::instance().render(mainRenderer, ballTexture);
}
void GraphicsHandler::clean() {
	//to avoid memory leakes
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyTexture(ballTexture);

	//to avoid dangling pointers
	mainWindow = nullptr;
	mainRenderer = nullptr;
	ballTexture = nullptr;
	cout << "cleaned graphics\n";

}

GraphicsHandler::GraphicsHandler()
{
}

GraphicsHandler::~GraphicsHandler()
{
	clean();
}
