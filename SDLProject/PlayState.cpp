#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map.h"
#include "PlayState2.h"
#include <cstdlib>
#include "SlimeEnemy.h"
#include "boss2.h"
#include "boss1.h"
//Map* lvl1 = new Map();

std::vector<Enemy*> m_enemies;
std::vector<SlimeEnemy*> m_slimes;
std::vector<chest*> m_chest;

std::vector<tower*> m_towers;
tower* tower1 = new tower(new LoaderParams(500, 500, 100, 140, "assets/tower.png"));
boss1* boss = NULL;

Player* player = NULL;
Portal* portal = NULL;

const const char* PlayState::s_playID = "PLAY";

void PlayState::update1() {

}

void PlayState::update() {
	int cnt = 0;
	if (time.getElapsedTime() > spawnTime && boss->death == 0) {
		int xpos = rand() % 1280;
		int ypos = rand() % 800;
		int monster = rand() % 2;
		int monster2 = rand() % 2;
		int xpos2 = rand() % 1280;
		int ypos2 = rand() % 800;
		Enemy* newEye = new Enemy(new LoaderParams(xpos, ypos, 150, 150, "assets/enemy1Run.png"));
		SlimeEnemy* newSlime = new SlimeEnemy(new LoaderParams(xpos, ypos, 64, 21, "assets/slimeIdle.png"));
		Enemy* newEye2 = new Enemy(new LoaderParams(xpos2, ypos2, 150, 150, "assets/enemy1Run.png"));
		SlimeEnemy* newSlime2 = new SlimeEnemy(new LoaderParams(xpos2, ypos2, 64, 21, "assets/slimeIdle.png"));
		if (difficulty == 2) {
			newEye->damageRes = 1.5;
			newSlime->damageRes = 1.5;
			newEye2->damageRes = 1.5;
			newSlime2->damageRes = 1.5;
		}
		if (monster == 0) {
			m_enemies.push_back(newEye);
		}
		else if (monster == 1) {
			m_slimes.push_back(newSlime);
		}

		if (monster2 == 0) {
			m_enemies.push_back(newEye2);
		}
		else if (monster2 == 1) {
			m_slimes.push_back(newSlime2);
		}
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

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->update();
	}

	for (int i = 0; i < m_chest.size(); ++i) {
		m_chest[i]->move(player);
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

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->move(player, 1);
	}
	//Chuyen man

	if (player->score >= 300) {
		boss->update();
		boss->move(player);
		if (endStage == 0 && boss->death == 1) {
			m_gameObjects.push_back(portal);
			for (int i = 0; i < m_slimes.size(); ++i) {
				m_slimes[i]->death = 1;
			}
			for (int i = 0; i < m_enemies.size(); ++i) {
				m_enemies[i]->death = 1;
			}
			endStage = 1;
		}
		if (boss->death == 1) {
			if (player->getPostiton().getX() >= portal->getPostiton().getX() && player->getPostiton().getY() >= portal->getPostiton().getY() - 40) {
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
				TextureManager::Instance()->clearFromTextureMap("assets/enemy2Run.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy2Hit.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy2Attack.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy2Death.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy3Run.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy3Hit.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy3Attack.png");
				TextureManager::Instance()->clearFromTextureMap("assets/enemy3Death.png");
				TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeDeath.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeHit.png");
				TextureManager::Instance()->clearFromTextureMap("assets/slimeIdle.png");
				TextureManager::Instance()->clearFromTextureMap("assets/portal.png");
				TextureManager::Instance()->clearFromTextureMap("assets/healthUnder.png");
				TextureManager::Instance()->clearFromTextureMap("assets/health.png");
				Mix_HaltMusic();

				Game::Instance()->getStateMachine()->changeState(new PlayState2(difficulty, character));
			}
		}
	}

}

void PlayState::render() {

	//lvl1->drawMapLayer1();
	//lvl1->drawMapLayer2();
	Map::getInstance()->drawMapLayer1();
	Map::getInstance()->drawMapLayer2();

	for (int i = 0; i < m_chest.size(); ++i) {
		m_chest[i]->draw();
	}

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->draw();
	}

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}

	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->draw();
	}


	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->draw();
	}
	if (player->score >= 300) {
		boss->draw();
	}

	Game::Instance()->m_score->draw();
}

