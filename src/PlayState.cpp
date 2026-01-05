#include"PlayState.h"
const Game_State PlayState::playID = PLAYING;
Map_Mode PlayState::mapModeState;
PlayState::PlayState():leftPlayer{ NULL }, rightPlayer{ NULL }
{
	leftPlayer = new Paddle(40, GraphicsHandler::instance().getWindowHeight() / 2, "left");
	rightPlayer = new Paddle(800 - 60, GraphicsHandler::instance().getWindowHeight() / 2, "right");
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
	return true;
}
void PlayState::init()
{
	rightPlayer->init();
	leftPlayer->init();
}
bool PlayState::onExit()
{
	return false;
}

void PlayState::update() {
	Ball::instance().update(leftPlayer, rightPlayer);
	leftPlayer->update();
	rightPlayer->update();
}
void PlayState::clean() {
	//to avoid memory leaks
	leftPlayer->clean();
	rightPlayer->clean();
	delete leftPlayer;
	delete rightPlayer;
	//to avoid dangling pointers
	leftPlayer = NULL;
	rightPlayer = NULL;
}