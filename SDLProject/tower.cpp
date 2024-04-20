#include "tower.h"
#include "SoundManager.h"
#include <iostream>

tower::tower(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_fire.clear();
	enemyRect.w = 70;
	enemyRect.h = 40;
	enemyRect.x = m_position.getX();
	enemyRect.y = m_position.getY();

}

void tower::draw() {
	SDLGameObject::draw();
	//TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, barWidth, barHeight, 1, 0, 0);
	//TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y - 30, healthBar, 8, 1, 0, 0);
	//SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
	for (int i = 0; i < m_fire.size(); ++i) {
		m_fire[i]->draw();
	}
}

void tower::update() {
	m_currentFrame = int(((SDL_GetTicks() / tick) % 11));

	SDLGameObject::update();

}

void tower::clean() {

}

void tower::move(Player*& player, int map) {
	enemyRect.x = m_position.getX() + 70;
	enemyRect.y = m_position.getY() + 100;
	m_textureID = "assets/tower.png";
	//cout << time.getElapsedTime() << endl;
	if (death) {
		m_velocity.setX(0);
		m_velocity.setY(0);
		if (time.getElapsedTime() > 0.3) {
			m_width = 0;
			m_height = 0;
			barHeight = barWidth = 0;
			healthBar = 0;
			time.reset();
		}
	}
	else {
		if (time.getElapsedTime() > 3) {
			m_fire.clear();
			FireBall* fire1 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
			FireBall* fire2 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
			FireBall* fire3 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
			FireBall* fire4 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
			FireBall* fire5 = new FireBall(new LoaderParams(m_position.getX() + 50, m_position.getY() + 50, 46, 46, "assets/fireBall.png"));
			m_fire.push_back(fire1);
			m_fire.push_back(fire2);
			m_fire.push_back(fire3);
			m_fire.push_back(fire4);
			m_fire.push_back(fire5);
			time.reset();
		}
	}
	for (int i = 0; i < m_fire.size(); ++i) {
		m_fire[i]->update();
		m_fire[i]->move(player,i, map);
	}
}