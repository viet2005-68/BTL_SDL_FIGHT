#include "Map_lv2.h"
#include "Map_lv3.h"
#include "Map.h"
#include "Player.h"
#include "InputHandler.h"
#include <cstdlib>
#include "Game.h"
#include "Map.h"

Player::Player(const LoaderParams* pParams, int a) : SDLGameObject(pParams)
{
	TextureManager::Instance()->load("assets/Arrow.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/dust.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealthUnder.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealth.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/heart.png", Game::Instance()->getRenderer());

	characterNum = a;
	if (characterNum == 4) {
		damage = 20;
		manaRegen = 10;
	}
	if (characterNum == 1) {
		defense = 2;
		attackSpeed = 0.5;
	}
	if (characterNum == 3) {

	}
	playerRect.w = 33;
	playerRect.h = 33;
	playerRect.x = m_position.getX() + playerRect.w;
	playerRect.y = m_position.getY() + playerRect.h;
	VecX = VecY = 0;

	skill1 = true;
	//Newly added
	TextureManager::Instance()->load("assets/manaBar.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/mana.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/regeneration.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/attackBoost.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/defenseBoost.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/speedBoost.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/shield.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/aura.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/speedAnimation.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/lightningSkill.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/lightningBirdFly.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/lightningBirdDeath.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/meguminFireBall.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/meguminFireBallDeath.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill1.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill2.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill3.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/meguminSkill3.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/dashSkill.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/border.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill1CoolDown.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill2CoolDown.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/skill3CoolDown.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/meguminSkill3CoolDown.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/dashSkillCoolDown.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/statusBox.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/avatar.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/avatar2.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/avatar3.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/avatar4.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/meguminExplosion.png", Game::Instance()->getRenderer());
}

