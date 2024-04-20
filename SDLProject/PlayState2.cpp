#include "PlayState2.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map_lv2.h"
#include "PlayState.h"
#include "Enemy.h"
#include "boss2.h"

const const char* PlayState2::s_play2ID = "PLAY2";

Enemy* enemy = nullptr;
std::vector<tower*> m_towers2;
std::vector<Enemy2*> m_skeletons;
std::vector<Enemy3*> m_goblins;
std::vector<Enemy4*> m_skulls;
std::vector<SlimeEnemy*> m_barrels;

//std::vector<Enemy4*> m_bats;
std::vector<chest*> m_chests2;
boss2* boss = NULL;
boss2* bossSecond = NULL;
Time time_rand;
Portal* portal2 = NULL;
Player* player2 = NULL;

void PlayState2::update() {
	Game::Instance()->playTime.resume();
	if (time.getElapsedTime() > spawnTime && (boss->death == 0 && bossSecond->death == 0)) {
		int xpos = rand() % 15 + 5;
		int ypos = rand() % 30 + 5;

		int xpos2 = rand() % 15 + 5;
		int ypos2 = rand() % 30 + 5;

		Enemy4* newSkull = new Enemy4(new LoaderParams(ypos * 32, xpos * 32, 64, 64, "assets/Bone_enemies.png"));
		Enemy2* newTorch = new Enemy2(new LoaderParams(ypos2*32, xpos2*32, 64, 64, "assets/Torch_Red.png"));
		while (Map_lv2::getInstance()->iswall(newSkull->enemyRect)) {
			xpos = rand() % 15 + 5;
			ypos = rand() % 30 + 5;
			newSkull = new Enemy4(new LoaderParams(ypos * 32, xpos * 32, 64, 64, "assets/Bone_enemies.png"));
		}
		while (Map_lv2::getInstance()->iswall(newTorch->enemyRect)) {
			xpos2 = rand() % 15 + 5;
			ypos2 = rand() % 30 + 5;
			newTorch = new Enemy2(new LoaderParams(ypos2*32, xpos2*32, 64, 64, "assets/Torch_Red.png"));
		}
		SlimeEnemy* newbarrel = new SlimeEnemy(new LoaderParams(100, 200, 64, 64, "assets/Barrel_Red.png"));
		for (int i = 0; i < m_skulls.size(); ++i) {
			if (m_skulls[i]->death == 0) {
				skullCnt++;
			}
			else {
				m_skulls.erase(m_skulls.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < m_skeletons.size(); ++i) {
			if (m_skeletons[i]->death == 0) {
				torchCnt++;
			}
			else {
				m_skeletons.erase(m_skeletons.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < m_barrels.size(); ++i) {
			if (m_barrels[i]->death == 0) {
				barrelCnt++;
			}
			else {
				m_barrels.erase(m_barrels.begin() + i);
				i--;
			}
		}
		if (skullCnt < monsterRistrected) {
			m_skulls.push_back(newSkull);
		}
		if (barrelCnt < monsterRistrected) {
			m_barrels.push_back(newbarrel);
		}
		if (torchCnt < monsterRistrected) {
			m_skeletons.push_back(newTorch);
		}
		skullCnt = 0;
		torchCnt = 0;
		barrelCnt = 0;
		time.reset();
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->update();
	}
	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->move(player2, 2);
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->update();
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->move(player2);
	}
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->update();
	}
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->move(player2);
	}
	for (int i = 0; i < m_skulls.size(); ++i) {
		m_skulls[i]->update();
	}
	for (int i = 0; i < m_skulls.size(); ++i) {
		m_skulls[i]->move(player2);
	}
	for (int i = 0; i < m_barrels.size(); ++i) {
		m_barrels[i]->update();
	}
	for (int i = 0; i < m_barrels.size(); ++i) {
		m_barrels[i]->move(player2);
	}
	/*for (int i = 0; i < m_bats.size(); ++i) {
		m_bats[i]->update();
	}
	for (int i = 0; i < m_bats.size(); ++i) {
		m_bats[i]->move(player, 2);
	}*/
	for (int i = 0; i < m_chests2.size(); ++i) {
		m_chests2[i]->move(player2);
	}

	player2->update();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	if (player2->healthBar <= 0)
	{
		Game::Instance()->getStateMachine()->changeState(new GameOverState());
	}

	if (player2->score >= 300 && warningTime.getElapsedTime() > 7) {
		boss->update();
		boss->move(player2);
		bossSecond->update();
		bossSecond->move(player2);
		if (endStage == 0 && boss->death == 1 && bossSecond->death == 1) {
			endStage = 1;
			m_gameObjects.push_back(portal2);
			for (int i = 0; i < m_barrels.size(); ++i) {
				m_barrels[i]->death = 1;
			}
			for (int i = 0; i < m_skulls.size(); ++i) {
				m_skulls[i]->death = 1;
			}
			for (int i = 0; i < m_skeletons.size(); ++i) {
				m_skeletons[i]->death = 1;
			}
			for (int i = 0; i < m_goblins.size(); ++i) {
				m_goblins[i]->death = 1;
			}
		}
		if (boss->death == 1 && bossSecond->death == 1) {
			if (Map_lv2::getInstance()->checkwall(player2->playerRect, portal2->portalRect)) {
				for (int i = 0; i < m_gameObjects.size(); ++i) {
					m_gameObjects[i]->clean();
				}
				m_gameObjects.clear();
				m_towers2.clear();
				m_skeletons.clear();
				m_chests2.clear();
				m_goblins.clear();
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

				Game::Instance()->getStateMachine()->changeState(new VictoryState);
			}
		}
	}



}
void PlayState2::update1() {

}
void PlayState2::update2() {

}
void PlayState2::update3() {

}
void PlayState2::render() {

	Map_lv2::getInstance()->DrawMap();
	for (int i = 0; i < m_chests2.size(); ++i) {
		m_chests2[i]->draw();
	}
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->draw();
	}

	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->draw();
	}

	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->draw();
	}

	for (int i = 0; i < m_skulls.size(); ++i) {
		m_skulls[i]->draw();
	}

	for (int i = 0; i < m_barrels.size(); ++i) {
		m_barrels[i]->draw();
	}
	//for (int i = 0; i < m_bats.size(); ++i) {
		//m_bats[i]->draw();
	//}
	player2->draw();
	if (player2->score >= 300 && warningTime.getElapsedTime() > 7) {
		boss->draw();
		bossSecond->draw();
	}

	if (player2->score >= 300) {
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
	Game::Instance()->playTime.prinTimeCount(100, 1050, 0, 80, 80);
	Game::Instance()->m_score->draw();

}

