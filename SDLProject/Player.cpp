#include "Player.h"
#include "InputHandler.h"
#include <cstdlib>
#include "Game.h"
#include "Map.h"
#include "Map_lv2.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	TextureManager::Instance()->load("assets/Arrow.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/dust.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealthUnder.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealth.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/heart.png", Game::Instance()->getRenderer());
	
	playerRect.w = 32;
	playerRect.h = 32;
	playerRect.x = m_position.m_x + playerRect.w;
	playerRect.y = m_position.m_y + playerRect.h;
	VecX = 0;
	VecY = 0;

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
}

void Player::draw()
{
	SDLGameObject::draw();
	TextureManager::Instance()->draw("assets/playerHealthUnder.png", Game::Instance()->getRenderer(), 65, 20, 100, 27);
	TextureManager::Instance()->draw("assets/playerHealth.png", Game::Instance()->getRenderer(), 65, 20, healthBar, 27);
	TextureManager::Instance()->draw("assets/playerHealthUnder.png", Game::Instance()->getRenderer(), 330, 20, 100, 27);
	TextureManager::Instance()->draw("assets/manaBar.png", Game::Instance()->getRenderer(), 330, 20, mana, 27);
	TextureManager::Instance()->draw("assets/heart.png", Game::Instance()->getRenderer(), 4, 20, 28, 28);
	TextureManager::Instance()->draw("assets/mana.png", Game::Instance()->getRenderer(), 275, 20, 28, 28);

	//DrawBuff
	if (regen == true) {
		TextureManager::Instance()->draw("assets/regeneration.png", Game::Instance()->getRenderer(), 70, 80, 16, 16);
	}
	if (defenseBoost == true) {
		TextureManager::Instance()->draw("assets/defenseBoost.png", Game::Instance()->getRenderer(), 102, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/shield.png", Game::Instance()->getRenderer(), playerRect.x-15, playerRect.y-20, 27, 30, 1, shieldFrame, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/shield.png", Game::Instance()->getRenderer(), playerRect.x-15, playerRect.y-20, 27, 30, 1, shieldFrame, 1);
		}
	}
	if (atkBoost == true) {
		TextureManager::Instance()->draw("assets/attackBoost.png", Game::Instance()->getRenderer(), 134, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/aura.png", Game::Instance()->getRenderer(), playerRect.x-20, playerRect.y-5, 32, 32, 1, auraFrame, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/aura.png", Game::Instance()->getRenderer(), playerRect.x-20, playerRect.y-5, 32, 32, 1, auraFrame, 1);
		}
	}
	if (speedBoost == true) {
		TextureManager::Instance()->draw("assets/speedBoost.png", Game::Instance()->getRenderer(), 166, 80, 16, 16);
		if (m_velocity.getX() > 0) {
			TextureManager::Instance()->drawFrame("assets/speedAnimation.png", Game::Instance()->getRenderer(), playerRect.x-20, playerRect.y-25, 32, 32, 1, (SDL_GetTicks() / 150) % 5, 0);
		}
		else {
			TextureManager::Instance()->drawFrame("assets/speedAnimation.png", Game::Instance()->getRenderer(), playerRect.x-20, playerRect.y-25, 32, 32, 1, shieldFrame, 1);
		}
	}

	TextureManager::Instance()->drawChar("assets/Arrow.png", Game::Instance()->getRenderer(), playerRect.x + 5, playerRect.y - 40, 13, 13, 1, 0, 0);
	if (run == 1 && m_velocity.getX() > 0) {
		TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x - 50, playerRect.y+10, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 0);
	}
	else if (run == 1 && m_velocity.getX() < 0) {
		TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x + 55, playerRect.y+10, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 1);
	}
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(playerRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Player::update()
{
	VecX = 0;
	VecY = 0;
	if (mana < 100 && time.getElapsedTime() > 0.5) {
		mana += 5;
		time.reset();
	}
	//playerRect.x = m_position.m_x+40;
	//playerRect.y = m_position.m_y+40;
	playerRect.x = m_position.m_x + playerRect.w;
	playerRect.y = m_position.m_y + playerRect.h;

	int tick = 100;
	frame = 6;
	m_currentRow = 1;
	run = 0;
	attack = 0;
	dash = 0;

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_x -= speed;
		//chieu am
		m_velocity.setX(-0.001);
		VecX -= speed;
		m_currentRow = 2;
		frame = 6;
		run = 1;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_y -= speed;
		VecY -= speed;
		m_currentRow = 8;
		frame = 3;
		run = 1;
		//move();

	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_y += speed;
		m_currentRow = 6;
		VecY += speed;
		frame = 3;
		run = 1;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_x += speed;
		//chieu duong
		VecX += speed;
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

	//Dash
	if (mana > 0) {
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
			m_position.m_x += 10;
			m_currentRow = 2;
			frame = 6;
			tick = 50;
			mana -= 1;
			dash = 1;
			run = 0;
			time.reset();
			//move();
		}
		else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
			m_position.m_y -= 10;
			m_currentRow = 8;
			frame = 3;
			tick = 50;
			mana -= 1;
			dash = 1;
			run = 0;
			//move();
		}
		else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
			m_position.m_y += 10;
			m_currentRow = 6;
			frame = 3;
			tick = 50;
			mana -= 1;
			dash = 1;
			run = 0;
			//move();
		}
		else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
			m_position.m_x -= 10;
			m_currentRow = 2;
			frame = 6;
			tick = 50;
			mana -= 1;
			dash = 1;
			run = 0;
			//move();
		}
	}

	if (attacked == 1) {
		m_currentRow = 5;
		frame = 3;
		tick = 300;
	}
	if (regen == true) {
		if (regenTime.getElapsedTime() > 1) {
			if (healthBar <= 97) {
				SoundManager::Instance()->playSound("assets/regen.wav", 0);
				healthBar += 3;
			}
			stopRegen++;
			if (stopRegen == 10) {
				regen = false;
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
	else if (dash == 1) {
		SoundManager::Instance()->playSound("assets/dash.wav", 0);
	}
	else {
		Mix_HaltChannel(-1);
	}

	SDLGameObject::update();
}
void Player::move() {
	if (lvl1 == true) {
		playerRect.x = m_position.m_x + playerRect.w;
		playerRect.y = m_position.m_y + playerRect.h;
		if (Map::getInstance()->iswall(playerRect)) {
			m_position.m_x -= VecX;
			
		}
		if (Map::getInstance()->iswall(playerRect)) {
			m_position.m_y -= VecY;

		}
	}
	else if (lvl2 == true) {
		playerRect.x = m_position.m_x + playerRect.w;
		playerRect.y = m_position.m_y + playerRect.h;
		if (Map_lv2::getInstance()->iswall(playerRect)) {
			m_position.m_x -= VecX;

		}
		if (Map_lv2::getInstance()->iswall(playerRect)) {
			m_position.m_y -= VecY;

		}
	}
}
void Player::clean()
{
}