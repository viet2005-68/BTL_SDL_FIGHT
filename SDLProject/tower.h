#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "FireBall.h"
#include <vector>

class FireBall;

class tower : public SDLGameObject
{
public:
	tower(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player, int map);
	bool death = 0;
	double damageRes = 1;
private:
	int frame = 8;
	int tick = 100;
	double health = 30;
	SDL_Rect enemyRect;
	Time time;
	double healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	std::vector<FireBall* > m_fire;
};
