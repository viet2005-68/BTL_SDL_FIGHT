/*#include "Enemy.h"
#include "TextureManager.h"

void Enemy::load(int x, int y, int width, int height, const char* textureID, SDL_Renderer* ren) {
	GameObject::load(x, y, width, height, textureID, ren);
}

void Enemy::draw(SDL_Renderer* ren) {
	GameObject::draw(ren, 0);
}

void Enemy::update() {
	//m_x += 1;
	//m_y += 1;
	m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
}
*/

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
	enemyRect.x = m_position.getX()+70;
	enemyRect.y = m_position.getY() + 100;
	m_textureID = "assets/enemy1Run.png";
	//cout << time.getElapsedTime() << endl;

		//LightningBird skill

	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5){
					health -= player->damage * 2 * player->damageRatio / damageRes;
					healthBar -= ((player->damage + 7) * 2 * player->damageRatio) / damageRes;
					if (health <= 0) {
						Game::Instance()->m_score->Setscore(10);
						player->score += 10;
						std::cout << player->score << std::endl;
						death = true;
					}
					birdTime.reset();
					break;
				}
			}
		}

		for (int i = 0; i < player->m_fireBalls.size(); ++i) {
			if (player->m_fireBalls[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_fireBalls[i]->fireRect, enemyRect)) {
					health -= player->damage * player->damageRatio / damageRes;
					healthBar -= ((player->damage + 7) * player->damageRatio) / damageRes;
					player->m_fireBalls[i]->death = 1;
					if (health <= 0) {
						Game::Instance()->m_score->Setscore(10);
						player->score += 10;
						std::cout << player->score << std::endl;
						death = true;
					}
			}
		}

		if (player->explosion == 1) {
			healthBar -= 1;
			if (healthBar <= 0) {
				Game::Instance()->m_score->Setscore(10);
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}

	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/enemy1Death.png";
		frame = 4;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {
			//TextureManager::Instance()->clearFromTextureMap("assets/enemy1Death.png");
			//Timer::getInstance()->reset();
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
			//time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 70 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 40 && death != true) {
		/*if (player->playerRect.x + 70 >= enemyRect.x) {
			m_velocity.setX(-0.0000000001);
		}
		else if(player->playerRect.x <= enemyRect.x + 70)  {
			m_velocity.setX(0);
		}*/

		if (player->skill == 1) {
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * 3 * player->damageRatio / damageRes;
				healthBar -= ((player->damage+7) * 3 * player->damageRatio) / damageRes;
				time.reset();
			}
			if (health <= 0) {
				Game::Instance()->m_score->Setscore(10);
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}

		if (player->lightning == 1) {
			if (lightning.getElapsedTime() > 0.1) {
				health -= 1 * player->damageRatio / damageRes;
				healthBar -= 2 * player->damageRatio / damageRes;
				lightning.reset();
			}
			if (health <= 0) {
				Game::Instance()->m_score->Setscore(10);
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}

		if (player->characterNum == 3) {
			if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect) && player->attack != 1) {

				m_textureID = "assets/enemy1Attack.png";
				tick = 150;
				frame = 8;
				if (time.getElapsedTime() > 1) {
					player->healthBar -= (10 / player->defense);
					player->attacked = 1;
					SoundManager::Instance()->playSound("assets/damaged.wav", 0);
					//Timer::getInstance()->reset();
					time.reset();
				}
			}
			else if (player->attack == 1) {
				m_textureID = "assets/enemy1Hit.png";
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
					Game::Instance()->m_score->Setscore(10);
					player->score += 10;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}
		else {
			if (player->attack != 1 || (player->playerRect.x + 80 > enemyRect.x + 70 && player->getVelocity().getX() > 0) || (player->playerRect.x + 80 < enemyRect.x + 70 && player->getVelocity().getX() < 0)) {
				m_textureID = "assets/enemy1Attack.png";
				tick = 150;
				frame = 8;
				if (time.getElapsedTime() > 1) {
					player->healthBar -= (10 / player->defense);
					player->attacked = 1;
					SoundManager::Instance()->playSound("assets/damaged.wav", 0);
					//Timer::getInstance()->reset();
					time.reset();
				}
			}
			else if (player->attack == 1) {
				m_textureID = "assets/enemy1Hit.png";
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
					Game::Instance()->m_score->Setscore(10);
					;				player->score += 10;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}
	}
	else if(player->playerRect.x + 70 < enemyRect.x) {
		tick = 100;
		frame = 8;
		m_velocity.setX(-1);
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}
	else if (player->playerRect.x > enemyRect.x + 70) {
		tick = 100;
		frame = 8;
		m_velocity.setX(1);
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}
	else {
		tick = 100;
		frame = 8;
		//player->attacked = 0;
		//Timer::getInstance()->reset();
		time.reset();
	}

	if (player->playerRect.y < enemyRect.y && death == false) {
		m_velocity.setY(-1);
	}
	else if (player->playerRect.y > enemyRect.y && death == false) {
		m_velocity.setY(1);
	}
	else {
		m_velocity.setY(0);
	}
}