#pragma once
#include "Game.h"
#include "string.h"

class GameObject;

class VictoryState : public GameState
{
public:
	virtual void update();
	virtual void update1();
	virtual void update2();
	virtual void update3();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_VictoryID;
	}

private:
	static void s_gameQuit();
	static void s_restartPlay();

	static const const char* s_VictoryID;

	GameObject* yesButton = new MenuButton(new LoaderParams(510, 500, 45, 36, "assets/yesButton.png"), s_restartPlay);
	GameObject* noButton = new MenuButton(new LoaderParams(660, 500, 45, 36, "assets/exitHelpButton.png"), s_gameQuit);
	WriteOnScreen* yourScore;

};
