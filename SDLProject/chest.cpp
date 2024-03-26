
#include "chest.h"
#include "SoundManager.h"
#include "cstdlib"
#include <iostream>


chest::chest(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	enemyRect.w = 50;
	enemyRect.h = 42;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();

}

void chest::draw() {
	SDLGameObject::draw();
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void chest::clean() {

}

void chest::move(Player* &player) {

	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();
	m_textureID = "assets/chest.png";
	m_currentFrame = 0;
	if (death) {
		m_currentFrame = 1;
	}
	else if (abs(player->playerRect.x - (enemyRect.x - 25)) <= 50 && player->playerRect.y + 91 >= enemyRect.y && player->playerRect.y <= enemyRect.y + 42 && death != true) {
		if ((player->attack == 1 && player->playerRect.x + 80 < enemyRect.x + 50 && player->getVelocity().getX() > 0) || (player->attack == 1 && player->playerRect.x + 80 > enemyRect.x + 50 && player->getVelocity().getX() < 0)) {
			if (time.getElapsedTime() > 0.4) {
				health -= player->damage;
				time.reset();
			}
			if (health <= 0) {
				int choice = rand() % 4 + 1;
				SoundManager::Instance()->playSound("assets/chestOpen.wav", 0);
				if (choice == 1) {
					player->regen = true;
					player->stopRegen = 0;
				}
				else if (choice == 2) {
					player->defenseBoost = true;
					player->stopDefenseBoost = 0;
				}
				else if (choice == 3) {
					player->atkBoost = true;
					player->stopAttackBoost = 0;
				}
				else if (choice == 4) {
					player->speedBoost = true;
					player->stopSpeedBoost = 0;
				}
				death = 1;
			}
		}
	}
}
