#pragma once

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Portal : public SDLGameObject
{
public:
	Portal (const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int frame = 8;
	int tick = 200;
	int open = 0;
	Time time;
};
