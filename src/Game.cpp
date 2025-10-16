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
		collision = false;
		Ball::instance().speedUp(1.05f, 9);
	}
	else collision = false;;
	// wall collision
	if (Ball::instance().position.getY() <= 15 || Ball::instance().position.getY() + 25 >= GraphicsHandler::instance().getWindowHeight()-15) {
		Ball::instance().velocity.setY(-1 * Ball::instance().velocity.getY());
	}

	updateScore();
}

void Game::render()
{
	//SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 50, 50, 50, 255);
	//
	SDL_RenderClear(GraphicsHandler::instance().getRenderer());
	GraphicsHandler::instance().renderFancyMap();
	leftPlayer->render(GraphicsHandler::instance().getRenderer(),1);
	rightPlayer->render(GraphicsHandler::instance().getRenderer(),1);
	
	
	
	//GraphicsHandler::instance().renderClassicMap();
	//GraphicsHandler::instance().renderFancyMap();
	//Ball::instance().render(GraphicsHandler::instance().getRenderer());
	GraphicsHandler::instance().renderScore(leftPlayerScore, 0);
	GraphicsHandler::instance().renderScore(rightPlayerScore, 1);

	SDL_RenderPresent(GraphicsHandler::instance().getRenderer());
}
Game::Game():leftPlayer{NULL}, rightPlayer{NULL}
{
	leftPlayer = new Paddle(32,120,40, GraphicsHandler::instance().getWindowHeight()/2);
	rightPlayer = new Paddle(32,120,700-40, GraphicsHandler::instance().getWindowHeight() / 2);
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
void Game::updateScore()
{
	int ballX = Ball::instance().position.getX();
	int ballY = Ball::instance().position.getY();

	bool leftSideGoal = ballX + 25 < 0;
	bool rightSideGoal =ballX>GraphicsHandler::instance().getWindowWidth();
	
	if (leftSideGoal || rightSideGoal) {
		if (leftSideGoal) {
			rightPlayerScore++;
		}
		if (rightSideGoal) {
			leftPlayerScore++;
		}
		Ball::instance().position = Vector2D(GraphicsHandler::instance().getWindowWidth() / 2, GraphicsHandler::instance().getWindowHeight() / 2);
		initSpeedForBall();
	}
	//cout << leftPlayerScore << " " << rightPlayerScore << "\n";
	//Ball::instance().position = Vector2D(windowHeight / 2, windowHeight / 2);
	//updateScore();
	//update score on screen


}
void Game::mainMenu()
{
	//load media
	//show play and quit buttons 
	//after play show modes (fancy, classic, more than two players)
	//enter the game after that
	//build state machine class
}
float dotProduct(Vector2D v1,Vector2D v2) {
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}
bool Game::checkCollision(Paddle *p)
{
	//vector<vector<vector<Uint8>>> ballAsMatrix = storeImageAsMatrix(ballFilePath);
	//ball collision
	//paddle
	float px1 = p->position.getX();
	float py1 = p->position.getY();
	float px2 = p->position.getX()+p->getWidth();
	float py2 = p->position.getY()+p->getHeight();
	//ball
	float bx1 = Ball::instance().position.getX();
	float by1 = Ball::instance().position.getY();
	float bx2 = Ball::instance().position.getX() + 25;
	float by2 = Ball::instance().position.getY() + 25;

	//Vector2D N(, dy);
	//Vector2D* V = &Ball::instance().velocity;
	//N.normalize();
	/*if ((bx1 <= px2 && bx1 >= px1 || bx2 >= px1 && bx2 <= px2) && by1 >= py1 && by2 <= py2&&collision==false) {
		Ball::instance().velocity.setX(-1*Ball::instance().velocity.getX());
		collision = true;
		return true;
	}*/











	float cx = Ball::instance().getCenterX();
	float cy = Ball::instance().getCenterY();
	float r = Ball::instance().getRadis();

	float closestX = clamp(cx, px1, px2);
	float closestY = clamp(cy, py1, py2);

	float dx = cx - closestX;
	float dy = cy - closestY;

	//Vector2D N(dx, dy);
	Vector2D *V = &Ball::instance().velocity;
	//N.normalize();
	//v' = v - (1 + e) * (v · n) * n
	// dx,dy from closest point to center
	if ((dx * dx + dy * dy <= r * r)) {
		//collision = true;
	
		float dist = sqrtf(dx * dx + dy * dy);
		Vector2D N(dx, dy);
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
		float e = 0.9f;
		*V = *V - N * (1 + e) * dotProduct(N, *V);
		//V->setX(V->getX() * -1);

		return true;
	}
	return false;
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