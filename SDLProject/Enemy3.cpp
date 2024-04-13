#include "Enemy3.h"
#include <iostream>
#include "Map_lv2.h"

Enemy3::Enemy3(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 40;
	enemyRect.h = 70;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();
	des_X_left = enemyRect.x - 60;
	des_X_right = enemyRect.x + 60;
}

void Enemy3::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Enemy3::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	enemyRect.x = m_position.m_x + 80;
	enemyRect.y = m_position.m_y + 80;
	SDLGameObject::update();

}

void Enemy3::clean() {

}

void Enemy3::move(Player*& player) {
	enemyRect.x = m_position.getX() + 80;
	enemyRect.y = m_position.getY() + 80;
	m_textureID = "assets/enemy3Run.png";
	//cout << time.getElapsedTime() << endl;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/enemy3Death.png";
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
	else if (abs(player->playerRect.x - enemyRect.x) <= 70 && player->playerRect.y + 32 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 40 && death != true) {
		if (player->playerRect.x + 70 >= enemyRect.x && player->playerRect.x + 80 < enemyRect.x + 120) {
			m_velocity.setX(-0.0000000001);
		}
		else if (player->playerRect.x <= enemyRect.x + 70 && player->playerRect.x + 32 > enemyRect.x + 120) {
			m_velocity.setX(0);
		}

		if (player->attack != 1 || (player->playerRect.x + 80 > enemyRect.x + 70 && player->getVelocity().getX() > 0) || (player->playerRect.x + 80 < enemyRect.x + 70 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/enemy3Attack.png";
			tick = 50;
			frame = 8;
			if (time.getElapsedTime() > 0.4) {
				player->healthBar -= (3 / player->defense);
				player->attacked = 1;
				SoundManager::Instance()->playSound("assets/damaged.wav", 0);
				//Timer::getInstance()->reset();
				time.reset();
			}
		}
		else if (player->attack == 1) {
			m_textureID = "assets/enemy3Hit.png";
			frame = 4;
			tick = 200;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * player->damageRatio / damageRes;
				healthBar -= (player->damage * player->damageRatio + 7) / damageRes;
				//std::cout << "Flying eye health: " << health << std::endl;
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
				//player->attacked = 0;
				//Timer::getInstance()->reset();
				time.reset();
			}

			if (health <= 0) {
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}
	
	else {
		tick = 90;
		frame = 8;
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		if (enemyRect.x <= des_X_left) {
			m_velocity.setX(0.001);
		}
		if (enemyRect.x >= des_X_right) {
			m_velocity.setX(-0.01);
		}
		enemyRect.x = m_position.m_x + 80;
		enemyRect.y = m_position.m_y + 80;
		if (Map_lv2::getInstance()->iswall(enemyRect)) {
			m_velocity.setX(-1 * m_velocity.m_x);
		}
		
		if (m_velocity.getX() <= 0) {
			m_position.m_x -= 0.8;
			time.reset();
		}
		if (m_velocity.getX() >= 0) {
			m_position.m_x += 0.8;
			time.reset();
		}
		//time.reset();


	}

}