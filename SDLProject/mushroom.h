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
	void Setlv1(bool lv) {
		lv1 = lv;
	}
	void Setlv2(bool lv) {
		lv2 = lv;
	}
	bool death = 0;
private:
	int heathBar = 50;
	SDL_Rect mushRect;
	//Time* time;
	int tick = 100 ;
	int frame = 4;
	int vecX = 1;
	bool lv1;
	bool lv2;
	int healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	int health= 30;
	Time time;
};