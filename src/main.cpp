#include<iostream>
#include<SDL3/SDL.h>
#include"Game.h"
using namespace std;
const int TARGET_FPS = 60;
const int FRAME_DELAY_MS = 1000 / TARGET_FPS;

Uint32 frameStart;
int frameTime;
int main() {
	if (Game::instance().init() == false) {
		cout << "SDL could not be init\n";
		return 0;
	}
	while (InputHandler::Instance().gameRunning()) {
		frameStart = SDL_GetTicks();
		//cout << "TEST1\n";
		Game::instance().inputHandler();
		//cout << "TEST2\n";
		Game::instance().update();
		//cout << "TEST3\n";
		Game::instance().render();
		//cout << "TEST4\n";
		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY_MS > frameTime) {
			SDL_Delay(FRAME_DELAY_MS - frameTime); // Delay if frame rendered too fast
		}
	}
	Game::instance().clean();

	return 0;
}