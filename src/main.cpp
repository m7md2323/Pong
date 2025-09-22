#include<iostream>
#include<SDL3/SDL.h>
#include"Game.h"
using namespace std;

int main() {
	//the Game loop
	//Game* theGame = Game::instance();
	bool quit = false;
	SDL_Event event;
	if (Game::instance().init() == false) {
		cout << "SDL could not be init\n";
		return 0;
	}
	while (!quit) {
		cout << "TEST1\n";
		Game::instance().inputHandler(quit);
		cout << "TEST2\n";
		Game::instance().update();
		cout << "TEST3\n";
		Game::instance().render();
		cout << "TEST4\n";
	}
	Game::instance().clean();

	return 0;
}