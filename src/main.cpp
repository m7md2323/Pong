#include"Game.h"
using namespace std;

const int TARGET_FPS =90;
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

		Game::instance().inputHandler();
		Game::instance().update();
		Game::instance().render();

		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY_MS > frameTime) {
			//SDL_Delay(FRAME_DELAY_MS - frameTime); // Delay if frame rendered too fast
		}
	}
	//Game::instance().clean();

	return 0;
}