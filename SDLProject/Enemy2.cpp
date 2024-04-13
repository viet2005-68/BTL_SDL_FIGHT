#include "Enemy2.h"
#include <iostream>


Enemy2::Enemy2(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 40;
	enemyRect.h = 70;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();

}

void Enemy2::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Enemy2::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void Enemy2::clean() {

}

void Enemy2::move(Player*& player) {
	enemyRect.x = m_position.getX() + 80;
	enemyRect.y = m_position.getY() + 80;
	m_textureID = "assets/enemy2Run.png";
	//cout << time.getElapsedTime() << endl;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/enemy2Death.png";
		frame = 4;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {
			//TextureManager::Instance()->clearFromTextureMap("assets/enemy1Death.png");
			//Timer::getInstance()->reset();
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
			time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 70 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 40 && death != true) {
		if (player->playerRect.x + 70 >= enemyRect.x && player->playerRect.x + 80 < enemyRect.x + 120) {
			m_velocity.setX(-0.0000000001);
		}
		else if (player->playerRect.x <= enemyRect.x + 70 && player->playerRect.x + 80 > enemyRect.x + 120) {
			m_velocity.setX(0);
		}

		if (player->attack != 1 || (player->playerRect.x + 80 > enemyRect.x + 70 && player->getVelocity().getX() > 0) || (player->playerRect.x + 80 < enemyRect.x + 70 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/enemy2Attack.png";
			tick = 150;
			frame = 8;
			if (time.getElapsedTime() > 1) {
				player->healthBar -= (15 / player->defense);
				player->attacked = 1;
				SoundManager::Instance()->playSound("assets/damaged.wav", 0);
				//Timer::getInstance()->reset();
				time.reset();
			}
		}
		else if (player->attack == 1) {
			m_textureID = "assets/enemy2Hit.png";
			frame = 4;
			tick = 200;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * player->damageRatio / damageRes;
				healthBar -= (player->damage * player->damageRatio) / damageRes;
				//std::cout << "Flying eye health: " << health << std::endl;
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
				//player->attacked = 0;
				//Timer::getInstance()->reset();
				time.reset();
			}

			if (healthBar <= 0) {
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}
	else if (player->playerRect.x + 70 < enemyRect.x) {
		tick = 100;
		frame = 4;
		m_velocity.setX(-0.5);
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}
	else if (player->playerRect.x > enemyRect.x + 70) {
		tick = 100;
		frame = 4;
		m_velocity.setX(0.5);
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}
	else {
		tick = 100;
		frame = 4;
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}

	if (player->playerRect.y < enemyRect.y && death == false) {
		m_velocity.setY(-0.5);
	}
	else if (player->playerRect.y > enemyRect.y && death == false) {
		m_velocity.setY(0.5);
	}
	else {
		m_velocity.setY(0);
	}
}