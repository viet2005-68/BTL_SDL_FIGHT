#pragma once

#include "GameState.h"
#include <vector>
#include "GameObject.h"
#include "MenuButton.h"

class difficultyState : public GameState
{
public:
	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const { return s_difficultyID; }

private:
	static const const char* s_difficultyID;

	static void s_easy();
	static void s_hard();

	GameObject* button1 = new MenuButton(new LoaderParams(540, 420, 115, 53, "assets/easyButton.png"), s_easy);
	GameObject* button2 = new MenuButton(new LoaderParams(540, 560, 115, 53, "assets/hardButton.png"), s_hard);


};