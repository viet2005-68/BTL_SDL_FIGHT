#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Player;

class mushroom : public SDLGameObject
{
public:
	mushroom(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void move(Player* player);
private:
	int heathBar = 50;
	SDL_Rect mushRect;
	Time* time;
	int tick = 100 ;
	int frame = 4;
	int vecX = 1;
};