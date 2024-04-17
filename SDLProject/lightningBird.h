#pragma once
#include "SDLGameObject.h"
#include "Time.h"

class lightningBird : public SDLGameObject
{
public:
	lightningBird(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(int direction, int map);

	SDL_Rect birdRect;
	bool death = 0;
private:
	int frame = 8;
	int tick = 100;
	Time time;
};