void Player::draw()
{
	SDLGameObject::draw();
	if (explosion == 1) {
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 200, 200, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 400, 100, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 700, 600, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 300, 500, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 200, 600, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 600, 600, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 900, 100, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 1000, 600, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 400, 300, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 500, 500, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 500, 100, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 600, 50, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 800, 600, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 400, 160, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 800, 260, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 860, 360, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
		TextureManager::Instance()->drawFrame("assets/meguminExplosion.png", Game::Instance()->getRenderer(), 700, 360, 64, 64, 1, (SDL_GetTicks() / 150) % 6, 0);
	}
	TextureManager::Instance()->draw("assets/playerHealthUnder.png", Game::Instance()->getRenderer(), 65, 20, 100, 27);//27
	TextureManager::Instance()->draw("assets/playerHealth.png", Game::Instance()->getRenderer(), 65, 20, healthBar, 27);
	TextureManager::Instance()->draw("assets/playerHealthUnder.png", Game::Instance()->getRenderer(), 330, 20, 100, 27);
	TextureManager::Instance()->draw("assets/manaBar.png", Game::Instance()->getRenderer(), 330, 20, mana, 27);
	TextureManager::Instance()->draw("assets/heart.png", Game::Instance()->getRenderer(), 4, 20, 28, 28);
	TextureManager::Instance()->draw("assets/mana.png", Game::Instance()->getRenderer(), 275, 20, 28, 28);
	TextureManager::Instance()->draw("assets/statusBox.png", Game::Instance()->getRenderer(), 10, 680, 300, 58);
	if (characterNum == 1) {
		TextureManager::Instance()->draw("assets/avatar.png", Game::Instance()->getRenderer(), 22, 708, 38, 38);
	}
	else if (characterNum == 2) {
		TextureManager::Instance()->draw("assets/avatar2.png", Game::Instance()->getRenderer(), 22, 708, 38, 38);
	}
	else if (characterNum == 3) {
		TextureManager::Instance()->draw("assets/avatar3.png", Game::Instance()->getRenderer(), 22, 708, 38, 38);
	}
	else if (characterNum == 4) {
		TextureManager::Instance()->draw("assets/avatar4.png", Game::Instance()->getRenderer(), 22, 708, 38, 38);
	}

	//DrawBuff
	if (regen == true) {
		TextureManager::Instance()->draw("assets/regeneration.png", Game::Instance()->getRenderer(), 70, 80, 16, 16);
	}
	if (defenseBoost == true) {
		TextureManager::Instance()->draw("assets/defenseBoost.png", Game::Instance()->getRenderer(), 102, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/shield.png", Game::Instance()->getRenderer(), playerRect.x - 15, playerRect.y - 20, 27, 30, 1, shieldFrame, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/shield.png", Game::Instance()->getRenderer(), playerRect.x - 15, playerRect.y - 20, 27, 30, 1, shieldFrame, 1);
		}
	}
	if (atkBoost == true) {
		TextureManager::Instance()->draw("assets/attackBoost.png", Game::Instance()->getRenderer(), 134, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/aura.png", Game::Instance()->getRenderer(), playerRect.x - 20, playerRect.y - 5, 32, 32, 1, auraFrame, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/aura.png", Game::Instance()->getRenderer(), playerRect.x - 20, playerRect.y - 5, 32, 32, 1, auraFrame, 1);
		}
	}
	if (speedBoost == true) {
		TextureManager::Instance()->draw("assets/speedBoost.png", Game::Instance()->getRenderer(), 166, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/speedAnimation.png", Game::Instance()->getRenderer(), playerRect.x - 20, playerRect.y - 25, 32, 32, 1, (SDL_GetTicks() / 150) % 5, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/speedAnimation.png", Game::Instance()->getRenderer(), playerRect.x - 20, playerRect.y - 25, 32, 32, 1, shieldFrame, 1);
		}
	}

	//Draw Skill
	if (characterNum == 4) {
		if (skill1 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 265, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill1.png", Game::Instance()->getRenderer(), 270, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 265, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill1CoolDown.png", Game::Instance()->getRenderer(), 270, 714, 32, 32);
		}

		if (skill2 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 365, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill2.png", Game::Instance()->getRenderer(), 370, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 365, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill2CoolDown.png", Game::Instance()->getRenderer(), 370, 714, 32, 32);
		}
		if (skill3 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 465, 709, 37, 37);
			TextureManager::Instance()->draw("assets/meguminSkill3.png", Game::Instance()->getRenderer(), 470, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 465, 709, 37, 37);
			TextureManager::Instance()->draw("assets/meguminSkill3CoolDown.png", Game::Instance()->getRenderer(), 470, 714, 32, 32);
		}
		if (dashSkill == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 165, 709, 37, 37);
			TextureManager::Instance()->draw("assets/dashSkill.png", Game::Instance()->getRenderer(), 170, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 165, 709, 37, 37);
			TextureManager::Instance()->draw("assets/dashSkillCoolDown.png", Game::Instance()->getRenderer(), 170, 714, 32, 32);
		}
	}
	else {
		if (skill1 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 265, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill1.png", Game::Instance()->getRenderer(), 270, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 265, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill1CoolDown.png", Game::Instance()->getRenderer(), 270, 714, 32, 32);
		}

		if (skill2 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 365, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill2.png", Game::Instance()->getRenderer(), 370, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 365, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill2CoolDown.png", Game::Instance()->getRenderer(), 370, 714, 32, 32);
		}
		if (skill3 == true) {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 465, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill3.png", Game::Instance()->getRenderer(), 470, 714, 32, 32);
		}
		else {
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 465, 709, 37, 37);
			TextureManager::Instance()->draw("assets/skill3CoolDown.png", Game::Instance()->getRenderer(), 470, 714, 32, 32);
		}
		if (dashSkill == true) {
			
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 165, 709, 37, 37);
			TextureManager::Instance()->draw("assets/dashSkill.png", Game::Instance()->getRenderer(), 170, 714, 32, 32);
		}
		else {
			
			TextureManager::Instance()->draw("assets/border.png", Game::Instance()->getRenderer(), 165, 709, 37, 37);
			TextureManager::Instance()->draw("assets/dashSkillCoolDown.png", Game::Instance()->getRenderer(), 170, 714, 32, 32);
			dashTime.printTimeOnScreen(2 - dashTime.getElapsedTime(), 170, 714, 60, 32);
		}
	}

	TextureManager::Instance()->drawChar("assets/Arrow.png", Game::Instance()->getRenderer(), playerRect.x + 5, playerRect.y - 40, 13, 13, 1, 0, 0);
	if (run == 1 && m_velocity.getX() > 0) {
		if (characterNum == 4) {
			TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x - 50, playerRect.y + 30, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x - 50, playerRect.y + 10, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 0);
		}
	}
	else if (run == 1 && m_velocity.getX() < 0) {
		if (characterNum == 4) {
			TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x + 55, playerRect.y + 30, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 1);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x + 55, playerRect.y + 10, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 1);
		}
	}

	if (skill == 1) {
		TextureManager::Instance()->drawFrame("assets/skill.png", Game::Instance()->getRenderer(), playerRect.x - 80, playerRect.y - 130, 128, 128, 1, ((SDL_GetTicks() / 200) % 10), 0);
	}
	if (lightning == 1) {
		TextureManager::Instance()->drawFrame("assets/lightningSkill.png", Game::Instance()->getRenderer(), playerRect.x - 256, playerRect.y - 400, 256, 256, 1, ((SDL_GetTicks() / 50) % 20), 0);
	}

	for (int i = 0; i < m_birds.size(); ++i) {
		m_birds[i]->draw();
	}
	for (int i = 0; i < m_fireBalls.size(); ++i) {
		m_fireBalls[i]->draw();
	}
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(playerRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Player::update()
{
	if (characterNum == 1) {
		VecX = VecY = 0;
		m_textureID = "assets/player1Idle.png";
		frame = 12;
		if (mana < 100 && time.getElapsedTime() > 0.5 && attack != 1) {
			if (mana + manaRegen > 100) {
				mana = 100;
			}
			else {
				mana += manaRegen;
			}
			time.reset();
		}

		int tick = 100;
		m_currentRow = 1;
		run = 0;
		attack = 0;
		skill = 0;
		dash = 0;
		lightningBird = 0;

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() - speed);
			VecX -= speed;
			//chieu am
			m_velocity.setX(-0.001);
			m_textureID = "assets/player1Run.png";
			frame = 8;
			//m_currentRow = 2;
			//frame = 6;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() - speed);
			VecY -= speed;
			m_textureID = "assets/player1Run.png";
			frame = 8;

			//m_currentRow = 8;
			//frame = 3;
			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() + speed);
			VecY += speed;

			m_textureID = "assets/player1Run.png";
			frame = 8;

			//m_currentRow = 6;
			//frame = 3;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() + speed);
			VecX += speed;
			//chieu duong
			m_velocity.setX(0.001);

			m_textureID = "assets/player1Run.png";
			frame = 8;

			//m_currentRow = 2;
			//frame = 6;

			run = 1;
			//move();

		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) && mana >= 5) {
			//m_currentRow = 3;
			//frame = 6;

			m_textureID = "assets/player1Attack.png";
			frame = 19;
			tick = 50;
			m_width = 100;
			m_height = 100;

			attack = 1;
			//move();
			if (time.getElapsedTime() > attackSpeed) {
				mana -= 5;
				time.reset();
			}
		}

		//Skill
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_K) && mana >= 40) {
			if (skillTime.getElapsedTime() < 1) {
				skill = 1;
				attack = 1;
				if (time.getElapsedTime() > attackSpeed) {
					mana -= 40;
					time.reset();
				}
			}
			if (skillTime.getElapsedTime() > 5) {
				skillTime.reset();
			}
		}

		if (skillTime.getElapsedTime() > 5 && mana >= 40) {
			skill1 = true;
		}
		else {
			skill1 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L) && mana >= 50) {
			if (lightningTime.getElapsedTime() < 0.1) {
				lightning = 1;
				if (cnt == 0) {
					mana -= 50;
					cnt++;
				}
			}
			if (lightningTime.getElapsedTime() > 10) {
				lightningTime.reset();
				cnt = 0;
			}
		}

		if (lightningTime.getElapsedTime() > 5) {
			lightning = 0;
		}
		if (lightningTime.getElapsedTime() > 10 && mana >= 50) {
			skill2 = true;
		}
		else {
			skill2 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_I) && mana >= 30) {
			lightningBird = 1;
			if (lightningBirdTime.getElapsedTime() < 0.05)
			{
				if (m_velocity.getX() >= 0) {
					direction = 0;
				}
				else {
					direction = 1;
				}
				if (cnt2 == 0) {
					m_birds.clear();
					if (m_velocity.getX() >= 0) {
						class lightningBird* newBird = new class lightningBird(new LoaderParams(playerRect.x - 10, playerRect.y - 30, 48, 48, "assets/lightningBirdFly"));
						m_birds.push_back(newBird);
					}
					else {
						class lightningBird* newBird = new class lightningBird(new LoaderParams(playerRect.x - 30, playerRect.y - 30, 48, 48, "assets/lightningBirdFly"));
						m_birds.push_back(newBird);
					}
					mana -= 30;
					cnt++;
				}
			}
			if (lightningBirdTime.getElapsedTime() > 7)
			{
				lightningBirdTime.reset();
				cnt2 = 0;
			}
		}

		if (lightningBirdTime.getElapsedTime() > 7 && mana >= 30)
		{
			skill3 = true;
		}
		else {
			skill3 = false;
		}

		if (dashTime.getElapsedTime() > 2) {
			dashSkill = true;
		}
		else {
			dashSkill = false;
		}

		if (attacked == 1) {

			TextureManager::Instance()->load("assets/player1Hit.png", Game::Instance()->getRenderer());
			m_textureID = "assets/player1Hit.png";
			frame = 7;
			tick = 200;
		}

		//Buff
		if (regen == true) {
			manaRegen = 10;
			if (regenTime.getElapsedTime() > 1) {
				if (healthBar <= 95) {
					SoundManager::Instance()->playSound("assets/regen.wav", 0);
					healthBar += 5;
				}
				stopRegen++;
				if (stopRegen == 10) {
					regen = false;
					manaRegen = 5;
					stopRegen = 0;
				}
				regenTime.reset();
			}
		}

		if (defenseBoost == true) {
			defense = 4;
			if (defenseTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopDefenseBoost++;
				if (stopDefenseBoost == 10) {
					defenseBoost = false;
					defense = 2;
					stopDefenseBoost = 0;
				}
				defenseTime.reset();
			}
		}

		if (atkBoost == true) {
			if (stopAttackBoost == 0) {
				damageRatio = 2;
			}
			if (attackTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopAttackBoost++;
				if (stopAttackBoost == 10) {
					atkBoost = false;
					damageRatio = 1;
					stopAttackBoost = 0;
				}
				attackTime.reset();
			}
		}

		if (speedBoost == true) {
			speed = 4;
			attackSpeed = 0.2;
			tick = 50;
			if (speedTime.getElapsedTime() > 1) {
				stopSpeedBoost++;
				if (stopSpeedBoost == 10) {
					speedBoost = false;
					speed = 2;
					attackSpeed = 0.4;
					stopSpeedBoost = 0;
				}
				speedTime.reset();
			}
		}
		shieldFrame = int(((SDL_GetTicks() / 50) % 6));
		auraFrame = int(((SDL_GetTicks() / 150) % 4));
		move();
		m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
		//Sound
		if (run == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/walk.wav", 0);
		}
		else if (attack == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/enemy1Damaged.wav", 0);
		}
		else if (attacked == 1) {
			SoundManager::Instance()->playSound("assets/damaged.wav", 0);
		}
		else if (lightningBird == 1) {
			SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
		}
		else {
			Mix_HaltChannel(-1);
		}
		if (lightning == 1) {
			if (soundLightningTime.getElapsedTime() > 0.02) {
				SoundManager::Instance()->playSound("assets/lightning.wav", 0);
				soundLightningTime.reset();
			}
		}

		for (int i = 0; i < m_birds.size(); ++i) {
			m_birds[i]->update();
			if (lvl2 == true) {
				m_birds[i]->move(direction, 2);
			}
			else if (lvl1 == true)
			{
				m_birds[i]->move(direction, 1);
			}
		}

		SDLGameObject::update();
	}
	else if (characterNum == 2) {
		VecX = VecY = 0;
		if (mana < 100 && time.getElapsedTime() > 0.5) {
			if (mana + manaRegen > 100) {
				mana = 100;
			}
			else {
				mana += manaRegen;
			}
			time.reset();
		}
		playerRect.x = m_position.getX() + playerRect.w;
		playerRect.y = m_position.getY() + playerRect.h;

		int tick = 100;
		frame = 6;
		m_currentRow = 1;
		run = 0;
		attack = 0;
		skill = 0;
		dash = 0;
		lightningBird = 0;

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() - speed);
			VecX -= speed;
			//chieu am
			m_velocity.setX(-0.001);
			m_currentRow = 2;
			frame = 6;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() - speed);
			VecY -= speed;
			m_currentRow = 8;
			frame = 3;
			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() + speed);
			VecY += speed;
			m_currentRow = 6;
			frame = 3;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() + speed);
			VecX += speed;
			//chieu duong
			m_velocity.setX(0.001);
			m_currentRow = 2;
			frame = 6;

			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) && mana >= 5) {
			m_currentRow = 3;
			frame = 6;
			attack = 1;
			//move();
			if (time.getElapsedTime() > attackSpeed) {
				mana -= 5;
				time.reset();
			}
		}

		//Skill
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_K) && mana >= 40) {
			if (skillTime.getElapsedTime() < 1) {
				skill = 1;
				m_currentRow = 3;
				frame = 6;
				attack = 1;
				if (time.getElapsedTime() > attackSpeed) {
					mana -= 40;
					time.reset();
				}
			}
			if (skillTime.getElapsedTime() > 5) {
				skillTime.reset();
			}
		}

		if (skillTime.getElapsedTime() > 5 && mana >= 40) {
			skill1 = true;
		}
		else {
			skill1 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L) && mana >= 50) {
			if (lightningTime.getElapsedTime() < 0.1) {
				lightning = 1;
				if (cnt == 0) {
					mana -= 50;
					cnt++;
				}
			}
			if (lightningTime.getElapsedTime() > 10) {
				lightningTime.reset();
				cnt = 0;
			}
		}

		if (lightningTime.getElapsedTime() > 5) {
			lightning = 0;
		}
		if (lightningTime.getElapsedTime() > 10 && mana >= 50) {
			skill2 = true;
		}
		else {
			skill2 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_I) && mana >= 30) {
			lightningBird = 1;
			if (lightningBirdTime.getElapsedTime() < 0.05)
			{
				if (m_velocity.getX() >= 0) {
					direction = 0;
				}
				else {
					direction = 1;
				}
				if (cnt2 == 0) {
					m_birds.clear();
					if (m_velocity.getX() >= 0) {
						class lightningBird* newBird = new class lightningBird(new LoaderParams(playerRect.x - 10, playerRect.y - 30, 48, 48, "assets/lightningBirdFly"));
						m_birds.push_back(newBird);
					}
					else {
						class lightningBird* newBird = new class lightningBird(new LoaderParams(playerRect.x - 30, playerRect.y - 30, 48, 48, "assets/lightningBirdFly"));
						m_birds.push_back(newBird);
					}
					mana -= 30;
					cnt++;
				}
			}
			if (lightningBirdTime.getElapsedTime() > 7)
			{
				lightningBirdTime.reset();
				cnt2 = 0;
			}
		}

		if (lightningBirdTime.getElapsedTime() > 7 && mana >= 30)
		{
			skill3 = true;
		}
		else {
			skill3 = false;
		}

		if (dashTime.getElapsedTime() > 2) {
			dashSkill = true;
			
		}
		else {
			
			dashSkill = false;
		}

		if (attacked == 1) {
			m_currentRow = 5;
			frame = 3;
			tick = 300;
		}

		//Buff
		if (regen == true) {
			manaRegen = 10;
			if (regenTime.getElapsedTime() > 1) {
				if (healthBar <= 95) {
					SoundManager::Instance()->playSound("assets/regen.wav", 0);
					healthBar += 5;
				}
				stopRegen++;
				if (stopRegen == 10) {
					regen = false;
					manaRegen = 5;
					stopRegen = 0;
				}
				regenTime.reset();
			}
		}

		if (defenseBoost == true) {
			defense = 3;
			if (defenseTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopDefenseBoost++;
				if (stopDefenseBoost == 10) {
					defenseBoost = false;
					defense = 1;
					stopDefenseBoost = 0;
				}
				defenseTime.reset();
			}
		}

		if (atkBoost == true) {
			if (stopAttackBoost == 0) {
				damageRatio = 2;
			}
			if (attackTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopAttackBoost++;
				if (stopAttackBoost == 10) {
					atkBoost = false;
					damageRatio = 1;
					stopAttackBoost = 0;
				}
				attackTime.reset();
			}
		}

		if (speedBoost == true) {
			speed = 4;
			attackSpeed = 0.2;
			tick = 50;
			if (speedTime.getElapsedTime() > 1) {
				stopSpeedBoost++;
				if (stopSpeedBoost == 10) {
					speedBoost = false;
					speed = 2;
					attackSpeed = 0.4;
					stopSpeedBoost = 0;
				}
				speedTime.reset();
			}
		}
		shieldFrame = int(((SDL_GetTicks() / 50) % 6));
		auraFrame = int(((SDL_GetTicks() / 150) % 4));
		move();
		m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
		//Sound
		if (run == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/walk.wav", 0);
		}
		else if (attack == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/enemy1Damaged.wav", 0);
		}
		else if (attacked == 1) {
			SoundManager::Instance()->playSound("assets/damaged.wav", 0);
		}
		else if (lightningBird == 1) {
			SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
		}
		else {
			Mix_HaltChannel(-1);
		}
		if (lightning == 1) {
			if (soundLightningTime.getElapsedTime() > 0.02) {
				SoundManager::Instance()->playSound("assets/lightning.wav", 0);
				soundLightningTime.reset();
			}
		}

		for (int i = 0; i < m_birds.size(); ++i) {
			m_birds[i]->update();
			if (lvl2 == true) {
				m_birds[i]->move(direction, 2);
			}
			else if (lvl1 == true)
			{
				m_birds[i]->move(direction, 1);
			}
		}

		SDLGameObject::update();
	}

	else if (characterNum == 3) {
		VecX = VecY = 0;
		playerRect.w = 33;
		playerRect.h = 33;
		if (mana < 100 && time.getElapsedTime() > 0.5) {
			if (mana + manaRegen > 100) {
				mana = 100;
			}
			else {
				mana += manaRegen;
			}
			time.reset();
		}
		static int state = 1;
		if (state == 1) {
			m_textureID = "assets/char3/Idle.png";
			frame = 16;
			damage = 10;
		}
		else {
			m_textureID = "assets/char3/Idle2.png";
			frame = 13;
			damage = 20;
		}
		int tick = 100;
		run = 0;
		attack = 0;
		skill = 0;
		dash = 0;
		lightningBird = 0;


		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() - speed);
			VecX -= speed;
			//chieu am
			m_velocity.setX(-0.001);
			if (state == 1) {
				m_textureID = "assets/char3/Run.png";
				frame = 6;
			}
			else {
				m_textureID = "assets/char3/Run2.png";
				frame = 6;
			}
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() - speed);
			VecY -= speed;
			if (state == 1) {
				m_textureID = "assets/char3/Run.png";
				frame = 6;
			}
			else {
				m_textureID = "assets/char3/Run2.png";
				frame = 6;
			}
			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setY(m_position.getY() + speed);
			VecY += speed;
			if (state == 1) {
				m_textureID = "assets/char3/Run.png";
				frame = 6;
			}
			else {
				m_textureID = "assets/char3/Run2.png";
				frame = 6;
			}
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
			m_position.setX(m_position.getX() + speed);
			VecX += speed;
			//chieu duong
			m_velocity.setX(0.001);
			if (state == 1) {
				m_textureID = "assets/char3/Run.png";
				frame = 6;
			}
			else {
				m_textureID = "assets/char3/Run2.png";
				frame = 6;
			}

			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) && mana >= 5) {
			if (state == 1) {
				m_textureID = "assets/char3/Attack.png";
				frame = 20;
			}
			else {
				m_textureID = "assets/char3/Attack2.png";
				frame = 28;
			}
			attack = 1;
			tick = 50;
			//move();
			if (time.getElapsedTime() > attackSpeed) {
				mana -= 5;
				time.reset();
			}
		}

		//Skill
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_K) && mana >= 40) {
			if (skillTime.getElapsedTime() < 1) {
				skill = 1;
				m_currentRow = 3;
				frame = 6;
				attack = 1;
				if (time.getElapsedTime() > attackSpeed) {
					mana -= 40;
					time.reset();
				}
			}
			if (skillTime.getElapsedTime() > 5) {
				skillTime.reset();
			}
		}

		if (skillTime.getElapsedTime() > 5 && mana >= 40) {
			skill1 = true;
		}
		else {
			skill1 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L) && mana >= 50) {
			if (lightningTime.getElapsedTime() < 0.1) {
				lightning = 1;
				if (cnt == 0) {
					mana -= 50;
					cnt++;
				}
			}
			if (lightningTime.getElapsedTime() > 10) {
				lightningTime.reset();
				cnt = 0;
			}
		}

		if (lightningTime.getElapsedTime() > 5) {
			lightning = 0;
		}
		if (lightningTime.getElapsedTime() > 10 && mana >= 50) {
			skill2 = true;
		}
		else {
			skill2 = false;
		}
		std::cout << state << std::endl;
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_I) && mana >= 60) {
			state = 2;
			mana -= 60;
			if (lightningBirdTime.getElapsedTime() > 30)
			{
				lightningBirdTime.reset();
			}
		}

		if (lightningBirdTime.getElapsedTime() > 10) {
			state = 1;
		}

		if (lightningBirdTime.getElapsedTime() > 30 && mana >= 60)
		{
			skill3 = true;
		}
		else {
			skill3 = false;
		}

		if (dashTime.getElapsedTime() > 2) {
			dashSkill = true;
		}
		else {
			dashSkill = false;
		}

		if (attacked == 1) {
			//m_currentRow = 5;
			//frame = 3;
			//tick = 300;
		}

		//Buff
		if (regen == true) {
			manaRegen = 10;
			if (regenTime.getElapsedTime() > 1) {
				if (healthBar <= 95) {
					SoundManager::Instance()->playSound("assets/regen.wav", 0);
					healthBar += 5;
				}
				stopRegen++;
				if (stopRegen == 10) {
					regen = false;
					manaRegen = 5;
					stopRegen = 0;
				}
				regenTime.reset();
			}
		}

		if (defenseBoost == true) {
			defense = 3;
			if (defenseTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopDefenseBoost++;
				if (stopDefenseBoost == 10) {
					defenseBoost = false;
					defense = 1;
					stopDefenseBoost = 0;
				}
				defenseTime.reset();
			}
		}

		if (atkBoost == true) {
			if (stopAttackBoost == 0) {
				damageRatio = 2;
			}
			if (attackTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopAttackBoost++;
				if (stopAttackBoost == 10) {
					atkBoost = false;
					damageRatio = 1;
					stopAttackBoost = 0;
				}
				attackTime.reset();
			}
		}

		if (speedBoost == true) {
			speed = 4;
			attackSpeed = 0.2;
			tick = 50;
			if (speedTime.getElapsedTime() > 1) {
				stopSpeedBoost++;
				if (stopSpeedBoost == 10) {
					speedBoost = false;
					speed = 2;
					attackSpeed = 0.4;
					stopSpeedBoost = 0;
				}
				speedTime.reset();
			}
		}
		shieldFrame = int(((SDL_GetTicks() / 50) % 6));
		auraFrame = int(((SDL_GetTicks() / 150) % 4));
		move();
		m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
		//Sound
		if (run == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/walk.wav", 0);
		}
		else if (attack == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/enemy1Damaged.wav", 0);
		}
		else if (attacked == 1) {
			SoundManager::Instance()->playSound("assets/damaged.wav", 0);
		}
		else if (lightningBird == 1) {
			SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
		}
		else {
			Mix_HaltChannel(-1);
		}
		if (lightning == 1) {
			if (soundLightningTime.getElapsedTime() > 0.02) {
				SoundManager::Instance()->playSound("assets/lightning.wav", 0);
				soundLightningTime.reset();
			}
		}

		SDLGameObject::update();
	}

	//Player 4
	else if (characterNum == 4) {
		VecX = VecY = 0;
		if (mana >= 0) {
			m_textureID = "assets/meguminIdle.png";
			frame = 4;
			m_width = m_height = 64;
		}
		else {
			m_textureID = "assets/meguminDown.png";
			frame = 1;
			m_width = m_height = 50;
		}

		if (mana < 100 && time.getElapsedTime() > 0.5) {
			if (mana + manaRegen > 100) {
				mana = 100;
			}
			else {
				mana += manaRegen;
			}
			time.reset();
		}

		int tick = 100;
		m_currentRow = 1;
		run = 0;
		fireBall = 0;
		attack = 0;
		skill = 0;
		dash = 0;
		lightningBird = 0;

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false && mana >= 0) {
			m_position.setX(m_position.getX() - speed);
			VecX -= speed;
			//chieu am
			m_velocity.setX(-0.001);
			m_textureID = "assets/meguminRun.png";
			m_width = 48;
			frame = 3;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false && mana >= 0) {
			m_position.setY(m_position.getY() - speed);
			VecY -= speed;
			m_textureID = "assets/meguminRun.png";
			m_width = 48;
			frame = 3;
			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false && mana >= 0) {
			m_position.setY(m_position.getY() + speed);
			VecY += speed;
			m_textureID = "assets/meguminRun.png";
			m_width = 48;

			frame = 3;
			run = 1;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false && mana >= 0) {
			m_position.setX(m_position.getX() + speed);
			VecX += speed;
			//chieu duong
			m_velocity.setX(0.001);
			m_textureID = "assets/meguminRun.png";
			m_width = 48;
			frame = 3;

			run = 1;
			//move();

		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) && mana >= 5) {
			if (moveCnt == 0) {
				m_position.setX(m_position.getX() - 30);
				m_position.setY(m_position.getY() - 30);
				moveCnt = 1;
			}
			m_textureID = "assets/meguminAttack.png";
			m_width = 81;
			m_height = 106;
			frame = 3;
			if (m_velocity.getX() >= 0) {
				direction = 0;
			}
			else {
				direction = 1;
			}
			fireBall = 1;
			//attack = 1;
			//move();
			if (time.getElapsedTime() > attackSpeed) {
				mana -= 10;
				playerFireBall* newFireBall = new playerFireBall(new LoaderParams(m_position.getX(), m_position.getY() + 25, 64, 64, "assets/meguminFireBall.png"), direction);
				m_fireBalls.push_back(newFireBall);
				time.reset();
			}
		}
		else {
			if (moveCnt == 1) {
				m_position.setX(m_position.getX() + 30);
				m_position.setY(m_position.getY() + 30);
				moveCnt = 0;
			}
		}

		//Skill
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_K) && mana >= 40) {
			if (skillTime.getElapsedTime() < 1) {
				skill = 1;
				m_currentRow = 3;
				frame = 6;
				attack = 1;
				if (time.getElapsedTime() > attackSpeed) {
					mana -= 40;
					time.reset();
				}
			}
			if (skillTime.getElapsedTime() > 5) {
				skillTime.reset();
			}
		}

		if (skillTime.getElapsedTime() > 5 && mana >= 40) {
			skill1 = true;
		}
		else {
			skill1 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L) && mana >= 50) {
			if (lightningTime.getElapsedTime() < 0.1) {
				lightning = 1;
				if (cnt == 0) {
					mana -= 50;
					cnt++;
				}
			}
			if (lightningTime.getElapsedTime() > 10) {
				lightningTime.reset();
				cnt = 0;
			}
		}
		if (lightningTime.getElapsedTime() > 5) {
			lightning = 0;
		}
		if (lightningTime.getElapsedTime() > 10 && mana >= 50) {
			skill2 = true;
		}
		else {
			skill2 = false;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_I) && mana >= 100 && lightningBirdTime.getElapsedTime() > 7) {
			explosion = 1;
			mana -= 300;
			lightningBirdTime.reset();
		}

		if (lightningBirdTime.getElapsedTime() > 1)
		{
			explosion = 0;
		}

		if (lightningBirdTime.getElapsedTime() > 7 && mana >= 100)
		{
			skill3 = true;
		}
		else {
			skill3 = false;
		}

		if (dashTime.getElapsedTime() > 2) {
			dashSkill = true;
		}
		else {
			dashSkill = false;
		}

		if (attacked == 1) {
			//m_currentRow = 5;
			//frame = 3;
			//tick = 300;
		}

		//Buff
		if (regen == true) {
			manaRegen = 20;
			if (regenTime.getElapsedTime() > 1) {
				if (healthBar <= 95) {
					SoundManager::Instance()->playSound("assets/regen.wav", 0);
					healthBar += 5;
				}
				stopRegen++;
				if (stopRegen == 10) {
					regen = false;
					manaRegen = 10;
					stopRegen = 0;
				}
				regenTime.reset();
			}
		}

		if (defenseBoost == true) {
			defense = 3;
			if (defenseTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopDefenseBoost++;
				if (stopDefenseBoost == 10) {
					defenseBoost = false;
					defense = 1;
					stopDefenseBoost = 0;
				}
				defenseTime.reset();
			}
		}

		if (atkBoost == true) {
			if (stopAttackBoost == 0) {
				damageRatio = 2;
			}
			if (attackTime.getElapsedTime() > 1) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				stopAttackBoost++;
				if (stopAttackBoost == 10) {
					atkBoost = false;
					damageRatio = 1;
					stopAttackBoost = 0;
				}
				attackTime.reset();
			}
		}

		if (speedBoost == true) {
			speed = 4;
			attackSpeed = 0.2;
			tick = 50;
			if (speedTime.getElapsedTime() > 1) {
				stopSpeedBoost++;
				if (stopSpeedBoost == 10) {
					speedBoost = false;
					speed = 2;
					attackSpeed = 0.4;
					stopSpeedBoost = 0;
				}
				speedTime.reset();
			}
		}
		shieldFrame = int(((SDL_GetTicks() / 50) % 6));
		auraFrame = int(((SDL_GetTicks() / 150) % 4));
		move();
		m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
		//Sound
		if (fireBall == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/fireBall.wav", 0);
		}
		else if (run == 1) {
			attacked = 0;
			SoundManager::Instance()->playSound("assets/walk.wav", 0);
		}
		else if (attacked == 1) {
			SoundManager::Instance()->playSound("assets/damaged.wav", 0);
		}
		else if (lightningBird == 1) {
			SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
		}
		else {
			Mix_HaltChannel(-1);
		}
		if (lightning == 1) {
			if (soundLightningTime.getElapsedTime() > 0.02) {
				SoundManager::Instance()->playSound("assets/lightning.wav", 0);
				soundLightningTime.reset();
			}
		}

		for (int i = 0; i < m_fireBalls.size(); ++i) {
			m_fireBalls[i]->update();
			if (lvl2 == true) {
				m_fireBalls[i]->move(2);
			}
			else if (lvl1 == true)
			{
				m_fireBalls[i]->move(1);
			}
		}

		SDLGameObject::update();
	}
}


