#pragma once

#include "GameState.h"
#include <vector>
#include "GameObject.h"
#include "MenuButton.h"
//#include "LoaderParams.h"

class MenuState : public GameState
{
public: 
	virtual void update();
	virtual void update1();
	virtual void update2();
	virtual void update3();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const { return s_menuID; }

private:
	static const const char* s_menuID;
	std::vector<GameObject*> m_gameObjects;
	
	static void s_menuToPlay();
	static void s_exitFromMenu();
	static void s_help();
	static void s_volumeMute();
	static void s_volumeUnmute();

	GameObject* button1 = new MenuButton(new LoaderParams(100, 400, 115, 53, "assets/playButton.png"), s_menuToPlay);
	GameObject* button3 = new MenuButton(new LoaderParams(100, 520, 115, 53, "assets/helpButton.png"), s_help);


};

