#pragma once
#include<SDL3/SDL.h>
#include "Vector2D.h"
#include<vector>
#include"Paddle.h"
using namespace std;
//this class instance is created using the Meyers’ singleton creational design pattern 

class InputHandler
{

public:
	static InputHandler& Instance() {
		static InputHandler instance;
		return instance;
	}
	void update(Paddle *player);
	void clean();
	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }

	bool gameRunning() { return m_gameRunning; }

	Vector2D* getMousePosition() { return m_mousePosition; }

	bool isKeyDown(SDL_Scancode key);
private:
	InputHandler() :m_mousePosition{ nullptr }, m_keyState{nullptr}{
		m_mousePosition = new Vector2D(0, 0);
	}
	~InputHandler() {}

	vector<vector<bool>> m_buttonStates;
	vector<bool> m_mouseButtonStates;

	Vector2D* m_mousePosition;

	bool m_gameRunning = true;

	const bool* m_keyState;

	int onKeyDown(SDL_Event *e,Paddle *player);
	int onKeyUp(SDL_Event *e);
	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
};
enum mouse_buttons {
	LEFT,
	MIDDLE,
	RIGHT
};
