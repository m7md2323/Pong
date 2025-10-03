#include "Game.h"
//Game* Game::_instance = NULL;
void Game::update() {
	Ball::instance().update();
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_W)) {
		leftPlayer->moveUp();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) {
		leftPlayer->moveDown();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_UP)) {
		rightPlayer->moveUp();
	}
	if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN)) {
		rightPlayer->moveDown();
	}
	if (checkCollision(leftPlayer) ||
		checkCollision(rightPlayer)) {
		Ball::instance().speedUp(1.05f, 9);
	}
	// wall collision
	if (Ball::instance().position.getY() <= 58 || Ball::instance().position.getY() + 25 >= 754) {
		Ball::instance().velocity.setY(-1 * Ball::instance().velocity.getY());
	}

	updateScore();
}

void Game::render()
{

	SDL_SetRenderDrawColor(mainRenderer, 50, 50, 50, 255);
	SDL_RenderClear(mainRenderer);
	leftPlayer->render(mainRenderer);
	rightPlayer->render(mainRenderer);
	renderMap();
	Ball::instance().render(mainRenderer,ballTexture);
	renderScore();
	SDL_RenderPresent(mainRenderer);
}
Game::Game():mainWindow{ NULL },mainRenderer{NULL},ballTexture{NULL},scoreTexture{NULL}, leftPlayer{NULL}, rightPlayer{NULL}
{
	leftPlayer = new Paddle(8,80);
	rightPlayer = new Paddle(8,80);
	rightPlayer->position.setX(rightPlayer->position.getX() + 1000);
	graphicsOffset = 43;
	rightPlayerScore = 0;
	leftPlayerScore = 0;
	speed = 6;
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


bool Game::init(int _windowWidth, int _windowHeight)
{
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
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
	initSpeedForBall();
	// if everything went right, return true 
	return true;
}

void Game::inputHandler()
{
	InputHandler::Instance().update();
}



bool Game::loadMedia()
{
	ballFilePath = "../assets/theBall.png";
	string scoreFilePath = "../assets/0To9_Score(1).png";

	ballTexture = IMG_LoadTexture(mainRenderer, ballFilePath.c_str());
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

void Game::renderMap()
{

	//render vertical dashed line in the middle
	renderLine(windowWidth / 2, windowHeight - graphicsOffset, 5,35,true, true);
	//render the upper horizontal non-dashed line 
	renderLine(graphicsOffset, windowWidth - graphicsOffset,35,15, false, false);
	//render the lower horizontal non-dashed line 
	renderLine(windowHeight - graphicsOffset, windowWidth - graphicsOffset,35,15, false, false);
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

void Game::renderScore()
{
	//left player score
	SDL_FRect sourceRect, destRect;

	sourceRect.x = (scoreTexture->w / 10) * leftPlayerScore;
	sourceRect.y = 0;
	sourceRect.w = scoreTexture->w/10;
	sourceRect.h = scoreTexture->h;

	destRect.x = 500;
	destRect.y = 100;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(mainRenderer, scoreTexture, &sourceRect, &destRect);
	//right player score
	sourceRect.x = (scoreTexture->w / 10) * rightPlayerScore;
	sourceRect.y = 0;
	sourceRect.w = scoreTexture->w / 10;
	sourceRect.h = scoreTexture->h;

	destRect.x = 700;
	destRect.y = 100;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(mainRenderer, scoreTexture, &sourceRect, &destRect);
}

void Game::updateScore()
{
	int ballX = Ball::instance().position.getX();
	int ballY = Ball::instance().position.getY();

	bool leftSideGoal = ballX + 25 < 0;
	bool rightSideGoal =ballX>windowWidth;
	
	if (leftSideGoal || rightSideGoal) {
		if (leftSideGoal) {
			rightPlayerScore++;
		}
		if (rightSideGoal) {
			leftPlayerScore++;
		}
		Ball::instance().position = Vector2D(windowWidth / 2, windowHeight / 2);
		initSpeedForBall();
	}
	//cout << leftPlayerScore << " " << rightPlayerScore << "\n";
	//Ball::instance().position = Vector2D(windowHeight / 2, windowHeight / 2);
	//updateScore();
	//update score on screen


}


void Game::renderLine(int start,int end,int width,int height,bool dashed, bool VerOrHor)
{
	SDL_FRect rectForLine;

	//the color of the line is white
	SDL_SetRenderDrawColor(mainRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	if (VerOrHor == true) {
		//vertical 
		rectForLine.x = start;
		rectForLine.y = graphicsOffset;
		rectForLine.w = width;
		rectForLine.h = height;
	}
	else {
		//horizontal 
		rectForLine.x = graphicsOffset;
		rectForLine.y = start;
		rectForLine.w = width;
		rectForLine.h = height;
	}
	//the offset for making a space between the dashes or no dashes in the case of a straight line
	int offset;
	if (dashed)offset = height + height / 4;
	else offset = height;
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
	float px2 = p->position.getX()+p->getWidth();
	float py2 = p->position.getY()+p->getHeight();

	float cx = Ball::instance().getCenterX();
	float cy = Ball::instance().getCenterY();
	float r = Ball::instance().getRadis();

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
		//speedUpBall();
		Vector2D N(dx, dy);
		float dist = sqrtf(dx * dx + dy * dy);

		if (dist == 0) {
			// Edge case: ball center exactly at closest point
			N = Vector2D(1, 0);
			dist = 1;
		}
		else {
			N /= dist; // normalize
		}

		// Move ball out of collision
		float penetration = r - dist;
		Ball::instance().position += N * penetration;

		// Reflect velocity
		Vector2D* V = &Ball::instance().velocity;
		float e = 1.0f;
		*V = *V - N * (1 + e) * dotProduct(N, *V);

		return true;
	}
	return false;
}

void Game::clean()
{
	//to avoid memory leaks
	
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyTexture(ballTexture);
	
	leftPlayer->clean();
	rightPlayer->clean();
	delete leftPlayer;
	delete rightPlayer;
	//to avoid dangling pointers
	leftPlayer = NULL;
	rightPlayer = NULL;
	ballTexture = NULL;
	mainRenderer = NULL;
	mainWindow = NULL;
	cout << "cleaned\n";
}