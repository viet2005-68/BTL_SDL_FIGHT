#include "Cyclone.h"
#include <iostream>


Cyclone::Cyclone(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 160;
	enemyRect.h = 450;
	enemyRect.x = m_position.getX()+20;
	enemyRect.y = m_position.getY()+200;
	m_currentFrame = 1;

}

void Cyclone::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Cyclone::update() {
	if (animationTime.getElapsedTime() > 0.1 && m_currentFrame > 3) {
		m_currentFrame++;
		animationTime.reset();
	}
	else if (animationTime.getElapsedTime() > 0.3 && m_currentFrame <= 3) {
		m_currentFrame++;
		animationTime.reset();
	}
	if (m_currentFrame == frame) {
		death = 1;
		m_currentFrame = 1;
	}
	SDLGameObject::update();

}

void Cyclone::clean() {

}

void Cyclone::move(Player*& player) {
	enemyRect.x = m_position.getX()+30;
	enemyRect.y = m_position.getY()+200;
	m_textureID = "assets/finalBoss/Cyclone.png";

	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_width = m_height = 0;
		time.reset();
	}
	else {
		if (m_currentFrame >= 6 && m_currentFrame <= 20 && Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect)) {
			if (time.getElapsedTime() > 0.2) {
				player->healthBar -= 5 / player->defense;
				player->attacked = 1;
				time.reset();
			}
		}
	}
}