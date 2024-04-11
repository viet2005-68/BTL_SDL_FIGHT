#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Game.h"

class GameObject;

class PlayState2 : public GameState
{
public:
	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_play2ID;
	}
	//static void s_pauseState();


private:
	static const const char* s_play2ID;
	std::vector<GameObject*> m_gameObjects;
	int health = 1000;
};

