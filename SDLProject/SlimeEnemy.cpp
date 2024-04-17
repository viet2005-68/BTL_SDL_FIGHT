#include "SlimeEnemy.h"
#include <iostream>
#include "Vector2D.h"
#include "Map_lv2.h"


SlimeEnemy::SlimeEnemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    enemyRect.w = 48;
    enemyRect.h = 32;
    enemyRect.x = m_position.m_x + 25;
    enemyRect.y = m_position.m_y;
    VecX = 1;
    //VecX = 1;
    //find_road = new AStar();
    //VecY = 0;
}

void SlimeEnemy::draw() {
    
    TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y, barWidth, barHeight, 1, 0, 0);
    TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y, healthBar, 8, 1, 0, 0);
    SDLGameObject::draw();
    SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
    SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void SlimeEnemy::update() {
  
    m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

    SDLGameObject::update();
    
   enemyRect.x = m_position.m_x + 20;
   enemyRect.y = m_position.m_y ;
}

void SlimeEnemy::clean() {}

void SlimeEnemy::move(Player*& player) {
	enemyRect.x = m_position.getX() + 25;
	enemyRect.y = m_position.getY();
	m_textureID = "assets/slimeIdle.png";

	//LightningBird skill
	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5) {
					health -= player->damage * 2 * player->damageRatio / damageRes;
					healthBar -= ((player->damage) * 2 * player->damageRatio) / damageRes;
					if (health <= 0) {
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
				healthBar -= ((player->damage) * player->damageRatio) / damageRes;
				player->m_fireBalls[i]->death = 1;
				if (health <= 0) {
					player->score += 10;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}

		if (player->explosion == 1) {
			healthBar -= 1;
			if (healthBar <= 0) {
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}

	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/slimeDeath.png";
		frame = 14;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {
			barHeight = barWidth = 0;
			healthBar = 0;
		}
		if (time.getElapsedTime() > 1) {
			m_width = 0;
			m_height = 0;
			time.reset();
		}
	}
	else if (abs(player->playerRect.x - enemyRect.x) <= 60 && player->playerRect.y + 32 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 32 && death != true) {
		if (player->playerRect.x + 32 >= enemyRect.x) {
			m_velocity.setX(-0.0000000001);
		}
		else if (player->playerRect.x <= enemyRect.x + 48) {
			m_velocity.setX(0);
		}

		if (player->skill == 1) {
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= (player->damage * 3 * player->damageRatio) / damageRes;
				healthBar -= ((player->damage) * 3 * player->damageRatio) / damageRes;
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
				healthBar -= 1 * player->damageRatio / damageRes;
				lightning.reset();
			}
			if (health <= 0) {
				Game::Instance()->m_score->Setscore(10);
				player->score += 10;
				std::cout << player->score << std::endl;
				death = true;
			}
		}

		if (player->attack != 1 || (player->playerRect.x + 32 > enemyRect.x + 48 && player->getVelocity().getX() > 0) || (player->playerRect.x + 32 < enemyRect.x + 48 && player->getVelocity().getX() < 0)) {
			m_textureID = "assets/slimeIdle.png";
			tick = 100;
			frame = 7;
			if (time.getElapsedTime() > 1) {
				player->healthBar -= (5 / player->defense);
				player->attacked = 1;
				time.reset();
			}
		}
		else if (player->attack == 1) {
			m_textureID = "assets/slimeHit.png";
			frame = 11;
			tick = 80;
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * player->damageRatio / damageRes;
				healthBar -= player->damage * player->damageRatio / damageRes;
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
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
	else if (player->playerRect.x + 65 < enemyRect.x) {
		tick = 100;
		frame = 9;
		m_velocity.setX(-1);
		time.reset();
	}
	else if (player->playerRect.x > enemyRect.x + 65) {
		tick = 100;
		frame = 9;
		m_velocity.setX(1);
		time.reset();
	}
	else {
		tick = 100;
		frame = 9;
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