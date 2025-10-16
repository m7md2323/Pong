#include"Game.h"
using namespace std;
Uint32 frameStart;
int frameTime;

int main() {
	if (Game::instance().init() == false) {
		cout << "SDL could not be init\n";
		return 0;
	}
	while (InputHandler::Instance().gameRunning()) {

		Game::instance().inputHandler();
		Game::instance().update();
		Game::instance().render();

		frameTime = SDL_GetTicks() - frameStart;
		SDL_SetRenderVSync(GraphicsHandler::instance().getRenderer(), 1);
	}
	//Game::instance().clean();

	return 0;
}