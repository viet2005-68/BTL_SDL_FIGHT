#include "MenuButton.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "SoundManager.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::drawButton();
}

void MenuButton::update()
{
	SDL_Point pMousePos = InputHandler::Instance()->GetMousePosition();

	if (pMousePos.x < ((int)m_position.getX() + m_width * 2) && pMousePos.x >  (int)m_position.getX() && pMousePos.y < ((int)m_position.getY() + m_height * 2) && pMousePos.y >(int)m_position.getY()) {
		m_currentFrame = MOUSE_OVER;

		if (InputHandler::Instance()->GetLeftMouseButtonState() && m_bRealeased) {

			SoundManager::Instance()->playSound("confirm", 0);

			m_currentFrame = CLICKED;

			m_callback();
			m_bRealeased = false;
		}
		else if (!InputHandler::Instance()->GetLeftMouseButtonState()) {
			m_bRealeased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}

}


void MenuButton::clean()
{
	SDLGameObject::clean();
}