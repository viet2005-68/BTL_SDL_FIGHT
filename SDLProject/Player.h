#pragma once
/*#include "GameObject.h"

using namespace std;

class Player : public GameObject {
public:
	void load(int x, int y, int width, int height, const char* textureID, SDL_Renderer* ren);
	void draw(SDL_Renderer* ren);
	void update();
	void clean();

private:
	int flip = 0;
	int frame;
	int currentRow = 1;

};
*/

#include "SDLGameObject.h"
#include "SoundManager.h"
#include "Map.h"
#include "Camera.h"
#include "Point.h"
#include "Time.h"
class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void move();
	//int** collisionPos;
	inline Point* GetOrigin() {
		return m_origin;
	}
	int currentRow = 1;
	int frame;
	int attacked = 0;
	int attack = 0;

	int damage = 10;
	int healthBar = 100;
	int mana = 100;
	double attackSpeed = 0.4;
	int score = 0;

	SDL_Rect playerRect;

	bool regen = false;
	int stopRegen = 0;

	bool atkBoost = false;
	int stopDefenseBoost = 0;
	int damageRatio = 1;

	bool defenseBoost = false;
	int stopAttackBoost = 0;
	int defense = 1;

	bool speedBoost = false;
	int stopSpeedBoost = 0;
	int speed = 2;

	int shieldFrame = 0;
	int auraFrame = 0;
private:
	int VecX;
	int VecY;
	int run = 0;
	Point* m_origin = new Point(0, 0);

	Time time;
	Time regenTime;
	Time defenseTime;
	Time attackTime;
	Time speedTime;
};
