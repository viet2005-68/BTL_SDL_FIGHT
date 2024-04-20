#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include <stack>
#include "Time.h"
#include "lightningBird.h"
#include "playerFireBall.h"
class Enemy4 : public SDLGameObject
{
public:
	Enemy4(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;

	void move_UP() {
		m_position.m_y -= 0.4;
		//enemyRect.y -= 2;
	}
	void move_DOWN() {
		m_position.m_y += 0.4;
		//enemyRect.y += 2;
	}
	void move_RIGHT() {
		m_position.m_x += 0.4;
		//enemyRect.x += 2;
		m_velocity.setX(0);
	}
	void move_LEFT() {
		m_position.m_x -= 0.4;
		//enemyRect.x -= 2;
		m_velocity.setX(-0.000000001);
	}
	double damageRes = 1;
	SDL_Rect enemyRect;
private:
	SDL_Rect upRect;
	SDL_Rect downRect;
	SDL_Rect rightRect;
	SDL_Rect leftRect;
	int frame = 5;
	int tick = 100;
	double health = 30;

	Time birdTime;
	Time time;
	Time lightning;
	double healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	std::pair<int, int> m_original;
};