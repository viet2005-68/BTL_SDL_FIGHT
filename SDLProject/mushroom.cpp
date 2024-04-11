#include "mushroom.h"
#include <cmath>
#include <iostream>
#include "Map.h"
#include "Camera.h"
int arr_i[4] = { 1,-1,0,0};
int arr_j[4] = { 0,0,-1,1};
mushroom::mushroom(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	mushRect.w = 32;
	mushRect.h = 32;
	mushRect.x = m_position.getX();
	mushRect.y = m_position.getY();
	vecX = 1;
}

void mushroom::draw() {
	SDLGameObject::draw();
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(mushRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);

}

void mushroom::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));
	Vector2D cam = Camera::GetInstance()->GetPosition();
	mushRect.x = m_position.getX() + 100  - cam.m_x;
	mushRect.y = m_position.getY() + 100 + 128  - cam.m_y;
	SDLGameObject::update();

}

void mushroom::clean() {

}

void mushroom::move(Player* player) {
	int distance = sqrt(pow(m_position.m_x - player->m_position.m_x, 2) - pow(m_position.m_y - player->m_position.m_y, 2));
	std::pair<int, int> next_tile = Map::getInstance()->FindOptimalPath(mushRect, player->playerRect);

	if (next_tile.first != 0 && next_tile.second != 0) {
		Vector2D cam = Camera::GetInstance()->GetPosition();

		// Nếu tìm thấy đường đi, tính toán vector vận tốc để di chuyển enemy đến ô tiếp theo
		int dx = next_tile.first * 32 - m_position.m_x;
		int dy = next_tile.second * 32 - m_position.m_y;

		// Chuẩn hóa vector vận tốc và nhân với tốc độ di chuyển mong muốn
		float length = sqrt(dx * dx + dy * dy);
		float velocity_x = 1 * dx / length;
		float velocity_y = 1 * dy / length;

		// Cập nhật vị trí của enemy
		m_position.m_x += velocity_x;
		m_position.m_y += velocity_y;
		mushRect.x = m_position.m_x + 100 - cam.m_x;
		mushRect.y = m_position.m_y  + 128 - cam.m_y;
		
		if (Map::getInstance()->iswall(mushRect)) {
			m_position.m_x -= velocity_x;
			m_position.m_y -= velocity_y;
		}
	}
	else {

	}
	if (mushRect.x < 0) m_position.m_x = 900;
	if (mushRect.y < 0) m_position.m_y = 900;
	
	/*else {
		// Nếu không tìm thấy đường đi, di chuyển enemy theo hướng mặc định
		//m_position.m_x += 1;
	}*/



	
}

