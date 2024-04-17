#include "lightningBird.h"
#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Map_lv2.h"

lightningBird::lightningBird(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	birdRect.w = 48;
	birdRect.h = 48;
	birdRect.x = m_position.getX();
	birdRect.y = m_position.getY();

}

void lightningBird::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(birdRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void lightningBird::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	SDLGameObject::update();

}

void lightningBird::clean() {

}

void lightningBird::move(int direction, int map) {
	birdRect.x = m_position.getX() + 20;
	birdRect.y = m_position.getY() + 20;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		frame = 5;
		tick = 300;
		m_textureID = "assets/lightningBirdDeath.png";
		if (time.getElapsedTime() > 1) {
			m_width = 0;
			m_height = 0;
			time.reset();
		}
	}
	else {
		m_textureID = "assets/lightningBirdFly.png";
		if (direction == 0) {
			m_velocity.setX(4);
		}
		else if (direction == 1) {
			m_velocity.setX(-4);
		}

		if (map == 2) {
			if (Map_lv2::getInstance()->iswall(birdRect)) {
				death = 1;
				time.reset();
			}
		}
		else if (map == 1) {
			if (Map::getInstance()->iswall(birdRect)) {
				death = 1;
				time.reset();
			}
		}
	}
}