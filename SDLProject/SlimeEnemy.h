#pragma once
#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"
#include "AStarFindPath.h"

class Player;

class SlimeEnemy : public SDLGameObject
{
public:
	SlimeEnemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void move(Player*& player);
	bool death = 0;
	double damageRes = 1;
	void updateBotMovement(float deltaTime) {

	}
private:
	bool circle;
	int frame = 7;
	int tick = 100;
	int health = 50;
	SDL_Rect enemyRect;
	Time time;
	float movementAngle = 0;
	//Time Lightning;
	int healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;
	int VecX;
	int VecY;
	Time lightning;
	Time birdTime;
	AstarFindPath* path2;
	int startAnimation = 0;
	Time frameTime;
	double attackTime = 0.1;
	Time explosionTime;
	int stop = 0;
	int set_Up;
	int set_Down;
	int x_original;
	int y_original;
	int healthXpos;
	int healthYpos;
};

