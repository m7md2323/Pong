#pragma once
#include"GameState.h"
#include"Paddle.h"
#include"Ball.h"
#include"GraphicsHandler.h"
#include"InputHandler.h"

using namespace std;
enum Map_Mode {
	CLASSIC,
	FANCY
};
enum Winner {
	NO_ONE,
	LEFT_PLAYER,
	RIGHT_PLAYER
};
class PlayState:public GameState {
public:
	PlayState();
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual Game_State getStateID() const { return playID; }

	void init();
	static void setMapMode(Map_Mode mode) { mapModeState = mode; }
	
	void clean();
	
	static Winner whoWon;
private:
	
	
	static const Game_State playID;

	static Map_Mode mapModeState;

	Paddle* leftPlayer, * rightPlayer;//clean

};