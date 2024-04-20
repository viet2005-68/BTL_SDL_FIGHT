#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Game.h"
#include "Enemy.h"
#include "boss1.h"
#include "chest.h"
#include "Portal.h"
#include "Time.h"

class GameObject;

class PlayState : public GameState
{
public: 
	PlayState(int a, int b) {
		difficulty = a;
		character = b;
	}
	//PlayState(){}
	virtual void update();
	virtual void update1();
	virtual void update2();
	virtual void update3();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_playID;
	}
	static void s_pauseState();
	static void s_none();

	int cntSound = 0;

private:
	static const const char* s_playID;
	std::vector<GameObject*> m_gameObjects;
	int score = 0;
	Time time;

	Time warningTime;
	Time drawPlayTime;

	int difficulty;
	int character;

	int spawnTime;
	int endStage = 0;
};