void Player::move() {
	if (lvl1 == true) {
		if (characterNum == 1) {
			playerRect.x = m_position.m_x + 66 /* + playerRect.w */;
			playerRect.y = m_position.m_y + 80/*+ playerRect.h*/;
		}
		else if (characterNum == 2) {
			playerRect.x = m_position.m_x + playerRect.w;
			playerRect.y = m_position.m_y + playerRect.h;
		}
		else if (characterNum == 3) {
			if (attack == 1) {
				playerRect.w = 100;
				playerRect.x = m_position.m_x + 45;
			}
			else {
				playerRect.x = m_position.m_x + 80;
				playerRect.y = m_position.m_y + 120;
			}
		}
		else if (characterNum == 4) {
			if (moveCnt == 1) {
				playerRect.x = m_position.m_x + playerRect.w + 30;
				playerRect.y = m_position.m_y + playerRect.h + 30;
			}
			else {
				playerRect.x = m_position.getX() + playerRect.w;
				playerRect.y = m_position.getY() + playerRect.h;
			}
		}
		if (Map::getInstance()->iswall(playerRect)) {
			m_position.m_x -= VecX;

		}
		if (Map::getInstance()->iswall(playerRect)) {
			m_position.m_y -= VecY;

		}
		if (mana > 0) {
			SDL_Rect nextPosition;
			if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
				nextPosition = { int(m_position.m_x) + 10 + 32,int(m_position.m_y) + 32, 33,33 };
				if (!Map::getInstance()->iswall(nextPosition)) {
					if (dashTime.getElapsedTime() < 0.2) {
						m_position.m_x += 10;
						playerRect.x = m_position.m_x + playerRect.w;
						playerRect.y = m_position.m_y + playerRect.h;
						//m_currentRow = 2;
						//frame = 6;
						mana -= 1;
						dash = 1;
						run = 0;
					}
				}
				if (dashTime.getElapsedTime() > 2) {
					dashTime.reset();
				}

			}
			else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
				nextPosition = { int(m_position.m_x) + 32,int(m_position.m_y) - 10 + 32, 33,33 };
				if (!Map::getInstance()->iswall(nextPosition)) {
					if (dashTime.getElapsedTime() < 0.2) {
						m_position.m_y -= 10;
						//m_currentRow = 8;
						playerRect.x = m_position.m_x + playerRect.w;
						playerRect.y = m_position.m_y + playerRect.h;
						//frame = 3;
						mana -= 1;
						dash = 1;
						run = 0;
					}
				}
				if (dashTime.getElapsedTime() > 2) {
					dashTime.reset();
				}
			}
			else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
				nextPosition = { int(m_position.m_x) + 32,int(m_position.m_y) + 10 + 32, 33,33 };
				if (!Map::getInstance()->iswall(nextPosition)) {
					if (dashTime.getElapsedTime() < 0.2) {
						m_position.m_y += 10;
						playerRect.x = m_position.m_x + playerRect.w;
						playerRect.y = m_position.m_y + playerRect.h;
						//m_currentRow = 6;
						//frame = 3;
						mana -= 1;
						dash = 1;
						run = 0;
					}
				}
				if (dashTime.getElapsedTime() > 2) {
					dashTime.reset();
				}
			}
			else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
				nextPosition = { int(m_position.m_x) - 10 + 32,int(m_position.m_y) + 32, 33,33 };
				if (!Map::getInstance()->iswall(nextPosition)) {
					if (dashTime.getElapsedTime() < 0.2) {
						m_position.m_x -= 10;
						//m_currentRow = 2;
						playerRect.x = m_position.m_x + playerRect.w;
						playerRect.y = m_position.m_y + playerRect.h;
						//frame = 6;
						mana -= 1;
						dash = 1;
						run = 0;
					}
				}
				if (dashTime.getElapsedTime() > 2) {
					dashTime.reset();
				}
			}
		}
	}
	else if (lvl2 == true) {
		if (characterNum == 1) {
			playerRect.x = m_position.m_x + 66 /* + playerRect.w */;
			playerRect.y = m_position.m_y + 80/*+ playerRect.h*/;
		}
		else if (characterNum == 2) {
			playerRect.x = m_position.m_x + playerRect.w;
			playerRect.y = m_position.m_y + playerRect.h;
		}
		else if (characterNum == 3) {
			playerRect.x = m_position.m_x + 80;
			playerRect.y = m_position.m_y + 120;
		}
		else if (characterNum == 4) {
			if (moveCnt == 1) {
				playerRect.x = m_position.m_x + playerRect.w + 30;
				playerRect.y = m_position.m_y + playerRect.h + 30;
			}
			else {
				playerRect.x = m_position.getX() + playerRect.w;
				playerRect.y = m_position.getY() + playerRect.h;
			}
		}
		if (Map_lv2::getInstance()->iswall(playerRect)) {
			m_position.m_x -= VecX;

		}
		if (Map_lv2::getInstance()->iswall(playerRect)) {
			m_position.m_y -= VecY;

		}
		if (mana > 0) {
			if (characterNum == 1) {
				SDL_Rect nextPosition;
				if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
					nextPosition = { int(m_position.m_x) + 10 + 66,int(m_position.m_y) + 80, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_x += 10;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//m_currentRow = 2;
							//frame = 6;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}

				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
					nextPosition = { int(m_position.m_x) + 66,int(m_position.m_y) - 10 + 80, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_y -= 10;
							//m_currentRow = 8;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//frame = 3;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
					nextPosition = { int(m_position.m_x) + 66,int(m_position.m_y) + 10 + 80, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_y += 10;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//m_currentRow = 6;
							//frame = 3;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
					nextPosition = { int(m_position.m_x) - 10 + 66,int(m_position.m_y) + 80, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_x -= 10;
							//m_currentRow = 2;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//frame = 6;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
			}
			else {
				SDL_Rect nextPosition;
				if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
					nextPosition = { int(m_position.m_x) + 10 + 32,int(m_position.m_y) + 32, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_x += 10;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//m_currentRow = 2;
							//frame = 6;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}

				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
					nextPosition = { int(m_position.m_x) + 32,int(m_position.m_y) - 10 + 32, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_y -= 10;
							//m_currentRow = 8;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//frame = 3;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
					nextPosition = { int(m_position.m_x) + 32,int(m_position.m_y) + 10 + 32, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_y += 10;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//m_currentRow = 6;
							//frame = 3;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
				else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
					nextPosition = { int(m_position.m_x) - 10 + 32,int(m_position.m_y) + 32, 33,33 };
					if (!Map_lv2::getInstance()->iswall(nextPosition)) {
						if (dashTime.getElapsedTime() < 0.2) {
							m_position.m_x -= 10;
							//m_currentRow = 2;
							playerRect.x = m_position.m_x + playerRect.w;
							playerRect.y = m_position.m_y + playerRect.h;
							//frame = 6;
							mana -= 1;
							dash = 1;
							run = 0;
						}
					}
					if (dashTime.getElapsedTime() > 2) {
						dashTime.reset();
					}
				}
			}
		}
	}
}
void Player::clean()
{
}