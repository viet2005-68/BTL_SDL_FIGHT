#include "SlimeEnemy.h"
#include <iostream>
#include "Vector2D.h"
#include "Map_lv2.h"


SlimeEnemy::SlimeEnemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 48;
	enemyRect.h = 32;
	enemyRect.x = m_position.m_x + 32;
	enemyRect.y = m_position.m_y + 32;
	VecX = 1;
	//VecX = 1;
	//find_road = new AStar();
	//VecY = 0;
	path2 = new AstarFindPath(Map_lv2::getInstance()->GetTileCheck());
	x_original = m_position.m_x;
	y_original = m_position.m_y;
}

void SlimeEnemy::draw() {

	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), healthXpos, healthYpos, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), healthXpos, healthYpos, healthBar, 8, 1, 0, 0);
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void SlimeEnemy::update() {

	if (frameTime.getElapsedTime() > attackTime) {
		m_currentFrame++;
		frameTime.reset();
	}
	if (m_currentFrame >= frame) {
		m_currentFrame = 1;
	}
	SDLGameObject::update();

	//enemyRect.x = m_position.m_x + 20;
	//enemyRect.y = m_position.m_y + 25;
}

void SlimeEnemy::clean() {}

void SlimeEnemy::move(Player*& player) {
	if (death != 1) {
		enemyRect.x = m_position.getX() + 25;
		enemyRect.y = m_position.getY() + 25;
	}
	m_textureID = "assets/Barrel_Red.png";
	m_currentRow = 2;
	frame = 6;
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
		m_textureID = "assets/TNTAttack.png";
		barHeight = barWidth = healthBar = 0;
		m_currentRow = 1;
		frame = 9;
		tick = 200;
		attackTime = 0.2;
		enemyRect.x = m_position.m_x;
		enemyRect.y = m_position.m_y;
		enemyRect.w = enemyRect.h = 100;
		if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect) && m_currentFrame >= 4 && stop == 0) {
			if (explosionTime.getElapsedTime() > 0.1) {
				player->healthBar -= 4/player->defense;
				explosionTime.reset();
			}
		}
		if (startAnimation == 1) {
			m_currentFrame = 1;
			startAnimation = 0;
		}
		if (m_currentFrame == 8) {
			m_width = m_height = 0;
			stop = 1;
		}
	}
	else if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect) && death != 1) {
		death = 1;
		startAnimation = 1;
	}
	else {
		healthXpos = enemyRect.x - 5;
		healthYpos = enemyRect.y - 25;
		m_textureID = "assets/Barrel_Red.png";
		m_currentRow = 2;
		frame = 6;
		time.reset();
		float deltaXRect = enemyRect.x - player->playerRect.x;
		float deltaYRect = enemyRect.y - player->playerRect.y;
		float distance_check = sqrt(deltaXRect * deltaXRect + deltaYRect * deltaYRect);
		if (distance_check < 400) {
			std::pair<int, int> path = path2->FindPath(enemyRect.x / 32, enemyRect.y / 32, player->playerRect.x / 32, player->playerRect.y / 32);

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
		else
		{
			healthXpos = enemyRect.x - 21;
			healthYpos = enemyRect.y - 30;
			std::pair<int, int> path = path2->FindPath(enemyRect.x / 32, enemyRect.y / 32, x_original / 32, y_original / 32);

			float deltaX = path.first - int(enemyRect.x / 32);
			float deltaY = path.second - int(enemyRect.y / 32);
			float distance = sqrt(deltaX * deltaX + deltaY * deltaY);


			float directionX;
			float directionY;

			directionX = deltaX / distance;
			directionY = deltaY / distance;
			if (distance < 1) {
				return;
			}
			if (directionX < 0) {
				m_velocity.setX(-0.0001);
			}
			else {
				m_velocity.setX(0.00001);
			}

			m_position.m_x += directionX * 1;
			m_position.m_y += directionY * 1;
			enemyRect.x = m_position.getX() + 64;
			enemyRect.y = m_position.getY() + 64;
		}
	}
	

}
