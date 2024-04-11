#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Player;

class SlimeEnemy : public SDLGameObject
{
public:
	SlimeEnemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
private:
	int frame = 7;
	int tick = 100;
	int health = 50;
	SDL_Rect enemyRect;
	Time time;
	int healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	int VecX;
	int VecY;
};

