#pragma once

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "AStarFindPath.h"

class Enemy2 : public SDLGameObject
{
public:
	Enemy2(const LoaderParams* pParams);

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
	double health = 50;

	Time time;
	double healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	int status;
	Time birdTime;
	Time lightning;
	Time attackedTime;
	SDL_Rect upRect;
	SDL_Rect downRect;
	SDL_Rect leftRect;
	SDL_Rect rightRect;
	AstarFindPath* Path;
	Time delay_Find;
	bool fight = true;
	int speed_back = 0.1;
};