#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Cyclone : public SDLGameObject
{
public:
	Cyclone(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
	double damageRes = 1;
private:
	int frame = 27;
	int tick = 100;
	SDL_Rect enemyRect;
	Time time;
	Time animationTime;
};
