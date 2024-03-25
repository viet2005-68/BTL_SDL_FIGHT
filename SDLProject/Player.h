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
	int score = 0;

	SDL_Rect playerRect;
private:
	int VecX;
	int VecY;
	int run = 0;
	Point* m_origin = new Point(0, 0);

};
