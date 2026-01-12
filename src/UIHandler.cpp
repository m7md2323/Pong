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
	buttonsTexture[type] = IMG_LoadTexture(GraphicsHandler::instance().getRenderer(), filePath.c_str());
	SDL_SetTextureBlendMode(buttonsTexture[type], SDL_BLENDMODE_BLEND);
	if (buttonsTexture[type] == NULL) {
		SDL_Log(filePath.c_str());
		SDL_Log("Image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
bool UIHandler::loadText(string filePath, Text_Type type)
{

	textsTexture[type] = IMG_LoadTexture(GraphicsHandler::instance().getRenderer(), filePath.c_str());
	SDL_SetTextureBlendMode(textsTexture[type], SDL_BLENDMODE_BLEND);
	if (textsTexture[type] == NULL) {
		SDL_Log(filePath.c_str());
		SDL_Log("Image could not be loaded!! SDL error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
//MENU
void UIHandler::renderMenu()
{
	setMenuLayout();
	renderText(PONG_LOGO);
	renderButton(PLAY_BUTTON);
	renderButton(EXIT_BUTTON);
}

void UIHandler::setMenuLayout()
{
	texts[PONG_LOGO]->x = 129;
	texts[PONG_LOGO]->y = 50;

	buttons[PLAY_BUTTON]->x = 312;
	buttons[PLAY_BUTTON]->y = 300;

	buttons[EXIT_BUTTON]->x = 312;
	buttons[EXIT_BUTTON]->y = 355;
}
//PAUSE
void UIHandler::renderPause()
{

	setPauseLayout();
	renderText(PAUSE_TEXT);
	renderButton(PLAY_BUTTON);
	renderButton(MENU_BUTTON);
	renderButton(EXIT_BUTTON);
}

void UIHandler::setPauseLayout()
{
	texts[PAUSE_TEXT]->x = 325;
	texts[PAUSE_TEXT]->y = 50;

	buttons[PLAY_BUTTON]->x = 312;
	buttons[PLAY_BUTTON]->y = 300;

	buttons[MENU_BUTTON]->x = 312;
	buttons[MENU_BUTTON]->y = 355;

	buttons[EXIT_BUTTON]->x = 312;
	buttons[EXIT_BUTTON]->y = 410;
}
// SELECT MAP MODE
void UIHandler::renderModeSelect()
{
	setSelModeLayout();
	renderText(MAP_MODE_SEL_TEXT);
	renderButton(FANCY_MAP_SEL_BUTTON);
	renderButton(CLASSIC_MAP_SEL_BUTTON);
}
void UIHandler::setSelModeLayout()
{
	texts[MAP_MODE_SEL_TEXT]->x = 200;
	texts[MAP_MODE_SEL_TEXT]->y = 50;

	buttons[FANCY_MAP_SEL_BUTTON]->x = 100;
	buttons[FANCY_MAP_SEL_BUTTON]->y = 200;

	buttons[CLASSIC_MAP_SEL_BUTTON]->x = 500;
	buttons[CLASSIC_MAP_SEL_BUTTON]->y = 200;
}
//
void UIHandler::renderButton(Button_Type type)
{
	SDL_Texture* tempButtonTex=buttonsTexture[type];
	Button* tempButton = buttons[type];

	int w = tempButton->width;
	int h = tempButton->height;
	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = w;
	sourceRect.h = h;
	if (type != FANCY_MAP_SEL_BUTTON && type != CLASSIC_MAP_SEL_BUTTON)
	{
		if (InputHandler::Instance().mouseOverObject(tempButton->x, tempButton->y, w, h)) {
			//move to hover button
			sourceRect.x = w;
		}
	}
	destRect.x = tempButton->x;
	destRect.y = tempButton->y;
	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;

	SDL_RenderTexture(GraphicsHandler::instance().getRenderer(), tempButtonTex, &sourceRect, &destRect);
}

void UIHandler::renderText(Text_Type type)
{
	SDL_Texture* tempTextTex = textsTexture[type];
	Text* tempText = texts[type];

	int w = tempText->width;
	int h = tempText->height;

	SDL_FRect sourceRect, destRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = tempText->width;
	sourceRect.h = tempText->height;

	destRect.x = tempText->x;
	destRect.y = tempText->y;
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
	Button* button = buttons[type];
	if (!button) return false;

	int x = button->x;
	int y = button->y;
	int w = button->width;
	int h = button->height;

	if (InputHandler::Instance().isMousePressedOnce(LEFT) && InputHandler::Instance().mouseOverObject(x, y, w, h)) {
		return true;
	}
	return false;
}
