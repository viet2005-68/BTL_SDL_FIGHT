#pragma once
#include "SDLGameObject.h"
#include "Time.h"

class playerFireBall : public SDLGameObject
{
public:
	playerFireBall(const LoaderParams* pParams, int a);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(int map);

	SDL_Rect fireRect;
	bool death = 0;
private:
	int direction;
	int frame = 6;
	int tick = 100;
	Time time;
};
