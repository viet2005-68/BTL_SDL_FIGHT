#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Game.h"
#include "chest.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"

class GameObject;

class PlayState2 : public GameState
{
public:

	PlayState2(int a, int b) {
		difficulty = a;
		character = b;
	}

	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_play2ID;
	}
	//static void s_pauseState();
    Player* player;
	
private:
	int difficulty;
	int character;
	static const const char* s_play2ID;
	std::vector<GameObject*> m_gameObjects;
	int health = 1000;
	
};

