#include "playerFireBall.h"
#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Map_lv2.h"

playerFireBall::playerFireBall(const LoaderParams* pParams, int a) : SDLGameObject(pParams)
{
	direction = a;
	fireRect.w = 64;
	fireRect.h = 24;
	fireRect.x = m_position.getX();
	fireRect.y = m_position.getY();

}

void playerFireBall::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(fireRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void playerFireBall::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	SDLGameObject::update();

}

void playerFireBall::clean() {

}

void playerFireBall::move(int map) {
	fireRect.x = m_position.getX()+20;
	fireRect.y = m_position.getY()+30;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		frame = 7;
		tick = 200;
		m_textureID = "assets/meguminFireBallDeath.png";
		if (time.getElapsedTime() > 1) {
			m_width = 0;
			m_height = 0;
			time.reset();
		}
	}
	else {
		m_textureID = "assets/meguminFireBall.png";
		if (direction == 0) {
			m_velocity.setX(4);
		}
		else if (direction == 1) {
			m_velocity.setX(-4);
		}

		if (map == 2) {
			if (Map_lv2::getInstance()->iswall(fireRect)) {
				death = 1;
				time.reset();
			}
		}
		else if (map == 1) {
			if (Map::getInstance()->iswall(fireRect)) {
				death = 1;
				time.reset();
			}
		}
		else if (map == 3) {
			if (Map_lv3::getInstance()->iswall(fireRect)) {
				death = 1;
				time.reset();
			}
		}
	}
}