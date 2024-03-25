#pragma once
#include "Game.h"

class GameObject;

class HelpState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_helpID;
	}

private:
	static void s_helpToMain();
	static const char* s_helpID;
	std::vector<GameObject*> m_gameObjects;
};