bool PlayState::onEnter() {
	endStage = 0;
	Map::getInstance()->LoadMap();
	//erase all old objects
	Mix_HaltMusic();

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->clean();
	}
	for (int i = 0; i < m_slimes.size(); ++i) {
		m_slimes[i]->clean();
	}
	for (int i = 0; i < m_chest.size(); ++i) {
		m_chest[i]->clean();
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->clean();
	}
	m_gameObjects.clear();
	m_enemies.clear();
	m_slimes.clear();
	m_chest.clear();
	m_towers.clear();
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
	TextureManager::Instance()->clearFromTextureMap("assets/enemy2Hit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy2Attack.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy2Death.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy2Run.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy3Hit.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy3Attack.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy3Death.png");
	TextureManager::Instance()->clearFromTextureMap("assets/enemy3Run.png");

	//Load sound and music
	SoundManager::Instance()->load("assets/playState1.wav", "assets/playState1.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState1.wav", 0);


	SoundManager::Instance()->load("assets/walk1.mp3", "assets/walk.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/attack.wav", "assets/attack.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/fireBall.wav", "assets/fireBall.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/damaged.wav", "assets/damaged.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/lightning.wav", "assets/lightning.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/lightningBird.wav", "assets/lightningBird.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/enemy1Damaged.wav", "assets/enemy1Damaged.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/portal.wav", "assets/portal.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/chestOpen.wav", "assets/chestOpen.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/regen.wav", "assets/regen.wav", SOUND_SFX);
	SoundManager::Instance()->load("assets/death.wav", "assets/death.wav", SOUND_SFX);
	//player->collisionPos = lvl1->getCollisionPos();

	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());

	//Load objects

	//Load player
	if (!TextureManager::Instance()->load("assets/player.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	TextureManager::Instance()->load("assets/player1Idle.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/player1Attack.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/player1Hit.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/player1Run.png", Game::Instance()->getRenderer());

	TextureManager::Instance()->load("assets/char3/Idle.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Run.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Attack.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Casting.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Idle2.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Run2.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Attack2.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/char3/Casting2.png", Game::Instance()->getRenderer());


	if (!TextureManager::Instance()->load("assets/player2Sprite.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player3Sprite.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/meguminIdle.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/meguminRun.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/meguminAttack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/meguminDown.png", Game::Instance()->getRenderer()))
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
	if (!TextureManager::Instance()->load("assets/enemy2Run.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy2Attack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy2Hit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy2Death.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy3Run.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy3Attack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy3Hit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy3Death.png", Game::Instance()->getRenderer()))
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
	if (!TextureManager::Instance()->load("assets/blankButton.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	//Load boss
	if (!TextureManager::Instance()->load("assets/boss1Run.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss1Attack2.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss1TakeHit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss1Death.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss2Attack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss2Hit.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss2Death.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/boss2Idle.png", Game::Instance()->getRenderer()))
	{
		return false;
	}

	//Load chest
	if (!TextureManager::Instance()->load("assets/chest.png", Game::Instance()->getRenderer()))
	{
		return false;
	}

	//Load tower
	if (!TextureManager::Instance()->load("assets/tower.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/fireBall.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/fireBallDeath.png", Game::Instance()->getRenderer()))
	{
		return false;
	}

	boss = new boss1(new LoaderParams(500, 500, 250, 250, "assets/boss1Run.png"));

	chest* chest1 = new chest(new LoaderParams(1000, 200, 31, 28, "assets/chest.png"));
	chest* chest2 = new chest(new LoaderParams(1000, 500, 31, 28, "assets/chest.png"));
	chest* chest3 = new chest(new LoaderParams(100, 700, 31, 28, "assets/chest.png"));
	chest* chest4 = new chest(new LoaderParams(560, 260, 31, 28, "assets/chest.png"));
	chest* chest5 = new chest(new LoaderParams(100, 80, 31, 28, "assets/chest.png"));
	m_chest.push_back(chest1);
	m_chest.push_back(chest2);
	m_chest.push_back(chest3);
	m_chest.push_back(chest4);
	m_chest.push_back(chest5);

	//Dang thay GameObject* thanh Player*
	SlimeEnemy* slime = new SlimeEnemy(new LoaderParams(1000, 100, 64, 21, "assets/slimeIdle.png"));

	Enemy* enemy1 = new Enemy(new LoaderParams(1000, 400, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy2 = new Enemy(new LoaderParams(100, 200, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy3 = new Enemy(new LoaderParams(600, 300, 150, 150, "assets/enemy1Run.png"));
	portal = new Portal(new LoaderParams(1050, 500, 128, 128, "assets/portal.png"));

	GameObject* pauseButton = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	//GameObject* scoreButton = new MenuButton(new LoaderParams(990, 10, 78, 36, "assets/blankButton.png"), s_none);
	//GameObject* timeButton = new MenuButton(new LoaderParams(830, 10, 78, 36, "assets/blankButton.png"), s_none);
	//m_gameObjects.push_back(enemy1);
	//m_gameObjects.push_back(enemy2);
	//m_gameObjects.push_back(enemy3);
	//m_slimes.push_back(enemy4);

	m_enemies.push_back(enemy1);
	m_enemies.push_back(enemy2);
	m_enemies.push_back(enemy3);

	m_slimes.push_back(slime);

	m_gameObjects.push_back(pauseButton);
	//m_gameObjects.push_back(scoreButton);
	//m_gameObjects.push_back(timeButton);

	m_towers.push_back(tower1);

	if (difficulty == 1) {
		std::cout << "entering easy PlayState\n";
		spawnTime = 6;
	}
	else if (difficulty == 2) {
		std::cout << "entering hard PlayState\n";
		spawnTime = 4;
		tower* newTower = new tower(new LoaderParams(1000, 300, 100, 140, "assets/tower.png"));
		m_towers.push_back(newTower);
	}

	if (character == 1) {
		std::cout << "Choose character 1\n";
	}
	else if (character == 2) {
		std::cout << "choose character 2\n";
	}
	else if (character == 3) {
		std::cout << "choose character 3\n";
	}
	else if (character == 4) {
		std::cout << "choose  character 4\n";
	}
	if (character == 1) {
		player = new Player(new LoaderParams(150, 150, 100, 100, "assets/player1Idle.png"), character);
	}
	else if (character == 2) {
		player = new Player(new LoaderParams(150, 150, 64, 64, "assets/player2Sprite.png"), character);
	}
	else if (character == 3) {
		player = new Player(new LoaderParams(150, 150, 130, 130, "assets/char3/Idle.png"), character);
	}
	else if (character == 4) {
		player = new Player(new LoaderParams(150, 150, 64, 64, "assets/meguminIdle.png"), character);
	}
	player->getLevel1(true);
	m_gameObjects.push_back(player);
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
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->clean();
	}
	m_slimes.clear();
	m_gameObjects.clear();
	m_enemies.clear();
	m_chest.clear();
	m_towers.clear();
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

	player->getLevel1(0);
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	return true;
}

void PlayState::s_pauseState()
{
	Game::Instance()->getStateMachine()->pushState(new PauseState());
}

