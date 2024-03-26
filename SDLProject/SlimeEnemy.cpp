#include "SlimeEnemy.h"
#include <iostream>
#include "Map.h"

SlimeEnemy::SlimeEnemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 65;
	enemyRect.h = 32;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();
	VecX = 0;
	VecY = 0;
}

void SlimeEnemy::draw() {
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	SDLGameObject::draw();
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void SlimeEnemy::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void SlimeEnemy::clean() {

}

void SlimeEnemy::move(Player*& player) {
	VecX = 0;
	VecY = 0;
	enemyRect.x = m_position.getX()+45;
	enemyRect.y = m_position.getY()+20;
	m_textureID = "assets/slimeIdle.png";
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/slimeDeath.png";
		frame = 14;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {
			barHeight = barWidth = 0;
		}
		if (time.getElapsedTime() > 1) {
			m_width = 0;
			m_height = 0;
			time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 60 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 32  && death != true) {
		/*if (player->playerRect.x + 70 >= enemyRect.x) {
			m_velocity.setX(-0.0000000001);
		}
		else if(player->playerRect.x <= enemyRect.x + 70)  {
			m_velocity.setX(0);
		}*/

		if (player->attack != 1 || (player->playerRect.x + 80 > enemyRect.x + 65 && player->getVelocity().getX() > 0) || (player->playerRect.x + 80 < enemyRect.x + 65 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/slimeIdle.png";
			tick = 100;
			frame = 7;
			if (time.getElapsedTime() > 0.5) {
				player->healthBar -= 5 / player->defense;
				player->attacked = 1;
				time.reset();
			}
		}
		else if (player->attack == 1) {
			m_textureID = "assets/slimeHit.png";
			frame = 11;
			tick = 80;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * player->damageRatio;
				healthBar -= player->damage * player->damageRatio;
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
				time.reset();
			}

			if (health <= 0) {
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}
	else if (abs(player->playerRect.x + 65 - enemyRect.x) < 200) {
		tick = 100;
		frame = 9;
		
		if (Map::getInstance()->iswall(enemyRect)) {
			m_velocity.setX(0.6);
		}
		time.reset();
	}
	else if (abs(player->playerRect.x -enemyRect.x + 65) > 200) {
		tick = 100;
		frame = 9;
		m_velocity.setX(0.6);
		if (Map::getInstance()->iswall(enemyRect)) {
			m_velocity.setX(-0.6);
		}
		time.reset();
	}
	else {
		tick = 100;
		frame = 9;
		time.reset();
	}

	/*if (player->playerRect.y + 50 <= enemyRect.y && death == false) {
		m_velocity.setY(-0.6);
	}
	else if (player->playerRect.y + 50 >= enemyRect.y && death == false) {
		m_velocity.setY(0.6);
	}*/
}