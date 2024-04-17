#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class FireBall : public SDLGameObject
{
public:
	FireBall(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player, int direction, int map);
	bool death = 0;
	double damageRes = 1;
private:
	int frame = 6;
	int tick = 100;
	SDL_Rect enemyRect;
	Time time;
};
