#pragma once
#include "GameState.h"
#include <vector>
#include <iostream>

class GameStateMachine {
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void update1();
	void render();
private:
	vector<GameState*> m_gameStates;
};
