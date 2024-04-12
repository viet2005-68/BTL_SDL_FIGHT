#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class boss1 : public SDLGameObject
{
public:
	boss1(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
private:
	int frame = 8;
	int tick = 100;
	int health = 100;
	SDL_Rect enemyRect;
	Time time;
	int healthBar = 100;
	int barWidth = 100;
	int barHeight = 16;
};