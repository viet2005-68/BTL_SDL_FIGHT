#pragma once
#include "Game.h"

class GameObject;

class CharacterState : public GameState
{
public:
	virtual void update();
	virtual void update1();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual const char* getStateID() const {
		return s_characterID;
	}
private:
	static void s_player1();
	static void s_player2();
	static void s_player3();
	static void s_player4();
	static const char* s_characterID;
	std::vector<GameObject*> m_char;
	//GameObject* player1 = new MenuButton(new LoaderParams(100, 200, 38, 38, "assets/player1.png"), s_player1);
	//GameObject* player2 = new MenuButton(new LoaderParams(200, 200, 38, 38, "assets/player2.png"), s_player2);
	GameObject* player4 = new MenuButton(new LoaderParams(400, 200, 38, 38, "assets/player4.png"), s_player4);
};