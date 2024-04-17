#include "FireBall.h"
#include "Map_lv2.h"
#include "Map.h"
#include <iostream>


FireBall::FireBall(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 30;
	enemyRect.h = 30;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();

}

void FireBall::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void FireBall::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	SDLGameObject::update();

}

void FireBall::clean() {

}

void FireBall::move(Player*& player, int direction, int map) {
	enemyRect.x = m_position.getX() + 20;
	enemyRect.y = m_position.getY() + 20;
	m_textureID = "assets/fireBall.png";
	//cout << time.getElapsedTime() << endl;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		frame = 7;
		tick = 300;
		m_textureID = "assets/fireBallDeath.png";
		if (time.getElapsedTime() > 0.5) {
			m_width = 0;
			m_height = 0;
			time.reset();
		}
	}
	else {
		if (direction == 0) {
			m_velocity.setX(2);
		}
		else if (direction == 1) {
			m_velocity.setX(-2);
		}
		else if (direction == 2) {
			m_velocity.setY(-2);
		}
		else if (direction == 3) {
			m_velocity.setX(2);
			m_velocity.setY(-2);
		}
		else if (direction == 4) {
			m_velocity.setX(-2);
			m_velocity.setY(-2);
		}
		if (time.getElapsedTime() > 5) {
			death = 1;
			time.reset();
		}
		if (map == 2) {
			if (Map_lv2::getInstance()->iswall(enemyRect)) {
				death = 1;
				time.reset();
			}
		}
		else if (map == 1) {
			if (Map::getInstance()->iswall(enemyRect)) {
				death = 1;
				time.reset();
			}
		}
		if (((enemyRect.x + 46 <= player->playerRect.x + 32 && enemyRect.x + 46 >= player->playerRect.x) || (enemyRect.x <= player->playerRect.x + 32 && enemyRect.x + 42 >= player->playerRect.x)) && ((enemyRect.y + 42 >= player->playerRect.y && enemyRect.y <= player->playerRect.y + 32) || (enemyRect.y <= player->playerRect.y + 32) && (enemyRect.y + 42 >= player->playerRect.y))) {
			player->healthBar -= 5 / player->defense;
			player->attacked = 1;
			death = 1;
			time.reset();
		}
	}
}