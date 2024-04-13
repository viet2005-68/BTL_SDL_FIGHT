#include "mushroom.h"
#include <cmath>
#include <iostream>
#include "Map_lv2.h"
#include "Time.h"
mushroom::mushroom(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	mushRect.w = 32;
	mushRect.h = 32;
	mushRect.x = m_position.getX() + mushRect.w;
	mushRect.y = m_position.getY() + mushRect.h;
	vecX = 1;
}

void mushroom::draw() {
	SDLGameObject::draw();
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(mushRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), mushRect.x, mushRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), mushRect.x, mushRect.y - 30, healthBar, 8, 1, 0, 0);
}

void mushroom::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	
	mushRect.x = m_position.getX() + mushRect.w;
	mushRect.y = m_position.getY() + mushRect.h;
	SDLGameObject::update();

}

void mushroom::clean() {

}

void mushroom::move(Player* player) {
	
	
	/*else {
		// Nếu không tìm thấy đường đi, di chuyển enemy theo hướng mặc định
		//m_position.m_x += 1;
	}*/

	if (lv2 == true) {
		if (death) {
			m_velocity.setX(0);
			m_velocity.setY(0);
			m_textureID = "assets/Death.png";
			frame = 4;
			tick = 100;
			if (time.getElapsedTime() > 0.3) {

				m_width = 0;
				m_height = 0;
				barHeight = barWidth = 0;
				time.reset();
			}
		}
		else if (abs(player->playerRect.x - mushRect.x) <= 70 && player->playerRect.y + 91 >= mushRect.y && player->playerRect.y <= mushRect.y + 40 && death != true) {

			if (player->attack != 1 || (player->playerRect.x + 80 > mushRect.x + 70 && player->getVelocity().getX() > 0) || (player->playerRect.x + 80 < mushRect.x + 70 && player->getVelocity().getX() < 0)) {
				m_textureID = "assets/Attack.png";
				tick = 150;
				frame = 8;
				if (time.getElapsedTime() > 1) {
					player->healthBar -= 10 / player->defense;
					player->attacked = 1;
					SoundManager::Instance()->playSound("assets/damaged.wav", 0);

					time.reset();
				}
			}
			else if (player->attack == 1) {
				m_textureID = "assets/TakeHit.png";
				frame = 4;
				tick = 200;
				if (time.getElapsedTime() > player->attackSpeed) {
					health -= player->damage * player->damageRatio;
					healthBar -= (player->damage) * player->damageRatio + 7;

					SoundManager::Instance()->playSound("assets/attack.wav", 0);

					time.reset();
				}

				if (healthBar <= 0) {
					player->score += 10;
					std::cout << player->score << std::endl;
					death = true;
				}
			}
			
		}
		else {
			m_textureID = "assets/Idle.png";
			tick = 100;
			frame = 4;
		}
		int distance = sqrt(pow(m_position.m_x - player->m_position.m_x, 2) - pow(m_position.m_y - player->m_position.m_y, 2));
		mushRect.x = m_position.getX();
		mushRect.y = m_position.getY();
		std::pair<int, int> next_tile = Map_lv2::getInstance()->FindOptimalPath(mushRect, player->playerRect);
		if (next_tile.first != 0 && next_tile.second != 0) {

			// Nếu tìm thấy đường đi, tính toán vector vận tốc để di chuyển enemy đến ô tiếp theo
			int dx = next_tile.first * 32 - m_position.m_x;
			int dy = next_tile.second * 32 - m_position.m_y;

			// Chuẩn hóa vector vận tốc và nhân với tốc độ di chuyển mong muốn
			float length = sqrt(dx * dx + dy * dy);

			float velocity_x = 1 * dx / length;
			float velocity_y = 1 * dy / length;
			if (length < 1) return;
			// Cập nhật vị trí của enemy
			m_position.m_x += velocity_x;
			m_position.m_y += velocity_y;

			mushRect.x = m_position.getX() + mushRect.w;
			mushRect.y = m_position.getY() + mushRect.h;


			if (Map_lv2::getInstance()->iswall(mushRect)) {
				m_position.m_x -= velocity_x;
			}
			if (Map_lv2::getInstance()->iswall(mushRect)) {
				m_position.m_y -= velocity_y;
			}

		}
		else {
			SDL_Rect rect = { 320,320,32,32 };
			std::pair<int, int> next_tile_home = Map_lv2::getInstance()->FindPathAStar(mushRect, rect);
			if (next_tile_home.first != 0 && next_tile_home.second != 0) {

				// Nếu tìm thấy đường đi, tính toán vector vận tốc để di chuyển enemy đến ô tiếp theo
				int dx = next_tile_home.first * 32 - m_position.m_x;
				int dy = next_tile_home.second * 32 - m_position.m_y;

				// Chuẩn hóa vector vận tốc và nhân với tốc độ di chuyển mong muốn
				float length = sqrt(dx * dx + dy * dy);

				float velocity_x = 2 * dx / length;
				float velocity_y = 2 * dy / length;
				if (length < 0.5) return;
				// Cập nhật vị trí của enemy
				m_position.m_x += velocity_x;
				m_position.m_y += velocity_y;

				mushRect.x = m_position.getX() + mushRect.w;
				mushRect.y = m_position.getY() + mushRect.h;


				if (Map_lv2::getInstance()->iswall(mushRect)) {
					m_position.m_x -= velocity_x;
				}
				if (Map_lv2::getInstance()->iswall(mushRect)) {
					m_position.m_y -= velocity_y;
				}
			}
		}
	}


	
}

