#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "FireBall.h"
#include "Cyclone.h"
#include "Bot.h"

class Bot;
class FireBall;
class finalBoss : public SDLGameObject
{
public:
	finalBoss(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
	bool bossAttacking = 0;

private:
	int frame = 16;
	int tick = 100;
	int health = 100;
	SDL_Rect enemyRect;
	SDL_Rect attackRect;
	Time time;
	int healthBar = 140;
	int barWidth = 200;
	int barHeight = 77;
	int healthHeight = 15;

	Time attackSpeed;
	Time attackedTime;
	Time frameTime;

	int skill = 0;
	Time coolDown;
	Time projectileCoolDown;
	Time cyclonCoolDown;
	std::vector<FireBall*> m_fire;
	Time deathTime;

	Time minionTime;
	std::vector<Bot*> m_minions;

	Time soundTime;
	int startAnimation = 0;

	Time birdTime;
	Time explosionTime;

};