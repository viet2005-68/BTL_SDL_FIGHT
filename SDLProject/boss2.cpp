#include "boss2.h"
#include <iostream>


boss2::boss2(const LoaderParams* pParams, int a) : SDLGameObject(pParams)
{
	map = a;
	enemyRect.w = 120;
	enemyRect.h = 80;
	enemyRect.x = m_position.getX()+20;
	enemyRect.y = m_position.getY()+50;

}

void boss2::draw() {
	SDLGameObject::drawBig();
	TextureManager::Instance()->drawChar("assets/finalBoss/Bar.png", Game::Instance()->getRenderer(), enemyRect.x - 40, enemyRect.y - 70, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/finalBoss/Health.png", Game::Instance()->getRenderer(), enemyRect.x + 10, enemyRect.y-22, healthBar, healthHeight, 1, 0, 0);
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
	for (int i = 0; i < m_fireBalls.size(); ++i) {
		m_fireBalls[i]->draw();
	}
}

void boss2::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void boss2::clean() {

}

void boss2::move(Player*& player) {
	enemyRect.x = m_position.getX()+20;
	enemyRect.y = m_position.getY()+50;
	tick = 100;

	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5) {
					health -= player->damage * 2 * player->damageRatio / (damageRes*3);
					healthBar -= ((player->damage) * 2 * player->damageRatio) / (damageRes*3);
					if (healthBar <= 0) {
						Game::Instance()->m_score->Setscore(50);
						player->score += 50;
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
				health -= player->damage * player->damageRatio / (damageRes*3);
				healthBar -= ((player->damage) * player->damageRatio) / (damageRes*3);
				player->m_fireBalls[i]->death = 1;
				if (healthBar <= 0) {
					Game::Instance()->m_score->Setscore(50);
					player->score += 50;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}

		if (player->explosion == 1) {
			healthBar -= 1;
			if (healthBar <= 0) {
				Game::Instance()->m_score->Setscore(50);
				player->score += 50;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}

	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_textureID = "assets/boss2Death.png";
		frame = 8;
		tick = 200;
		if (time.getElapsedTime() > 1.2) {
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
			time.reset();
		}
	}
	else {
		m_textureID = "assets/boss2Idle.png";
		frame = 8;
		tick = 100;

		if (((enemyRect.x + 100 <= player->playerRect.x + 32 && enemyRect.x + 100 >= player->playerRect.x) || (enemyRect.x <= player->playerRect.x + 32 && enemyRect.x + 100 >= player->playerRect.x)) && ((enemyRect.y + 80 >= player->playerRect.y && enemyRect.y <= player->playerRect.y + 32) || (enemyRect.y <= player->playerRect.y + 32) && (enemyRect.y + 80 >= player->playerRect.y))) {
			if (player->attack == 1 && attackTime.getElapsedTime() > player->attackSpeed) {
				healthBar -= (player->damage * player->damageRatio)/2;
				attackTime.reset();
			}
			if (player->skill == 1) {
				if (time.getElapsedTime() > player->attackSpeed) {
					health -= (player->damage * 3 * player->damageRatio)/2;
					healthBar -= ((player->damage + 7) * 3 * player->damageRatio)/2;
					time.reset();
				}
				if (health <= 0) {
					Game::Instance()->m_score->Setscore(50);
					player->score += 50;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}

		if (healthBar <= 0) {
			death = 1;
			time.reset();
		}

		if (enemyRect.x >= player->playerRect.x + 90 && time.getElapsedTime() < 3) {
			m_velocity.setX(-0.0000000001);
			dir = 1;
		}
		else if(enemyRect.x + 120 <= player->playerRect.x && time.getElapsedTime() < 3){
			m_velocity.setX(0);
			dir = 0;
		}
		else if (time.getElapsedTime() > 3) {
			if (time.getElapsedTime() > 11) {
				fireNum = 5;
				time.reset();
			}
			if (fireNum == 0) {
				m_textureID = "assets/boss2Idle.png";
				frame = 8;
				tick = 100;
			}
			else {
				m_textureID = "assets/boss2Attack.png";
				frame = 16;
				tick = 30;
			}
			if (test.getElapsedTime() > 0.5) {
				if (fireNum != 0) {
					FireBall* fire1 = new FireBall(new LoaderParams(m_position.getX() + 80, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
					m_fireBalls.push_back(fire1);
					fireNum--;
				}
				test.reset();
			}
		}
	}
	for (int i = 0; i < m_fireBalls.size(); ++i) {
		m_fireBalls[i]->update();
		m_fireBalls[i]->move(player, dir, map);
	}
}