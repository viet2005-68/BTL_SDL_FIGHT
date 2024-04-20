#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Game.h"

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
	virtual void update2();
	virtual void update3();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_play2ID;
	}
	//static void s_pauseState();
	int cntSound = 0;
private:
	int difficulty;
	int character;
	static const const char* s_play2ID;
	std::vector<GameObject*> m_gameObjects;
	Time time;
	Time warningTime;
	int spawnTime;
	int endStage = 0;

	int monsterRistrected = 7;

	int skullCnt = 0;
	int torchCnt = 0;
	int barrelCnt = 0;
};

