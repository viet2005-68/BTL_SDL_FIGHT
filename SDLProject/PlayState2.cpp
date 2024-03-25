#include "PlayState2.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map.h"
#include "PlayState.h"

Map* lvl2 = new Map();

const const char* PlayState2::s_play2ID = "PLAY2";

void PlayState2::update() {

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	health-=10;
	std::cout << "health: " << health << endl;
	if (health == 0)
	{
		Game::Instance()->getStateMachine()->changeState(new GameOverState());
	}

}

void PlayState2::render() {

	//lvl1->drawMapLayer1();
	//lvl1->drawMapLayer2();

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}
}

bool PlayState2::onEnter() {

	//Music
	SoundManager::Instance()->load("assets/playState2.wav", "assets/playState2.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState2.wav", 0);

	//lvl1->LoadMap();
	//player->collisionPos = lvl1->getCollisionPos();

	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());
	if (!TextureManager::Instance()->load("assets/playerTemp.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/bossIdle.png", Game::Instance()->getRenderer())) {
		return false;
	}

	//Dang thay GameObject* thanh Player*
	Player* player = new Player(new LoaderParams(0, 0, 180, 182, "assets/player.png"));
	GameObject* enemy1 = new Enemy(new LoaderParams(1000, 400, 160, 144, "assets/bossIdle.png"));
	//GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy1);
	//m_gameObjects.push_back(button1);


	//player->collisionPos = lvl1->getCollisionPos();

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState2::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	TextureManager::Instance()->clearFromTextureMap("assets/bossIdle.png");
	//TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	return true;
}

//void PlayState::s_pauseState()
//{
	//Game::Instance()->getStateMachine()->pushState(new PauseState());
//}