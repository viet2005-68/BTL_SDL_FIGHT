#pragma once

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Enemy3 : public SDLGameObject
{
public:
	Enemy3(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
	double damageRes = 1;
private:
	int frame = 8;
	int tick = 100;
	double health = 30;
	SDL_Rect enemyRect;
	Time time;
	Time lightning;
	double healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	int des_X_left;
	int des_X_right;
	Time birdTime;
};
