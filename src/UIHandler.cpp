#include"UIHandler.h"

bool UIHandler::init() {
	if (!load("../assets/PlayButton.png", PLAY_BUTTON)) {
		SDL_Log("Media playButton could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!load("../assets/PongLogo.png",PONG_LOGO)) {
		SDL_Log("Media PongLogo could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//init buttons objects
	buttons[PLAY_BUTTON] = new Button(PLAY_BUTTON, Vector2D(300, 300), buttonsTexture[PLAY_BUTTON]->w, buttonsTexture[PLAY_BUTTON]->h);
	buttons[PONG_LOGO] = new Button(PONG_LOGO, Vector2D(130, 50), buttonsTexture[PONG_LOGO]->w, buttonsTexture[PONG_LOGO]->h);
	return true;

}

bool UIHandler::load(string filePath,Button_Type type)
{
	
		buttonsTexture[type] = new SDL_Texture();

		buttonsTexture[type] = IMG_LoadTexture(GraphicsHandler::instance().getRenderer(), filePath.c_str());
		if (buttonsTexture[type] == NULL) {
			SDL_Log(filePath.c_str());
			SDL_Log("Image could not be loaded!! SDL error: %s\n", SDL_GetError());
			return false;
		}
	return true;
}

void UIHandler::renderMenu()
{
	renderLogo();
	renderButton(PLAY_BUTTON);
}

void UIHandler::renderButton(Button_Type type)
{
	SDL_Texture* tempButtonTex=buttonsTexture[type];
	Button* tempButton = buttons[type];

	int x = tempButton->buttonPos.getX();
	int y = tempButton->buttonPos.getY();
	int w = tempButton->width;
	int h = tempButton->height;
	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = w/2;
	sourceRect.h = h;
	if (InputHandler::Instance().mouseOverObject(x, y, w/2, h)) {
		sourceRect.x = w / 2;
	}
	//sourceRect.w /= 2;
	destRect.x = x;
	destRect.y = y;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(GraphicsHandler::instance().getRenderer(), tempButtonTex, &sourceRect, &destRect);
}

void UIHandler::renderLogo()
{
	SDL_Texture* tempButtonTex = buttonsTexture[PONG_LOGO];
	Button* tempButton = buttons[PONG_LOGO];

	int x = tempButton->buttonPos.getX();
	int y = tempButton->buttonPos.getY();
	int w = tempButton->width;
	int h = tempButton->height;

	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = tempButton->width;
	sourceRect.h = tempButton->height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = w ;
	destRect.h = h;

	SDL_RenderTexture(GraphicsHandler::instance().getRenderer(), tempButtonTex, &sourceRect, &destRect);
}
void UIHandler::clean()
{

}

bool UIHandler::onPlayClicked()
{
	Button* playButton = buttons[PLAY_BUTTON];

	int x = playButton->buttonPos.getX();
	int y = playButton->buttonPos.getY();
	int w = playButton->width;
	int h = playButton->height;

	if (InputHandler::Instance().getMouseButtonState(LEFT) && InputHandler::Instance().mouseOverObject(x, y, w / 2, h)) {
		return true;
	}
	return false;
}
