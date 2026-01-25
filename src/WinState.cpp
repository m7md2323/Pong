#include"WinState.h"

const Game_State WinState::winID = WIN;
void WinState::update() {

}
void WinState::render() {
    
	if(PlayState::whoWon==LEFT_PLAYER)
		UIHandler::instance().renderWin(LEFT_PLAYER_WINNER);
	if (PlayState::whoWon == RIGHT_PLAYER)
		UIHandler::instance().renderWin(RIGHT_PLAYER_WINNER);
}
bool WinState::onEnter() {
	UIHandler::instance().setWinLayout();
	cout << "Entering Win state\n";
	return true;
}
bool WinState::onExit() { return false; }