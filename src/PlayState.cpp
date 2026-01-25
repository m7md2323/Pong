#include"PlayState.h"
const Game_State PlayState::playID = PLAYING;
Map_Mode PlayState::mapModeState;
Winner PlayState::whoWon = NO_ONE;

PlayState::PlayState():leftPlayer{ NULL }, rightPlayer{ NULL }
{
	leftPlayer = new Paddle(40, GraphicsHandler::instance().getWindowHeight() / 2, "left");
	rightPlayer = new Paddle(800 - 60, GraphicsHandler::instance().getWindowHeight() / 2, "right");
	Ball::instance().resetBall();
}
void PlayState::render() {
	SDL_SetRenderDrawColor(GraphicsHandler::instance().getRenderer(), 50, 50, 50, 255);
	SDL_RenderClear(GraphicsHandler::instance().getRenderer());

	if(mapModeState ==FANCY)
	GraphicsHandler::instance().renderFancyMap();
	else GraphicsHandler::instance().renderClassicMap();

	leftPlayer->render(GraphicsHandler::instance().getRenderer(), mapModeState);
	rightPlayer->render(GraphicsHandler::instance().getRenderer(), mapModeState);

	GraphicsHandler::instance().renderScore(leftPlayer->getScore(), "left");
	GraphicsHandler::instance().renderScore(rightPlayer->getScore(), "right");
}
bool PlayState::onEnter()
{
	Ball::instance().resetBall();
	cout << "Entering Play state!!\n";
	return true;
}
void PlayState::init()
{
	rightPlayer->init();
	leftPlayer->init();
}
bool PlayState::onExit()
{
	return true;
}

void PlayState::update() {
	if (leftPlayer->getScore() == 10)whoWon = LEFT_PLAYER;
	if (rightPlayer->getScore() == 10)whoWon = RIGHT_PLAYER;

	Ball::instance().update(leftPlayer, rightPlayer);

	leftPlayer->update();
	rightPlayer->update();
}
void PlayState::clean() {
	//to avoid memory leaks
	delete leftPlayer;
	delete rightPlayer;
	//to avoid dangling pointers
	leftPlayer = NULL;
	rightPlayer = NULL;
}