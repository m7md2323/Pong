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
	PAUSE_BUTTON,
	FANCY_MAP_SEL_BUTTON,
	CLASSIC_MAP_SEL_BUTTON
};
enum Text_Type {
	PONG_LOGO,
	MAP_MODE_SEL_TEXT,
	PAUSE_TEXT
};
struct Text {
	Text(Text_Type _type, int _width, int _height) :x{ 0 }, y{0},textType { _type }, width{ _width }, height{ _height } {

	}
	int x, y;
	int width;
	int height;
	Text_Type textType;
};
struct Button {
	Button(Button_Type _type, int _width, int _height) : x{ 0 }, y{ 0 },buttonType{ _type }, width{ _width },
		height{ _height } {

	}
	int x, y;
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
	bool loadButton(string,Button_Type);
	bool loadText(string, Text_Type);
	void renderMenu();
	void renderPause();
	void renderModeSelect();

	void setMenuLayout();
	void setPauseLayout();
	void setSelModeLayout();

	void renderButton(Button_Type);
	void renderText(Text_Type);
	void clean();

	bool onButtonClicked(Button_Type);
protected:
	UIHandler(){}
	~UIHandler() { clean(); }
private:
	map<Button_Type, Button*> buttons;
	map<Button_Type, SDL_Texture*> buttonsTexture;

	map<Text_Type, Text*> texts;
	map<Text_Type, SDL_Texture*> textsTexture;
};