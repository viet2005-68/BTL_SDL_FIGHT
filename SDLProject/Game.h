#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Bot.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "finalBoss.h"
#include "tower.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "difficultyState.h"
#include "CharacterState.h"
#include "CharacterStateHard.h"
#include "PlayState.h"
#include "PlayState2.h"
#include "PauseState.h"
#include "HelpState.h"
#include "Vector2D.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "SoundManager.h"
#include "MenuButton.h"
#include "Map_lv2.h"
#include "Map_lv3.h"
#include "ScorePlayer.h"
#include "BestScore.h"
#include "Time.h"

using namespace std;

class Game {
public:
	//Game() {};
	//~Game();
	void init(const char* title, int w, int h, bool fullscreen);
	void render();
	void update();
	void handleEvent();
	void clean();
	void Quit();
	SDL_Renderer* getRenderer() const { return renderer; }

	bool running(){
		return isRunning;
	}

	static Game* Instance() {
		if (g_instance == 0) {
			g_instance = new Game();
		}return g_instance;
	}

	GameStateMachine* getStateMachine() {
		return m_pGameStateMachine;
	}
	
	ScorePlayer* m_score;
	Time playTime;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	static Game* g_instance;
	bool isRunning = true;
	int currentFrame;

	//GameObject* m_player;
	//GameObject* m_enemy;
	//GameObject* m_boss;
	vector<GameObject*> m_gameObjects;
	//TextureManager texture;

	GameStateMachine* m_pGameStateMachine;

};

