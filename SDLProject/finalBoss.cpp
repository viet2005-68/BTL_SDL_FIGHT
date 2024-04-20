#include "finalBoss.h"
#include <iostream>

Cyclone* cyclone = NULL;

finalBoss::finalBoss(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 140;
	enemyRect.h = 140;
	enemyRect.x = m_position.getX()+80;
	enemyRect.y = m_position.getY()+100;
	attackRect.w = 160;
	attackRect.h = 190;
	attackRect.x = m_position.getX()+120;
	attackRect.y = m_position.getY()+100;
	m_currentFrame = 1;
	cyclone = NULL;
	attackedTime.reset();
	coolDown.reset();
	frameTime.reset();
	attackSpeed.reset();
}

void finalBoss::draw() {
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(attackRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
	for (int i = 0; i < m_fire.size(); ++i) {
		m_fire[i]->draw();
	}
	for (int i = 0; i < m_minions.size(); ++i) {
		m_minions[i]->draw();
	}
	if (cyclone != NULL) {
		cyclone->draw();
	}
	SDLGameObject::drawBig();
	TextureManager::Instance()->drawOG("assets/finalBoss/Bar.png", Game::Instance()->getRenderer(), enemyRect.x - 45, enemyRect.y - 30, barWidth, barHeight);
	TextureManager::Instance()->drawOG("assets/finalBoss/Health.png", Game::Instance()->getRenderer(), enemyRect.x - 15, enemyRect.y + 2, healthBar, healthHeight);
}

void finalBoss::update() {
	//m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	if (frameTime.getElapsedTime() > 0.1) {
		m_currentFrame++;
		frameTime.reset();
	}
	if (m_currentFrame >= frame) {
		m_currentFrame = 1;
	}
	SDLGameObject::update();

}

void finalBoss::clean() {

}

