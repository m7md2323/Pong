#include"UIHandler.h"

bool UIHandler::init() {
	//buttons
	if (!loadButton("../assets/PlayButton.png", PLAY_BUTTON)) {
		SDL_Log("Media PlayButton could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadButton("../assets/ExitButton.png", EXIT_BUTTON)) {
		SDL_Log("Media ExitButton could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadButton("../assets/FancyMap.png", FANCY_MAP_SEL_BUTTON)) {
		SDL_Log("Media FancyMap could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadButton("../assets/ClassicMap.png", CLASSIC_MAP_SEL_BUTTON)) {
		SDL_Log("Media ClassicMap could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadButton("../assets/PauseButton.png", PAUSE_BUTTON)) {
		SDL_Log("Media PauseButton could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadButton("../assets/MenuButton.png", MENU_BUTTON)) {
		SDL_Log("Media MenuButton could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//texts
	if (!loadText("../assets/PongLogo.png",PONG_LOGO)) {
		SDL_Log("Media PongLogo could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadText("../assets/SelectMapModeTxt.png", MAP_MODE_SEL_TEXT)) {
		SDL_Log("Media SelectMapModeTxt could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	if (!loadText("../assets/PauseTxt.png", PAUSE_TEXT)) {
		SDL_Log("Media PauseTxt could not be loaded ! SDL error: %s\n", SDL_GetError());
		return false;
	}
	//init buttons objects
	buttons[PLAY_BUTTON] = new Button(PLAY_BUTTON,  buttonsTexture[PLAY_BUTTON]->w/2, buttonsTexture[PLAY_BUTTON]->h);
	buttons[EXIT_BUTTON] = new Button(EXIT_BUTTON,buttonsTexture[EXIT_BUTTON]->w/2, buttonsTexture[EXIT_BUTTON]->h);
	//buttons[PAUSE_STATE_EXIT_BUTTON] = new Button(PAUSE_STATE_EXIT_BUTTON, Vector2D(312, 405), buttonsTexture[EXIT_BUTTON]->w, buttonsTexture[EXIT_BUTTON]->h);
	buttons[PAUSE_BUTTON] = new Button(PAUSE_BUTTON,  buttonsTexture[PAUSE_BUTTON]->w/2, buttonsTexture[PAUSE_BUTTON]->h);
	buttons[MENU_BUTTON] = new Button(MENU_BUTTON,  buttonsTexture[MENU_BUTTON]->w/2, buttonsTexture[MENU_BUTTON]->h);
	buttons[FANCY_MAP_SEL_BUTTON] = new Button(FANCY_MAP_SEL_BUTTON,  buttonsTexture[FANCY_MAP_SEL_BUTTON]->w, buttonsTexture[FANCY_MAP_SEL_BUTTON]->h);
	buttons[CLASSIC_MAP_SEL_BUTTON] = new Button(CLASSIC_MAP_SEL_BUTTON, buttonsTexture[CLASSIC_MAP_SEL_BUTTON]->w, buttonsTexture[CLASSIC_MAP_SEL_BUTTON]->h);

	//init texts objects
	texts[PONG_LOGO] = new Text(PONG_LOGO, textsTexture[PONG_LOGO]->w, textsTexture[PONG_LOGO]->h);
	texts[MAP_MODE_SEL_TEXT] = new Text(MAP_MODE_SEL_TEXT, textsTexture[MAP_MODE_SEL_TEXT]->w, textsTexture[MAP_MODE_SEL_TEXT]->h);
	texts[PAUSE_TEXT] = new Text(PAUSE_TEXT, textsTexture[PAUSE_TEXT]->w, textsTexture[PAUSE_TEXT]->h);

	return true;

}

bool UIHandler::loadButton(string filePath,Button_Type type)
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
bool UIHandler::loadText(string filePath, Text_Type type)
{

	textsTexture[type] = new SDL_Texture();

	textsTexture[type] = IMG_LoadTexture(GraphicsHandler::instance().getRenderer(), filePath.c_str());
	if (textsTexture[type] == NULL) {
		SDL_Log(filePath.c_str());
		SDL_Log("Image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void UIHandler::renderMenu()
{
	renderText(129, 50,PONG_LOGO);
	renderButton(312, 300,PLAY_BUTTON);
	renderButton(312, 355,EXIT_BUTTON);
}

void UIHandler::renderPause()
{
	renderText(325, 50,PAUSE_TEXT);
	renderButton(312, 300,PLAY_BUTTON);
	renderButton(312, 355,MENU_BUTTON);
	renderButton(312, 410,EXIT_BUTTON);
}

void UIHandler::renderModeSelect()
{
	renderText(200,50,MAP_MODE_SEL_TEXT);
	renderButton(100,200,FANCY_MAP_SEL_BUTTON);
	renderButton(500,200,CLASSIC_MAP_SEL_BUTTON);
}

void UIHandler::renderButton(int x,int y,Button_Type type)
{
	SDL_Texture* tempButtonTex=buttonsTexture[type];
	Button* tempButton = buttons[type];

	tempButton->x = x;
	tempButton->y = y;
	int w = tempButton->width;
	int h = tempButton->height;
	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = w;
	sourceRect.h = h;
	if (type != FANCY_MAP_SEL_BUTTON && type != CLASSIC_MAP_SEL_BUTTON)
	{
		if (InputHandler::Instance().mouseOverObject(x, y, w, h)) {
			//move to hover button
			sourceRect.x = w;
		}
	}
	destRect.x = x;
	destRect.y = y;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(GraphicsHandler::instance().getRenderer(), tempButtonTex, &sourceRect, &destRect);
}

void UIHandler::renderText(int x,int y,Text_Type type)
{
	SDL_Texture* tempTextTex = textsTexture[type];
	Text* tempText = texts[type];

	tempText->x = x;
	tempText->y = y;
	int w = tempText->width;
	int h = tempText->height;

	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = tempText->width;
	sourceRect.h = tempText->height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = w ;
	destRect.h = h;
	
	SDL_RenderTexture(GraphicsHandler::instance().getRenderer(), tempTextTex, &sourceRect, &destRect);
	//SDL_SetTextureBlendMode(tempTextTex, SDL_BLENDMODE_BLEND);
}
void UIHandler::clean()
{
	for (auto& var : buttons) {
		delete var.second;
		var.second = nullptr;
	}
	for (auto& var : buttonsTexture) {
		SDL_DestroyTexture(var.second);
	}
	for (auto& var : texts) {
		delete var.second;
		var.second = nullptr;
	}
	for (auto& var : textsTexture) {
		SDL_DestroyTexture(var.second);
	}
}

bool UIHandler::onButtonClicked(Button_Type type)
{
	Button* playButton = buttons[type];

	int x = playButton->x;
	int y = playButton->y;
	int w = playButton->width;
	int h = playButton->height;

	if (InputHandler::Instance().getMouseButtonState(LEFT) && InputHandler::Instance().mouseOverObject(x, y, w, h)) {
		return true;
	}
	return false;
}
