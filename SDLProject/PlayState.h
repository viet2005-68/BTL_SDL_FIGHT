#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Game.h"
#include "Enemy.h"
#include "Portal.h"
#include "chest.h"
#include "Time.h"

class GameObject;

class PlayState : public GameState
{
public: 
	PlayState(int a) {
		difficulty = a;
	}
	PlayState(){}
	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_playID;
	}
	static void s_pauseState();

	~PlayState();
private:
	static const const char* s_playID;
	std::vector<GameObject*> m_gameObjects;
	int score = 0;
	Time time;

	int difficulty = 1;
	int spawnTime;
	int endStage = 0;
};

