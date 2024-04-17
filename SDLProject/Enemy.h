#pragma once
/*#include "GameObject.h"

class Enemy : public GameObject {
public:
	void load(int x, int y, int width, int height, const char* textureID, SDL_Renderer* ren);
	void draw(SDL_Renderer* ren);
	void update();
	void clean();
};
*/

#include "SDLGameObject.h"
#include "Player.h"
#include "PlayState.h"
#include "cmath"
#include "Time.h"

class Player;

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
	SDL_Rect getRect() {
		return enemyRect;
	}
	void move(Player* &player);
	void changeRectX(int rectx) {
		enemyRect.x = rectx;
	}
	void changeRectY(int rectx) {
		enemyRect.y = rectx;
	}
	bool death = 0;
	double damageRes = 1;
private:
	int frame = 8;
	int tick = 100;
	int health = 30;
	SDL_Rect enemyRect;
	Time time;
	Time lightning;
	int healthBar = 50;
	int barWidth = 50;
	int barHeight = 8;

	Time birdTime;
};
