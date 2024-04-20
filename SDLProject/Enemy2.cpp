#include "Enemy2.h"
#include <iostream>
#include "Map_lv2.h"
#include <vector>
#include <algorithm>


Enemy2::Enemy2(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 32;
	enemyRect.h = 32;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();
	Path = new AstarFindPath(Map_lv2::getInstance()->GetTileCheck());

}

void Enemy2::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);

}

void Enemy2::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void Enemy2::clean() {

}

void Enemy2::move(Player*& player) {
	enemyRect.x = m_position.getX() + 32;
	enemyRect.y = m_position.getY() + 32;
	m_textureID = "assets/Torch_Red.png";
	//cout << time.getElapsedTime() << endl;
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
				healthBar -= ((player->damage) * player->damageRatio) / damageRes;
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
			if(healthBar <= 0) {
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
		m_textureID = "assets/Torch_Red.png";
		frame = 3;
		tick = 300;
		m_currentRow = 4;
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
	else if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect)) {
		if (player->playerRect.x + 32 >= enemyRect.x && player->playerRect.x + 32 < enemyRect.x + 100) {
			m_velocity.setX(-0.0000000001);
		}
		else if (player->playerRect.x <= enemyRect.x + 40 && player->playerRect.x + 32 > enemyRect.x + 120) {
			m_velocity.setX(0);
		}
		if (player->attack == 1) {
			if (attackedTime.getElapsedTime() > player->attackSpeed) {
				health -= (player->damage * player->damageRatio) / damageRes;
				healthBar -= (player->damage * player->damageRatio) / damageRes;
				attackedTime.reset();
			}
			if (healthBar <= 0) {
				Game::Instance()->m_score->Setscore(10);
				player->score += 10;
				death = 1;
			}
		}
		if (player->skill == 1) {
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * 3 * player->damageRatio / damageRes;
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

		if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect)) {
			m_textureID = "assets/Torch_Red.png";
			tick = 150;
			frame = 6;
			m_currentRow = 3;
			if (time.getElapsedTime() > 1) {
				player->healthBar -= (5 / player->defense);
				player->attacked = 1;
				//Timer::getInstance()->reset();
				time.reset();
			}
		}

	}
	else if(!Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect)){
		tick = 80;
		frame = 7;
		m_currentRow = 1;
		
		float deltaXRect = enemyRect.x - player->playerRect.x;
		float deltaYRect = enemyRect.y - player->playerRect.y;
		float distance_check = sqrt(deltaXRect * deltaXRect + deltaYRect * deltaYRect);

		if (distance_check < 300) {
			std::pair<int, int> path = Path->FindPath(enemyRect.x / 32, enemyRect.y / 32, player->playerRect.x / 32, player->playerRect.y / 32);




			float deltaX = path.first - int(enemyRect.x / 32);
			float deltaY = path.second - int(enemyRect.y / 32);
			float distance = sqrt(deltaX * deltaX + deltaY * deltaY);


			float directionX;
			float directionY;

			directionX = deltaX / distance;
			directionY = deltaY / distance;
			if (directionX < 0) {
				m_velocity.setX(-0.0001);
			}
			else {
				m_velocity.setX(0.00001);
			}

			m_position.m_x += directionX * 1;
			m_position.m_y += directionY * 1;
			enemyRect.x = m_position.getX() + 32;
			enemyRect.y = m_position.getY() + 32;
			if (Map_lv2::getInstance()->iswall(enemyRect)) {
				m_position.m_x -= directionX * 1;
				m_position.m_y -= directionY * 1;
			}

		}

	}
}