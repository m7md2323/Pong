#include "InputHandler.h"
#include<iomanip>
#include<iostream>
#include"Paddle.h"

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keyState != 0)
	{
		if (m_keyState[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
void InputHandler::update(Paddle *player)
{
	SDL_Scancode key;
	
	m_keyState = SDL_GetKeyboardState(0);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_EVENT_QUIT:
			m_gameRunning = false;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			onMouseMove(event);
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			onMouseButtonDown(event);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			onMouseButtonUp(event);
			break;
		case SDL_EVENT_KEY_DOWN:
			onKeyDown(&event,player);
			break;
		case SDL_EVENT_KEY_UP:
			onKeyUp(&event);
			break;
		default:
			break;
		}
	}
}
int InputHandler::onKeyDown(SDL_Event *e,Paddle *player)
{
	switch (e->key.scancode)
	{
		case SDL_SCANCODE_W:
			player->moveUp();
			break;
		case SDL_SCANCODE_S:
			player->moveDown();
	default:
		break;
	}
	return 0;

}

int InputHandler::onKeyUp(SDL_Event *e)
{
	return 0;
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_MOTION) {
		std::cout << event.motion.x<<" "<<event.motion.y << "\n";;
		m_mousePosition->setX(event.motion.x);
		m_mousePosition->setY(float(event.motion.y));
	}
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_mouseButtonStates[LEFT] = true;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			m_mouseButtonStates[MIDDLE] = true;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_mouseButtonStates[RIGHT] = true;
		}
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_mouseButtonStates[LEFT] = false;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			m_mouseButtonStates[MIDDLE] = false;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_mouseButtonStates[RIGHT] = false;
		}
	}
}
