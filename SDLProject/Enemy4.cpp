#include "Enemy4.h"
#include <iostream>
#include <cstdlib>
#include "Map_lv2.h"
#include <ctime>
int arr[5][5] = { {96,224},{96,400},{296,224},{296,500} };

Enemy4::Enemy4(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	int x = rand() % 5;

	enemyRect.w = 32;
	enemyRect.h = 32;
	m_original.first = m_position.m_x = enemyRect.x = arr[x][0];
	m_original.second = m_position.m_y = enemyRect.y = arr[x][1];
}

void Enemy4::draw() {
	SDLGameObject::draw();
	TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x - 15, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x - 15, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Enemy4::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	SDLGameObject::update();

}

void Enemy4::clean() {

}

void Enemy4::move(Player*& player) {
	enemyRect.x = m_position.getX() + 32;
	enemyRect.y = m_position.getY() + 32;
	m_textureID = "assets/Bone_enemies.png";
	m_currentRow = 1;
	//cout << time.getElapsedTime() << endl;

	if (death != 1) {
		for (int i = 0; i < player->m_birds.size(); ++i) {
			if (player->m_birds[i]->death != 1 && Map_lv2::getInstance()->checkwall(player->m_birds[i]->birdRect, enemyRect)) {
				if (birdTime.getElapsedTime() < 0.2) {
					SoundManager::Instance()->playSound("assets/lightningBird.wav", 0);
				}
				if (birdTime.getElapsedTime() > 0.5) {
					health -= player->damage * 10 * player->damageRatio / damageRes;
					healthBar -= ((player->damage) * 10 * player->damageRatio) / damageRes;
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
				health -= player->damage *10* player->damageRatio / damageRes;
				healthBar -= ((player->damage)*10 * player->damageRatio) / damageRes;
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
		m_textureID = "assets/Bone_enemies.png";
		frame = 6;
		m_currentRow = 4;
		tick = 200;
		if (time.getElapsedTime() > 0.3) {

			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
		}
	}
	else if (Map_lv2::getInstance()->checkwall(enemyRect, player->playerRect)) {

		if (player->attack != 1) {
			m_textureID = "assets/Bone_enemies.png";
			tick = 150;
			frame = 6;
			m_currentFrame = 3;
			if (time.getElapsedTime() > 0.4) {
				player->healthBar -= (5 / player->defense);
				player->attacked = 5;
				SoundManager::Instance()->playSound("assets/damaged.wav", 0);
				//Timer::getInstance()->reset();
				time.reset();
			}
		}
		else if (player->attack == 1) {
			if (time.getElapsedTime() > player->attackSpeed) {
				health = 0;
				healthBar = 0;
				//std::cout << "Flying eye health: " << health << std::endl;
				SoundManager::Instance()->playSound("assets/attack.wav", 0);
				//player->attacked = 0;
				//Timer::getInstance()->reset();
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
	else {
		m_currentRow = 1;
		frame = 6;
		int distance = sqrt(pow(m_position.m_x - player->getPostiton().getX(), 2) - pow(m_position.m_y - player->getPostiton().getY(), 2));
		enemyRect.x = m_position.getX() + 32;
		enemyRect.y = m_position.getY() + 32;
		std::pair<int, int> next_tile = Map_lv2::getInstance()->FindPath(enemyRect, player->playerRect);
		if (next_tile.first != 0 && next_tile.second != 0 && distance < 60) {

			int dx = next_tile.first * 32 - m_position.m_x;
			int dy = next_tile.second * 32 - m_position.m_y;

			float length = sqrt(dx * dx + dy * dy);

			float velocity_x = 1 * dx / length;
			float velocity_y = 1 * dy / length;
			if (length < 1) return;

			m_position.m_x += velocity_x;
			m_position.m_y += velocity_y;

			enemyRect.x = m_position.getX() + enemyRect.w;
			enemyRect.y = m_position.getY() + enemyRect.h;


			if (Map_lv2::getInstance()->iswall(enemyRect)) {
				m_position.m_x -= velocity_x;
			}
			if (Map_lv2::getInstance()->iswall(enemyRect)) {
				m_position.m_y -= velocity_y;
			}

		}

		else {
			float distance = sqrt(pow(m_position.m_x - player->getPostiton().getX(), 2) - pow(m_position.m_y - player->getPostiton().getY(), 2));

			if (distance < 60) {


				int up_move = 10000000;
				int down_move = 10000000;
				int right_move = 10000000;
				int left_move = 10000000;

				upRect = { enemyRect.x, enemyRect.y - 2, enemyRect.w,enemyRect.h };


				downRect = { enemyRect.x, enemyRect.y + 2, enemyRect.w,enemyRect.h };



				rightRect = { enemyRect.x + 2, enemyRect.y, enemyRect.w,enemyRect.h };


				leftRect = { enemyRect.x - 2, enemyRect.y, enemyRect.w,enemyRect.h };


				if (!Map_lv2::getInstance()->iswall(upRect)) {
					up_move = sqrt(pow(upRect.x - player->playerRect.x, 2) + pow(upRect.y - player->playerRect.y, 2));
				}
				if (!Map_lv2::getInstance()->iswall(downRect)) {
					down_move = sqrt(pow(downRect.x - player->playerRect.x, 2) + pow(downRect.y - player->playerRect.y, 2));
				}
				if (!Map_lv2::getInstance()->iswall(rightRect)) {
					right_move = sqrt(pow(rightRect.x - player->playerRect.x, 2) + pow(rightRect.y - player->playerRect.y, 2));
				}
				if (!Map_lv2::getInstance()->iswall(leftRect)) {
					left_move = sqrt(pow(leftRect.x - player->playerRect.x, 2) + pow(leftRect.y - player->playerRect.y, 2));
				}


				std::vector<int> moves;

				moves.push_back(up_move);
				moves.push_back(down_move);
				moves.push_back(right_move);
				moves.push_back(left_move);

				std::sort(moves.begin(), moves.end());

				bool flag = false;

				if (up_move == moves[0] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (down_move == moves[0] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (right_move == moves[0] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();

					flag = true;
				}
				else if (left_move == moves[0] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();

					flag = true;
				}
				if (flag == false && up_move == moves[1] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[1] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[1] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[1] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (flag == false && up_move == moves[2] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[2] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[2] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[2] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (flag == false && up_move == moves[3] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[3] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[3] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[3] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (Map_lv2::getInstance()->iswall(downRect) || Map_lv2::getInstance()->iswall(rightRect)) {
					m_velocity.setX(-0.0001);
				}

			}
			else {
				int up_move = 10000000;
				int down_move = 10000000;
				int right_move = 10000000;
				int left_move = 10000000;

				upRect = { enemyRect.x, enemyRect.y - 2, enemyRect.w,enemyRect.h };


				downRect = { enemyRect.x, enemyRect.y + 2, enemyRect.w,enemyRect.h };



				rightRect = { enemyRect.x + 2, enemyRect.y, enemyRect.w,enemyRect.h };


				leftRect = { enemyRect.x - 2, enemyRect.y, enemyRect.w,enemyRect.h };


				if (!Map_lv2::getInstance()->iswall(upRect)) {
					up_move = sqrt(pow(upRect.x - m_original.first, 2) + pow(upRect.y - m_original.second, 2));
				}
				if (!Map_lv2::getInstance()->iswall(downRect)) {
					down_move = sqrt(pow(downRect.x - m_original.first, 2) + pow(downRect.y - m_original.second, 2));
				}
				if (!Map_lv2::getInstance()->iswall(rightRect)) {
					right_move = sqrt(pow(rightRect.x - m_original.first, 2) + pow(rightRect.y - m_original.second, 2));
				}
				if (!Map_lv2::getInstance()->iswall(leftRect)) {
					left_move = sqrt(pow(leftRect.x - m_original.first, 2) + pow(leftRect.y - m_original.second, 2));
				}


				std::vector<int> moves;

				moves.push_back(up_move);
				moves.push_back(down_move);
				moves.push_back(right_move);
				moves.push_back(left_move);

				std::sort(moves.begin(), moves.end());

				bool flag = false;

				if (up_move == moves[0] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (down_move == moves[0] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (right_move == moves[0] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();

					flag = true;
				}
				else if (left_move == moves[0] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();

					flag = true;
				}
				if (flag == false && up_move == moves[1] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[1] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[1] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[1] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (flag == false && up_move == moves[2] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[2] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[2] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[2] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (flag == false && up_move == moves[3] && Map_lv2::getInstance()->iswall(upRect) == false && up_move != 10000000) {
					move_UP();
					flag = true;
				}
				else if (flag == false && down_move == moves[3] && Map_lv2::getInstance()->iswall(downRect) == false && down_move != 10000000) {
					move_DOWN();
					flag = true;
				}
				else if (flag == false && right_move == moves[3] && Map_lv2::getInstance()->iswall(rightRect) == false && right_move != 10000000) {
					move_RIGHT();
					flag = true;
				}
				else if (flag == false && left_move == moves[3] && Map_lv2::getInstance()->iswall(leftRect) == false && left_move != 10000000) {
					move_LEFT();
					flag = true;
				}
				if (Map_lv2::getInstance()->iswall(downRect) || Map_lv2::getInstance()->iswall(rightRect)) {
					m_velocity.setX(-0.0001);
				}

			}

		}


	}
}
