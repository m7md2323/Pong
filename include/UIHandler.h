#pragma once
#include"InputHandler.h"
#include"Vector2D.h"
#include"GraphicsHandler.h"
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<map>
using namespace std;
//this class instance is created using the Meyers’ singleton creational design pattern 
enum Button_Type {
	PLAY_BUTTON,
	EXIT_BUTTON,
	MENU_BUTTON,
	FANCY_MAP_SEL_BUTTON,
	CLASSIC_MAP_SEL_BUTTON,
	PONG_LOGO//not a button, just a logo
};
struct Button {
	Button(Button_Type _type, Vector2D _buttonPos, int _width, int _height) :buttonPos{ _buttonPos }, buttonType{ _type }, width{ _width },
		height{ _height } {

	}
	Vector2D buttonPos;
	int width;
	int height;
	Button_Type buttonType;
};
class UIHandler {
public:
	static UIHandler& instance() {
		static UIHandler instance;
		return instance;
	}
	bool init();
	bool load(string,Button_Type);
	void renderMenu();
	void renderPause();
	void renderModeSelect();

	void renderButton(Button_Type);
	void renderLogo();
	void clean();

	bool onPlayClicked();
protected:
	UIHandler(){}
	~UIHandler() { clean(); }
private:
	map<Button_Type, Button*> buttons;
	map<Button_Type, SDL_Texture*> buttonsTexture;
};