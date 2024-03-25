#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map.h"
#include "PlayState2.h"
#include <cstdlib>
#include "SlimeEnemy.h"
#include "Camera.h"

Map* lvl1 = new Map();

std::vector<Enemy*> m_enemies;
std::vector<SlimeEnemy*> m_slimes;
Player* player = NULL;
//SlimeEnemy* slime = NULL;
Portal* portal = NULL;
//Enemy* enemy1 = NULL;
//Enemy* enemy2 = NULL;
//Enemy* enemy3 = NULL;

const const char* PlayState::s_playID = "PLAY";
int arr[4][2] = { {300,300},{300,250},{300,250},{300,250} };
void PlayState::update() {
	int cnt = 0;
	if (time.getElapsedTime() > 5) {
		Vector2D cam = Camera::GetInstance()->GetPosition();
		int i = rand() % 4;
		//int j = rand() % 2;
		int xpos = arr[i][0] - cam.m_x;
		int ypos = arr[i][1] - cam.m_y;
		Enemy* newEye =  new Enemy(new LoaderParams(xpos, ypos, 150, 150, "assets/enemy1Run.png"));
		
		SlimeEnemy* newSlime = new SlimeEnemy(new LoaderParams(xpos / 2, ypos / 2, 96, 32, "assets/slimeIdle.png"));
		m_enemies.push_back(newEye);
		m_slimes.push_back(newSlime);
		time.reset();
	}

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->update();
	}

	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->update();
	}

	if (player->healthBar <= 0) {
	Game::Instance()->getStateMachine()->changeState(new GameOverState());
    }

	// flying eye
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->move(player);
	}

	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->move(player);
	}

	//Chuyen man

	if (player->score >= 100) {
		if (endStage == 0) {
			m_gameObjects.push_back(portal);
			endStage = 1;
		}
			if (player->getPostiton().getX() >= portal->getPostiton().getX()-50 && player->getPostiton().getY() >= portal->getPostiton().getY() - 40) {
				for (int i = 0; i < m_gameObjects.size(); ++i) {
					m_gameObjects[i]->clean();
				}
				for (int i = 0; i < m_enemies.size(); ++i) {
					m_enemies[i]->clean();
				}
				for (int i = 0; i < m_slimes.size(); ++i) {
					m_slimes[i]->clean();
				}
				m_slimes.clear();
				m_gameObjects.clear();
				m_enemies.clear();
				TextureManager::Instance()->clearFromTextureMap("assets/player.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy1Run.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy1Hit.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy1Attack.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy1Death.png");
				TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeDeath.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeHit.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeIdle.png");
				TextureManager::Instance()->clearFromTextureMap("assets/portal.png");
				TextureManager::Instance()->clearFromTextureMap("assets/healthUnder.png");
				TextureManager::Instance()->clearFromTextureMap("assets/health.png");
				Mix_HaltMusic();

				Game::Instance()->getStateMachine()->pushState(new PlayState2());
			}
		}

	Camera::GetInstance()->Update(player->getPostiton().m_x, player->getPostiton().m_y);
	    
	}

void PlayState::render() {

	//lvl1->drawMapLayer1();
	//lvl1->drawMapLayer2();

	Map::getInstance()->DrawMap();

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}

	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->draw();
	}

	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->draw();
	}
}

bool PlayState::onEnter() {

	endStage = 0;

	//erase all old objects
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->clean();
	}
	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->clean();
	}
	m_gameObjects.clear();
	m_enemies.clear();
	m_slimes.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Run.png");
	TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Hit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Attack.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Death.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeDeath.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeHit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeIdle.png");
	TextureManager::Instance()->clearFromTextureMap("assets/portal.png");
	TextureManager::Instance()->clearFromTextureMap("assets/healthUnder.png");
	TextureManager::Instance()->clearFromTextureMap("assets/health.png");


	//Load sound and music
	SoundManager::Instance()->load("assets/playState1.wav", "assets/playState1.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState1.wav", 0);


	SoundManager::Instance()->load("assets/walk1.mp3", "assets/walk.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/attack.wav", "assets/attack.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/damaged.wav", "assets/damaged.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/enemy1Damaged.wav", "assets/enemy1Damaged.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/portal.wav", "assets/portal.wav", SOUND_SFX);

	//lvl1->LoadMap();
	//player->collisionPos = lvl1->getCollisionPos();

	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());

	//Load objects
	if (!TextureManager::Instance()->load("assets/player.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy1Run.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy1Attack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy1Hit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy1Death.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/slimeDeath.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/slimeHit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/slimeIdle.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/healthUnder.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/health.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/portal.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	

	//Dang thay GameObject* thanh Player*
	SlimeEnemy* slime = new SlimeEnemy(new LoaderParams(1000, 100, 96, 32, "assets/slimeIdle.png"));
	player = new Player(new LoaderParams(50, 50, 180, 182, "assets/player.png"));
	Enemy* enemy1 = new Enemy(new LoaderParams(1000, 400, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy2 = new Enemy(new LoaderParams(100, 200, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy3 = new Enemy(new LoaderParams(600, 300, 150, 150, "assets/enemy1Run.png"));
	
	portal = new Portal(new LoaderParams(1100, 500, 128, 128, "assets/portal.png"));
	
	GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	m_gameObjects.push_back(player);
	//m_gameObjects.push_back(enemy1);
	//m_gameObjects.push_back(enemy2);
	//m_gameObjects.push_back(enemy3);
	//m_slimes.push_back(enemy4);
	
	m_enemies.push_back(enemy1);
	m_enemies.push_back(enemy2);
	m_enemies.push_back(enemy3);

	m_slimes.push_back(slime);
	m_gameObjects.push_back(button1);
	

	//player->collisionPos = lvl1->getCollisionPos();

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->clean();
	}
	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->clean();
	}
	m_slimes.clear();
	m_gameObjects.clear();
	m_enemies.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Run.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Hit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Attack.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy1Death.png");
	TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeDeath.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeHit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/slimeIdle.png");
	TextureManager::Instance()->clearFromTextureMap("assets/portal.png");
	TextureManager::Instance()->clearFromTextureMap("assets/healthUnder.png");
	TextureManager::Instance()->clearFromTextureMap("assets/health.png");
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	return true;
}

void PlayState::s_pauseState()
{
	Game::Instance()->getStateMachine()->pushState(new PauseState());
}