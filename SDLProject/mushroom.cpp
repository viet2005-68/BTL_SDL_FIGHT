#include "mushroom.h"
#include <cmath>
#include <iostream>

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
	
	mushRect.x = m_position.getX() + 100;
	mushRect.y = m_position.getY() + 100;
	SDLGameObject::update();

}

void mushroom::clean() {

}

void mushroom::move(Player* player) {
	
	
	/*else {
		// Nếu không tìm thấy đường đi, di chuyển enemy theo hướng mặc định
		//m_position.m_x += 1;
	}*/



	
}

