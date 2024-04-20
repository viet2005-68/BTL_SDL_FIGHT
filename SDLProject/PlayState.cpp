#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map.h"
#include "PlayState2.h"
#include <cstdlib>
#include "SlimeEnemy.h"
#include "boss2.h"

//Map* lvl1 = new Map();

std::vector<Enemy*> m_enemies;
std::vector<Bot*> m_bots;
std::vector<chest*> m_chest;

std::vector<tower*> m_towers;
tower* tower1 = new tower(new LoaderParams(850, 290, 100, 140, "assets/tower.png")); 

finalBoss* finBoss = NULL;
Player* player = NULL;
Portal* portal = NULL;
Bot* bot = NULL;
const const char* PlayState::s_playID = "PLAY";

void PlayState::update1() {

}
void PlayState::update2() {

}
void PlayState::update3() {

}

void PlayState::update() {
	Game::Instance()->playTime.resume();
	player->update();
	int cnt = 0;
	if (time.getElapsedTime() > spawnTime && finBoss->death == 0 && cntSound == 0 && player->score < 300) {
		int xpos1 = rand() % 25;
		int ypos1 = rand() % 40;
		Enemy* newEye = new Enemy(new LoaderParams(xpos1 * 32, ypos1 * 32, 150, 150, "assets/enemy1Run.png"));
		
		Enemy* newEye2 = new Enemy(new LoaderParams(xpos1*32, ypos1*32, 150, 150, "assets/enemy1Run.png"));
		
		int botX = rand() % 15 + 5;
		int botY = rand() % 30+5;
		Bot* bot = new Bot(new LoaderParams(botY * 32, botX * 32, 100, 100, "assets/bot/Run.png"));
		std::cout << botX << " " << botY << std::endl;
		while (Map_lv3::getInstance()->iswall(bot->enemyRect)) {
			botX = rand() % 25;
			botY = rand() % 40;
			bot = new Bot(new LoaderParams(botY * 32, botX * 32, 100, 100, "assets/bot/Run.png"));
		}
		

		if (difficulty == 2) {
			newEye->damageRes = 1.5;
			newEye2->damageRes = 1.5;
			bot->damageRes = 1.5;
		}
		m_enemies.push_back(newEye);
		m_enemies.push_back(newEye2);
		m_bots.push_back(bot);
		

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


	for (int i = 0; i < m_bots.size(); ++i) {
		m_bots[i]->update();
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

	for (int i = 0; i < m_bots.size(); ++i) {
		m_bots[i]->move(player);
	}

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->move(player, 3);
	}
	//Chuyen man

	if (cntSound == 1) {
		for (int i = 0; i < m_enemies.size(); ++i) {
			m_enemies[i]->death = 1;
		}
		for (int i = 0; i < m_bots.size(); ++i) {
			m_bots[i]->death = 1;
		}
	}

	if (player->score >= 300 && warningTime.getElapsedTime() > 7) {
		finBoss->update();
		finBoss->move(player);
		if (endStage == 0 && finBoss->death == 1) {
			endStage = 1;
			m_gameObjects.push_back(portal);
			for (int i = 0; i < m_enemies.size(); ++i) {
				m_enemies[i]->death = 1;
			}
			for (int i = 0; i < m_bots.size(); ++i) {
				m_bots[i]->death = 1;
			}
		}
		if (finBoss->death == 1) {
			if (Map_lv2::getInstance()->checkwall(player->playerRect, portal->portalRect)) {
				for (int i = 0; i < m_gameObjects.size(); ++i) {
					m_gameObjects[i]->clean();
				}
				for (int i = 0; i < m_enemies.size(); ++i) {
					m_enemies[i]->clean();
				}
				for (int i = 0; i < m_bots.size(); ++i) {
					m_bots[i]->clean();
				}
				m_gameObjects.clear();
				m_enemies.clear();
				m_bots.clear();
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
	//Map::getInstance()->drawMapLayer1();
	//Map::getInstance()->drawMapLayer2();
	Map_lv3::getInstance()->DrawMap();
	for (int i = 0; i < m_chest.size(); ++i) {
		m_chest[i]->draw();
	}

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->draw();
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->draw();
	}
	for (int i = 0; i < m_bots.size(); ++i) {
		m_bots[i]->draw();
	}
	player->draw();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}


	if (player->score >= 300 && warningTime.getElapsedTime() > 7) {
		finBoss->draw();
	}

	if (player->score >= 300) {
		if (warningTime.getElapsedTime() < 7) {
			if (cntSound == 0) {
				SoundManager::Instance()->playMusic("assets/warningSound.wav", 0);
				cntSound = 1;
			}
			TextureManager::Instance()->drawFrame("assets/warning.png", Game::Instance()->getRenderer(), 450, 150, 200, 200, 1, (SDL_GetTicks() / 150) % 5, 0);
		}
		else {
			if (cntSound == 1) {
				SoundManager::Instance()->playMusic("assets/bossFight.mp3", 0);
				cntSound = 0;
			}
		}
	}
	else {
		warningTime.reset();
	}
	if (drawPlayTime.getElapsedTime() > 5) {
		Game::Instance()->playTime.prinTimeCount(100, 1050, 0, 80, 80);
	}
	Game::Instance()->m_score->draw();

}

bool PlayState::onEnter() {
	Game::Instance()->m_score->reset();
	drawPlayTime.reset();
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
	for (int i = 0; i < m_chest.size(); ++i) {
		m_chest[i]->clean();
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->clean();
	}
	m_gameObjects.clear();
	m_enemies.clear();
	m_bots.clear();
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
	SoundManager::Instance()->load("assets/bossFight.mp3", "assets/bossFight.mp3", SOUND_MUSIC);
	SoundManager::Instance()->load("assets/warningSound.mp3", "assets/warningSound.wav", SOUND_MUSIC);
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

	//Load boss
	TextureManager::Instance()->load("assets/finalBoss/Idle.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Attack.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Run.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Death.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Health.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Bar.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/finalBoss/Cyclone.png", Game::Instance()->getRenderer());

	//Load bot
	TextureManager::Instance()->load("assets/bot/Run.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Attack.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Death.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Idle.png", Game::Instance()->getRenderer());


	//Load warning
	TextureManager::Instance()->load("assets/warning.png", Game::Instance()->getRenderer());

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
	if (!TextureManager::Instance()->load("assets/enemy4Attack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy4Idle.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/enemy4Death.png", Game::Instance()->getRenderer()))
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

	
	finBoss = new finalBoss(new LoaderParams(1250, 250, 140, 140, "assets/finalBoss/Idle.png"));

	chest* chest1 = new chest(new LoaderParams(1220, 150, 31, 28, "assets/chest.png"));
	chest* chest2 = new chest(new LoaderParams(1000, 500, 31, 28, "assets/chest.png"));
	chest* chest3 = new chest(new LoaderParams(1220, 720, 31, 28, "assets/chest.png"));
	chest* chest4 = new chest(new LoaderParams(220, 560, 31, 28, "assets/chest.png"));
	chest* chest5 = new chest(new LoaderParams(450, 210, 31, 28, "assets/chest.png"));
	m_chest.push_back(chest1);
	m_chest.push_back(chest2);
	m_chest.push_back(chest3);
	m_chest.push_back(chest4);
	m_chest.push_back(chest5);

	//Dang thay GameObject* thanh Player*

	Enemy* enemy1 = new Enemy(new LoaderParams(1000, 400, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy2 = new Enemy(new LoaderParams(100, 200, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy3 = new Enemy(new LoaderParams(600, 300, 150, 150, "assets/enemy1Run.png"));
	Enemy* enemy4 = new Enemy(new LoaderParams(1000, 700, 150, 150, "assets/enemy1Run.png"));

	Bot* bot1 = new Bot(new LoaderParams(1000, 200, 100, 100, "assets/bot/Run.png"));
	Bot* bot2 = new Bot(new LoaderParams(500, 500, 100, 100, "assets/bot/Run.png"));
	Bot* bot3 = new Bot(new LoaderParams(100, 50, 100, 100, "assets/bot/Run.png"));
	Bot* bot4 = new Bot(new LoaderParams(10, 500, 100, 100, "assets/bot/Run.png"));
	Bot* bot5 = new Bot(new LoaderParams(410, 550, 100, 100, "assets/bot/Run.png"));
	Bot* bot6 = new Bot(new LoaderParams(10, 300, 100, 100, "assets/bot/Run.png"));
	m_bots.push_back(bot1);
	m_bots.push_back(bot2);
	m_bots.push_back(bot3);
	m_bots.push_back(bot4);
	m_bots.push_back(bot5);
	m_bots.push_back(bot6);
	//Enemy4* bat = new Enemy4(new LoaderParams(160, 500, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat2 = new Enemy4(new LoaderParams(830, 20, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat3 = new Enemy4(new LoaderParams(890, 60, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat4 = new Enemy4(new LoaderParams(165, 400, 64, 64, "assets/enemy4Idle.png"));
	//m_bats1.push_back(bat);
	//m_bats1.push_back(bat2);
	//m_bats1.push_back(bat3);
	//m_bats1.push_back(bat4);
	portal = new Portal(new LoaderParams(950, 500, 128, 128, "assets/portal.png"));

	GameObject* pauseButton = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);

	//m_gameObjects.push_back(enemy1);
	//m_gameObjects.push_back(enemy2);
	//m_gameObjects.push_back(enemy3);
	//m_slimes.push_back(enemy4);
	
	m_enemies.push_back(enemy1);
	m_enemies.push_back(enemy2);
	m_enemies.push_back(enemy3);
	m_enemies.push_back(enemy4);

	m_gameObjects.push_back(pauseButton);


	m_towers.push_back(tower1);
	
	if (difficulty == 1) {
		std::cout << "entering easy PlayState\n";
		spawnTime = 6;
	}
	else if (difficulty == 2) {
		std::cout << "entering hard PlayState\n";
		spawnTime = 4;
		for (int i = 0; i < m_enemies.size(); ++i) {
			m_enemies[i]->damageRes = 1.5;
		}
		for (int i = 0; i < m_bots.size(); ++i) {
			m_bots[i]->damageRes = 1.5;
		}
		tower* newTower = new tower(new LoaderParams(220, 0, 100, 140, "assets/tower.png"));
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
		player = new Player(new LoaderParams(200, 250, 100, 100, "assets/player1Idle.png"), character);
	}
	else if(character == 2) {
		player = new Player(new LoaderParams(150, 150, 64, 64, "assets/player2Sprite.png"), character);
	}
	else if (character == 3) {
		player = new Player(new LoaderParams(150, 300, 130, 130, "assets/char3/Idle.png"), character);
	}
	else if (character == 4) {
		player = new Player(new LoaderParams(150, 150, 64, 64, "assets/meguminIdle.png"), character);
	}
	player->getLevel3(true);

	return true;
}

bool PlayState::onExit() {
	Game::Instance()->playTime.pause();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->clean();
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->clean();
	}
	m_gameObjects.clear();
	m_enemies.clear();
	m_chest.clear();
	m_towers.clear();
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
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

	player->getLevel3(0);
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	return true;
}

void PlayState::s_pauseState()
{
	Game::Instance()->getStateMachine()->pushState(new PauseState());
}

void PlayState::s_none()
{
}