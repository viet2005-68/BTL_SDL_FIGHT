#include "Portal.h"
#include <iostream>


Portal::Portal(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_currentRow = 2;
	open = 0;
	portalRect.w = 60;
	portalRect.h = 128;
	portalRect.x = m_position.m_x+50;
	portalRect.y = m_position.m_y+40;
}

void Portal::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(portalRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Portal::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	SDLGameObject::update();
	if (open == 0) {
		SoundManager::Instance()->playSound("assets/portal.wav", 0);
		if (time.getElapsedTime() > 3) {
			open = 1;
			time.reset();
		}
	}
	else {
		tick = 100;
		m_currentRow = 1;
	}
}

void Portal::clean() {

}

