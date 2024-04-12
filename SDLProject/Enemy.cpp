#include "Enemy.h"
#include <iostream>


Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 70;
	enemyRect.h = 40;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();
	
}

void Enemy::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Enemy::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();
	
}

void Enemy::clean() {

}

void Enemy::move(Player* &player) {
	
	enemyRect.x = m_position.getX() + 70;
	enemyRect.y = m_position.getY() + 100;
	m_textureID = "assets/enemy1Run.png";
	
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/enemy1Death.png";
		frame = 4;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {
			
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 70 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 40 && death != true) {
	
		if (player->attack != 1 || (player->playerRect.x + 80 > enemyRect.x+70 && player->getVelocity().getX()>0) || (player->playerRect.x + 80 < enemyRect.x+70 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/enemy1Attack.png";
			tick = 150;
			frame = 8;
			if (time.getElapsedTime() > 1) {
				player->healthBar -= 10 / player->defense;
				player->attacked = 1;
				SoundManager::Instance()->playSound("assets/damaged.wav", 0);
				
				time.reset();
			}
		}
		else if (player->attack == 1) {
			m_textureID = "assets/enemy1Hit.png";
			frame = 4;
			tick = 200;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage*player->damageRatio;
				healthBar -= (player->damage)*player->damageRatio + 7;
				
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
			
				time.reset();
			}

			if (healthBar <= 0) {
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}
	else if(player->playerRect.x + 70 < enemyRect.x) {
		tick = 100;
		frame = 8;

		m_velocity.setX(-1);
		
		time.reset();
	}
	else if (player->playerRect.x > enemyRect.x + 70) {
		tick = 100;
		frame = 8;

		m_velocity.setX(1);
	
		time.reset();
	}
	else {
		tick = 100;
		frame = 8;
		time.reset();
	}

	if (player->playerRect.y <= enemyRect.y && death == false) {
		m_velocity.setY(-1);
		
	}
	else if (player->playerRect.y >= enemyRect.y && death == false) {
		m_velocity.setY(1);
	}
}
