#pragma once

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "AStarFindPath.h"

class Bot : public SDLGameObject
{
public:
	Bot(const LoaderParams* pParams);
	~Bot() {};
	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
	double damageRes = 1;
	SDL_Rect enemyRect;
private:
	int frame = 8;
	int tick = 100;
	double health = 30;

	SDL_Rect attackRect;
	Time time;
	Time lightning;
	double healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;

	Time birdTime;

	int startAnimation = 0;
	int attackState = 0;
	Time frameTime;
	Time attackSpeed;
	Time attackedTime;
	int startDeathAnimation = 0;
	Time Delay;
	AstarFindPath* Path1;
	double fps = 0.1;
};
