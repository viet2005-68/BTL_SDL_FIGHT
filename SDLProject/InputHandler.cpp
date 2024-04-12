#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::input_instance = 0;

void InputHandler::handleEvent() {
	InputHandler::m_keystates = SDL_GetKeyboardState(0);
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		Game::Instance()->Quit();
		break;
	case SDL_KEYUP:
		InputHandler::KeyUp();
		break;
	case SDL_KEYDOWN:
		InputHandler::KeyDown();
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_MouseBottonDown = true;
		m_MouseButtonUp = false;
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_MouseButtonLeft = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		m_MouseButtonUp = true;
		m_MouseBottonDown = false;
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_MouseButtonLeft = false;
		}
		break;
	case SDL_MOUSEMOTION:
		m_MousePosition.x = event.button.x;
		m_MousePosition.y = event.button.y;
	default:
		break;
	}
}

void InputHandler::KeyDown() {
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::KeyUp() {
	m_keystates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
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

bool InputHandler::GetMouseButtonDown()
{
	return m_MouseBottonDown;
}

bool InputHandler::GetMouseButtonUp()
{
	return m_MouseButtonUp;
}

bool InputHandler::GetLeftMouseButtonState() {
	return m_MouseButtonLeft;
}

void InputHandler::Reset()
{
	m_MouseBottonDown = false;
	m_MouseButtonUp = false;
}

SDL_Point InputHandler ::GetMousePosition()
{
	return m_MousePosition;
}