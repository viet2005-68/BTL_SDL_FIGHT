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
#pragma once
#include "SDLGameObject.h"
#include "SoundManager.h"
#include "time.h"
#include <vector>
#include "lightningBird.h"
#include "playerFireBall.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams, int a);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void move();

	int currentRow = 1;
	int frame;
	int attacked = 0;
	int attack = 0;
	int fireBall = 0;
	int explosion = 0;

	int damage = 10;
	int healthBar = 100;
	int mana = 100;
	int manaRegen = 5;
	double attackSpeed = 0.4;
	int score = 0;

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

	int skill = 0;
	int lightning = 0;
	int lightningBird = 0;
	int direction;

	int shieldFrame = 0;
	int auraFrame = 0;
	SDL_Rect playerRect;
	void getLevel1(bool a) {
		lvl1 = a;
	}
	void getLevel2(bool a) {
		lvl2 = a;
	}
	void getLevel3(bool a) {
		lvl3 = a;
	}
	bool skill1 = true;
	bool skill2 = true;
	bool skill3 = true;
	bool dashSkill = true;

	int cnt = 0;
	int cnt2 = 0;


	//Use this variable to move the sprite position of character 4 for better precision.
	int moveCnt = 0;

	std::vector<class lightningBird*> m_birds;
	std::vector<playerFireBall* > m_fireBalls;
private:
	int characterNum;
	bool lvl1 = false;
	bool lvl2 = false;
	bool lvl3 = false;

	int VecX;
	int VecY;
	int run = 0;
	int dash = 0;
	Time time;

	//Boost timimg
	Time regenTime;
	Time defenseTime;
	Time attackTime;
	Time speedTime;

	Time dashTime;

	Time skillTime;
	Time lightningTime;
	Time lightningBirdTime;

	Time soundLightningTime;
	Time soundLightningBirdTime;
	Time soundExplosionTime;

};
