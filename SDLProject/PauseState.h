#pragma once
#include "Game.h";

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const{
		return s_pauseID;
	}
	~PauseState();
private:
	static void s_pauseToMain();
	static void s_resumePlay();

	static const const char* s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};

