#include "boss1.h"
#include <iostream>


boss1::boss1(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 120;
	enemyRect.h = 120;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();

}

void boss1::draw() {
	SDLGameObject::drawBig();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x - 20, enemyRect.y - 50, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x - 20, enemyRect.y - 50, healthBar, barHeight, 1, 0, 0);
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void boss1::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void boss1::clean() {

}

void boss1::move(Player*& player) {
	enemyRect.x = m_position.getX() + 180;
	enemyRect.y = m_position.getY() + 220;
	//m_textureID = "assets/boss1Run.png";
	//cout << time.getElapsedTime() << endl;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/boss1Death.png";
		frame = 4;
		tick = 200;
		if (time.getElapsedTime() > 0.5) {
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
			time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 100 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 120 && death != true) {
		if (player->playerRect.x + 70 >= enemyRect.x && player->playerRect.x + 80 < enemyRect.x + 120) {
			m_velocity.setX(-0.0000000001);
		}
		else if (player->playerRect.x <= enemyRect.x + 120 && player->playerRect.x + 80 > enemyRect.x + 120) {
			m_velocity.setX(0);
		}


		if ((player->attack == 1 && player->playerRect.x + 80 < enemyRect.x + 120 && player->getVelocity().getX() > 0) || (player->attack == 1 && player->playerRect.x + 80 > enemyRect.x + 120 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/boss1TakeHit.png";
			tick = 300;
			frame = 3;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= (player->damage * player->damageRatio) / 2;
				healthBar -= (player->damage * player->damageRatio) / 2;
				time.reset();
			}
			if (health <= 0) {
				death = 1;
			}
		}
		else if (player->attack != 1) {
			m_textureID = "assets/boss1Attack2.png";
			tick = 200;
			frame = 8;
			if (time.getElapsedTime() > 1.5) {
				player->healthBar -= (30 / player->defense);
				player->attacked = 1;
				time.reset();
			}
		}
	}
	if (player->playerRect.x + 80 < enemyRect.x) {
		tick = 100;
		frame = 8;
		m_textureID = "assets/boss1Run.png";
		m_velocity.setX(-1);
		time.reset();
	}
	else if (player->playerRect.x > enemyRect.x + 120) {
		tick = 100;
		frame = 8;
		m_textureID = "assets/boss1Run.png";
		m_velocity.setX(1);
		time.reset();
	}

	if (player->playerRect.y < enemyRect.y + 30 && death == false) {
		m_velocity.setY(-1);
	}
	else if (player->playerRect.y > enemyRect.y + 30 && death == false) {
		m_velocity.setY(1);
	}
	else {
		m_velocity.setY(0);
	}
}