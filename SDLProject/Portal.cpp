#include "Portal.h"
#include <iostream>


Portal::Portal(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_currentRow = 2;
	open = 0;
}

void Portal::draw() {
	SDLGameObject::draw();
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