bool PlayState2::onEnter() {

	endStage = 0;
	//clear old
	//m_bats.clear();
	m_skeletons.clear();
	m_goblins.clear();
	m_towers2.clear();
	m_gameObjects.clear();
	m_chests2.clear();
	m_skulls.clear();
	m_barrels.clear();
	//Music
	SoundManager::Instance()->load("assets/playState2.wav", "assets/playState2.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState2.wav", 0);


	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());
	if (!TextureManager::Instance()->load("assets/player.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player2Sprite.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player3Sprite.png", Game::Instance()->getRenderer()))
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
	//Load enemy
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
	if (!TextureManager::Instance()->load("assets/Torch_Red.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/TNTAttack.png", Game::Instance()->getRenderer()))
	{
		return false;
	}	
	if (!TextureManager::Instance()->load("assets/Barrel_Red.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/Bone_enemies.png", Game::Instance()->getRenderer()))
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

	//Dang thay GameObject* thanh Player*
	if (character == 1) {
		player2 = new Player(new LoaderParams(800, 600, 100, 100, "assets/player1Idle.png"), character);
	}
	else if (character == 2) {
		player2 = new Player(new LoaderParams(800, 600, 64, 64, "assets/player2Sprite.png"), character);
	}
	else if (character == 3) {
		player2 = new Player(new LoaderParams(800, 600, 130, 130, "assets/char3/Idle.png"), character);
	}
	else if (character == 4) {
		player2 = new Player(new LoaderParams(800, 600, 64, 64, "assets/meguminIlde.png"), character);
	}

	if (difficulty == 1) {
		spawnTime = 6;
		monsterRistrected = 7;
	}
	else if (difficulty == 2) {
		spawnTime = 4;
		monsterRistrected = 10;
		tower* newTower1 = new tower(new LoaderParams(1085, 660, 100, 140, "assets/tower.png"));
		m_towers2.push_back(newTower1);
	}

	portal2 = new Portal(new LoaderParams(100, 50, 128, 128, "assets/portal.png"));
	boss = new boss2(new LoaderParams(100, 200, 90, 90, "assets/boss2Idle.png"), 2);
	bossSecond = new boss2(new LoaderParams(900, 120, 90, 90, "assets/boss2Idle.png"), 2);

	Enemy2* skeleton = new Enemy2(new LoaderParams(100, 400, 64, 64, "assets/Torch_Red.png"));
	Enemy2* skeleton2 = new Enemy2(new LoaderParams(870, 50, 64, 64, "assets/Torch_Red.png"));
	Enemy2* skeleton3 = new Enemy2(new LoaderParams(970, 500, 64, 64, "assets/Torch_Red.png"));
	Enemy3* goblin = new Enemy3(new LoaderParams(1000, 200, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin1 = new Enemy3(new LoaderParams(1120, 260, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin2 = new Enemy3(new LoaderParams(150, 80, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin3 = new Enemy3(new LoaderParams(560, 250, 150, 150, "assets/enemy3Run.png"));

	Enemy4* skull1 = new Enemy4(new LoaderParams(500, 300, 64, 64, "assets/Bone_enemies.png"));

	SlimeEnemy* barrel1 = new SlimeEnemy(new LoaderParams(100, 200, 64, 64, "assets/Barrel_Red.png"));
	SlimeEnemy* barrel2 = new SlimeEnemy(new LoaderParams(600, 600, 64, 64, "assets/Barrel_Red.png"));
	SlimeEnemy* barrel3 = new SlimeEnemy(new LoaderParams(100, 500, 64, 64, "assets/Barrel_Red.png"));
	//Enemy4* bat = new Enemy4(new LoaderParams(560, 100, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat2 = new Enemy4(new LoaderParams(830, 20, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat3 = new Enemy4(new LoaderParams(890, 60, 64, 64, "assets/enemy4Idle.png"));
	//Enemy4* bat4 = new Enemy4(new LoaderParams(165, 110, 64, 64, "assets/enemy4Idle.png"));
	if (difficulty == 2) {
		skeleton->damageRes = 1.5;
		goblin->damageRes = 1.5;
		goblin1->damageRes = 1.5;
		goblin2->damageRes = 1.5;
		goblin3->damageRes = 1.5;
	}
	m_skeletons.push_back(skeleton);
	m_skeletons.push_back(skeleton2);
	m_skeletons.push_back(skeleton3);
	m_goblins.push_back(goblin);
	m_goblins.push_back(goblin1);
	m_goblins.push_back(goblin2);
	m_goblins.push_back(goblin3);
	m_skulls.push_back(skull1);
	m_barrels.push_back(barrel1);
	m_barrels.push_back(barrel2);
	m_barrels.push_back(barrel3);
	//m_bats.push_back(bat);
	//m_bats.push_back(bat2);
	//m_bats.push_back(bat3);
	//m_bats.push_back(bat4);

	//GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	//m_gameObjects.push_back(enemy);
	//m_gameObjects.push_back(player);


	//m_gameObjects.push_back(button1);
	player2->getLevel1(0);
	player2->getLevel2(1);
	player2->getLevel3(0);

	chest* chest1 = new chest(new LoaderParams(1025, 370, 31, 28, "assets/chest.png"));
	chest* chest2 = new chest(new LoaderParams(1040, 470, 31, 28, "assets/chest.png"));
	chest* chest4 = new chest(new LoaderParams(910, 30, 31, 28, "assets/chest.png"));
	chest* chest5 = new chest(new LoaderParams(185, 90, 31, 28, "assets/chest.png"));
	m_chests2.push_back(chest1);
	m_chests2.push_back(chest2);
	m_chests2.push_back(chest4);
	m_chests2.push_back(chest5);

	tower* newTower = new tower(new LoaderParams(330, 400, 100, 140, "assets/tower.png"));
	m_towers2.push_back(newTower);
	std::cout << "entering PlayState2...\n";
	return true;
}

bool PlayState2::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->clean();
	}
	m_gameObjects.clear();
	player2->clean();
	m_towers2.clear();
	m_skeletons.clear();
	m_goblins.clear();
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	//TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	player2->getLevel2(0);
	Map_lv2::getInstance()->CleanMap();
	return true;

}

//void PlayState::s_pauseState()
//{
	//Game::Instance()->getStateMachine()->pushState(new PauseState());
//}