void finalBoss::move(Player*& player) {

	if (m_velocity.getX() >= 0) {
		attackRect.x = m_position.getX() + 120;
		attackRect.y = m_position.getY() + 100;
	}
	else {
		attackRect.x = m_position.getX();
		attackRect.y = m_position.getY() + 100;
	}

	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5) {
					health -= (player->damage * 3 * player->damageRatio) / (3);
					healthBar -= ((player->damage) * 3 * player->damageRatio) / (3);
					if (healthBar <= 0) {
						Game::Instance()->m_score->Setscore(100);
						player->score += 100;
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
				health -= (player->damage * player->damageRatio)/3;
				healthBar -= (player->damage * player->damageRatio)/3;
				player->m_fireBalls[i]->death = 1;
				if (healthBar <= 0) {
					Game::Instance()->m_score->Setscore(100);
					player->score += 100;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
		}

		if (player->explosion == 1) {
			if (explosionTime.getElapsedTime() > 0.02) {
				healthBar -= 1;
				explosionTime.reset();
			}
			if (healthBar <= 0) {
				Game::Instance()->m_score->Setscore(100);
				player->score += 100;
				std::cout << player->score << std::endl;
				death = true;
			}
		}
	}


	if (death == 1) {
		frame = 25;
		for (int i = 0; i < m_minions.size(); ++i) {
			m_minions[i]->death = 1;
		}
		static int deathCnt = 0;
		if (deathCnt == 0) {
			m_currentFrame = 1;
			deathCnt = 1;
		}
		m_textureID = "assets/finalBoss/Death.png";
		tick = 200;
		if (m_currentFrame == 24) {
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = healthHeight =  0;
		}
		m_fire.clear();
	}
	else {
		deathTime.reset();

		if (m_position.m_x > 600) {
			//m_position.m_x-=1;
			m_velocity.setX(-1);
			m_textureID = "assets/finalBoss/Run.png";
			frame = 10;
			enemyRect.x = m_position.getX() + 80;
			enemyRect.y = m_position.getY() + 100;
		}

		else if (m_position.m_x <= 600) {
			if (player->playerRect.x + 33 <= enemyRect.x+70 && skill != 1) {
				m_velocity.setX(-0.00000001);
			}
			else if (player->playerRect.x > enemyRect.x + 70 && skill != 1) {
				m_velocity.setX(0);
			}
			else {
				m_velocity.setX(0);
			}

			//projectile
			if (projectileCoolDown.getElapsedTime() > 7) {
				m_fire.clear();
				FireBall* fire1 = new FireBall(new LoaderParams(m_position.getX() + 150, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				FireBall* fire2 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				FireBall* fire3 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 100, 46, 46, "assets/fireBall.png"));
				FireBall* fire4 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				FireBall* fire5 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				FireBall* fire6 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 200, 46, 46, "assets/fireBall.png"));
				FireBall* fire7 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				FireBall* fire8 = new FireBall(new LoaderParams(m_position.getX() + 100, m_position.getY() + 150, 46, 46, "assets/fireBall.png"));
				m_fire.push_back(fire1);
				m_fire.push_back(fire2);
				m_fire.push_back(fire3);
				m_fire.push_back(fire4);
				m_fire.push_back(fire5);
				m_fire.push_back(fire6);
				m_fire.push_back(fire7);
				m_fire.push_back(fire8);
				projectileCoolDown.reset();
			}
			for (int i = 0; i < m_fire.size(); ++i) {
				m_fire[i]->update();
				m_fire[i]->move(player, i, 3);
			}

			//Minions
			if (minionTime.getElapsedTime() > 20) {
				Bot* bot1 = new Bot(new LoaderParams(m_position.getX() + 200, m_position.getY() + 200, 100, 100, "assets/bot/Run.png"));
				Bot* bot2 = new Bot(new LoaderParams(m_position.getX() + 200, m_position.getY(), 100, 100, "assets/bot/Run.png"));
				Bot* bot3 = new Bot(new LoaderParams(m_position.getX() - 100, m_position.getY(), 100, 100, "assets/bot/Run.png"));
				Bot* bot4 = new Bot(new LoaderParams(m_position.getX() - 100, m_position.getY() + 200, 100, 100, "assets/bot/Run.png"));
				m_minions.push_back(bot1);
				m_minions.push_back(bot2);
				m_minions.push_back(bot3);
				m_minions.push_back(bot4);
				minionTime.reset();
			}
			for (int i = 0; i < m_minions.size(); ++i) {
				m_minions[i]->update();
				m_minions[i]->move(player);
			}

			//Cyclone
			if (cyclonCoolDown.getElapsedTime() > 10) {
				cyclone = new Cyclone(new LoaderParams(player->playerRect.x-90, player->playerRect.y - 570, 160, 450, "assets/finalBoss/Cyclone.png"));
				cyclonCoolDown.reset();
			}
			if (cyclone != NULL) {
				cyclone->update();
				cyclone->move(player);
			}

			if (Map_lv2::getInstance()->checkwall(player->playerRect, enemyRect)) {
				if (coolDown.getElapsedTime() > 10) {
					bossAttacking = 1;
				}
				if (player->attack == 1 && player->attacked != 1 && skill != 1) {
					if (attackedTime.getElapsedTime() > player->attackSpeed) {
						health -= player->damage * player->damageRatio / 3;
						healthBar -= player->damage * player->damageRatio / 3;
						attackedTime.reset();
					}
					if (healthBar <= 0) {
						Game::Instance()->m_score->Setscore(100);
						player->score += 100;
						death = 1;
					}
				}
			}
			if (bossAttacking == 1) {
				if (startAnimation == 0) {
					m_currentFrame = 1;
					startAnimation = 1;
				}

				if (time.getElapsedTime() < 3.9) {
					m_textureID = "assets/finalBoss/Attack.png";
					frame = 39;
					skill = 1;
					if (soundTime.getElapsedTime() > 0.1) {
						SoundManager::Instance()->playSound("assets/fireBall.wav", 0);
						soundTime.reset();
					}
				}
				else {
					bossAttacking = 0;
					time.reset();
					skill = 0;
				}

				if (Map_lv2::getInstance()->checkwall(player->playerRect, attackRect)) {
					if (time.getElapsedTime() > 2.2) {
						if (attackSpeed.getElapsedTime() > 0.2) {
							player->healthBar -= 5 / player->defense;
							player->attacked = 1;
							attackSpeed.reset();
						}
					}
				}
			}
			else {
				m_textureID = "assets/finalBoss/Idle.png";
				frame = 16;
				startAnimation = 0;
				time.reset();
				//m_currentFrame = 1;
			}
			if (skill == 1) {
				coolDown.reset();
			}
		}
	}
}