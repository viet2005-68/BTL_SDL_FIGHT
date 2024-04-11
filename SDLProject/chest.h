#pragma once
#include "Player.h"
#include "SDLGameObject.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
class Player;
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