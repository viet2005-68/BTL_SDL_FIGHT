#include "PlayState2.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map_lv2.h"
#include "PlayState.h"
#include "mushroom.h"
#include "Enemy.h"

const const char* PlayState2::s_play2ID = "PLAY2";

mushroom* mush = nullptr;
Enemy* enemy = nullptr;

void PlayState2::update() {

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	mush->move(player);
	mush->update();

	enemy->move(player);
	enemy->update();

	player->update();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	//health-=10;
	std::cout << "health: " << health << endl;
	if (health == 0)
	{
		Game::Instance()->getStateMachine()->changeState(new GameOverState());
	}
	
	
	
}
void PlayState2::update1() {

}
void PlayState2::render() {

	//lvl1->drawMapLayer1();
	//lvl1->drawMapLayer2();
	
	Map_lv2::getInstance()->DrawMap();
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	
	player->draw();
	enemy->draw();
	mush->draw();
	
}

bool PlayState2::onEnter() {
	
	//Music
	SoundManager::Instance()->load("assets/playState2.wav", "assets/playState2.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState2.wav", 0);


	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());
	if (!TextureManager::Instance()->load("assets/playerTemp.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/bossIdle.png", Game::Instance()->getRenderer())) {
		return false;
	}

	//Dang thay GameObject* thanh Player*
	player = new Player(new LoaderParams(200, 200, 64, 64, "assets/player.png"));
	GameObject* enemy1 = new Enemy(new LoaderParams(1000, 400, 160, 144, "assets/bossIdle.png"));
	enemy = new Enemy(new LoaderParams(1000, 400, 150, 150, "assets/enemy1Run.png"));
	//GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	//m_gameObjects.push_back(enemy);
	m_gameObjects.push_back(enemy1);
	//m_gameObjects.push_back(player);
	
	
	//m_gameObjects.push_back(button1);
	player->getLevel2(1);

	//player->collisionPos = lvl1->getCollisionPos();
	mush = new mushroom(new LoaderParams(200, 200, 150, 150, "assets/Idle.png"));
	mush->Setlv2(1);
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState2::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	player->clean();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	TextureManager::Instance()->clearFromTextureMap("assets/bossIdle.png");
	//TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	player->getLevel2(0);
	mush->Setlv2(0);
	Map_lv2::getInstance()->CleanMap();
	return true;
	
}

//void PlayState::s_pauseState()
//{
	//Game::Instance()->getStateMachine()->pushState(new PauseState());
//}