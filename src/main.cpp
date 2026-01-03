#include"Game.h"
using namespace std;

int main() {
	if (Game::instance().init() == false) {
		cout << "SDL could not be init\n";
		return 0;
	}
	while (InputHandler::Instance().gameRunning()) {

		Game::instance().inputHandler();
		Game::instance().update();
		Game::instance().render();

		SDL_SetRenderVSync(GraphicsHandler::instance().getRenderer(), 1);
	}

	return 0;
}