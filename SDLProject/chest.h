#pragma once

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class chest : public SDLGameObject
{
public:
	chest(const LoaderParams* pParams);

	virtual void draw();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
private:
	int health = 10;
	SDL_Rect enemyRect;
	Time time;
};