#include "Bot.h"
#include <iostream>
#include "Map.h"
#include "AStarFindPath.h"
Bot::Bot(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 64;
	enemyRect.h = 64;
	attackRect.w = 96;
	attackRect.h = 32;
	enemyRect.x = m_position.getX() + 60;
	enemyRect.y = m_position.getY() + 90;
	attackRect.x = m_position.getX() +60 ;
	attackRect.y = m_position.getY() + 90;
	Path1 = new AstarFindPath(Map_lv2::getInstance()->GetTileCheck());   
}

void Bot::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x - 20, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x - 20, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(attackRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Bot::update() {
	if (frameTime.getElapsedTime() > fps) {
		m_currentFrame++;
		frameTime.reset();
	}
	if (m_currentFrame >= frame) {
		m_currentFrame = 1;
	}
	SDLGameObject::update();

}

void Bot::clean() {

}

void Bot::move(Player*& player) {
	std::cout << time.getElapsedTime() << std::endl;
	enemyRect.x = m_position.getX() + 60;
	enemyRect.y = m_position.getY() + 90;
	//LightningBird skill
	if (m_velocity.getX() >= 0) {
		attackRect.x = m_position.getX() + 60;
		attackRect.y = m_position.getY() + 90;
	}
	else {
		attackRect.x = m_position.getX() - 10;
		attackRect.y = m_position.getY() + 90;
	}
	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5) {
					health -= player->damage * 2 * player->damageRatio / damageRes;
					healthBar -= ((player->damage + 7) * 2 * player->damageRatio) / damageRes;
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
				healthBar -= ((player->damage + 7) * player->damageRatio) / damageRes;
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
		m_textureID = "assets/bot/Death.png";
		frame = 14;
		if (startDeathAnimation == 0) {
			m_currentFrame = 1;
			startDeathAnimation = 1;
		}
		if (m_currentFrame == frame - 1) {
			m_width = m_height = 0;
			healthBar = barHeight = barWidth = 0;
		}
	}
	else {
		if (player->playerRect.x + 32 <= enemyRect.x && attackState != 1) {
			m_velocity.setX(-0.000001);
		}
		else if (player->playerRect.x >= enemyRect.x + 16 && attackState != 1) {
			m_velocity.setX(0);
		}
		if (player->skill == 1) {
			if (time.getElapsedTime() > player->attackSpeed) {
				health -= player->damage * 3 * player->damageRatio / damageRes;
				healthBar -= ((player->damage + 7) * 3 * player->damageRatio) / damageRes;
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

		if (Map::getInstance()->checkwall(player->playerRect, enemyRect)) {
			attackState = 1;
			if (player->attack == 1) {
				if (attackedTime.getElapsedTime() > player->attackSpeed) {
					health -= player->damage * player->damageRatio;
					healthBar -= player->damage + 7 * player->damageRatio;
					attackedTime.reset();
				}
				if (healthBar <= 0) {
					death = 1;
				}
			}
		}

		if (attackState == 1) {
			if (startAnimation == 0) {
				m_currentFrame = 1;
				startAnimation = 1;
			}

			if (time.getElapsedTime() < 2) {
				fps = 0.05;
				m_textureID = "assets/bot/Attack.png";
				frame = 42;
			}
			else {
				attackState = 0;
				startAnimation = 0;
				time.reset();
			}

			if (Map_lv2::getInstance()->checkwall(player->playerRect, attackRect)) {
				if (m_currentFrame >= 32 && m_currentFrame <= 38) {
					if (attackSpeed.getElapsedTime() > 0.3) {
						player->healthBar -= (8 / player->defense);
						player->attacked = 1;
						attackSpeed.reset();
					}
				}
			}
		}
		else
		{
			fps = 0.1;
			m_textureID = "assets/bot/Run.png";
			frame = 8;
			time.reset();
			
			float deltaXRect = enemyRect.x - player->playerRect.x;
			float deltaYRect = enemyRect.y - player->playerRect.y;
			float distance_check = sqrt(deltaXRect * deltaXRect + deltaYRect * deltaYRect);
			//delay_Find.reset();
			if (distance_check < 300) {
				std::pair<int, int> path = Path1->FindPath(enemyRect.x / 32, enemyRect.y / 32, player->playerRect.x / 32, player->playerRect.y / 32);

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

				m_position.m_x += directionX * 2;
				m_position.m_y += directionY * 2;
				enemyRect.x = m_position.getX() + 60;
				enemyRect.y = m_position.getY() + 90;
			if (Map_lv2::getInstance()->iswall(enemyRect)) {
					m_position.m_x -= directionX * 2;
					m_position.m_y -= directionY * 2;
			}
				

			}
			else {

			}

			//delete Path1;

		}
	}
}
