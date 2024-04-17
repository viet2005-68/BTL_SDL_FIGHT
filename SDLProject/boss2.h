#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "FireBall.h"

class boss2 : public SDLGameObject
{
public:
	boss2(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
private:
	int frame = 9;
	int tick = 100;
	int health = 100;
	int dir;
	int fireNum = 5;
	SDL_Rect enemyRect;
	Time time;
	Time test;
	Time attackTime;
	int healthBar = 100;
	int barWidth = 100;
	int barHeight = 16;
	std::vector<FireBall*> m_fireBalls;

	bool Idle;
	bool Hit;
	bool Attack;
};