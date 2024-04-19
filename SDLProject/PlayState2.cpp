#include "PlayState2.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Map_lv2.h"
#include "PlayState.h"
#include "mushroom.h"
#include "Enemy.h"
#include "Enemy4.h"
#include "BestScore.h"
#include "Bot.h"
const const char* PlayState2::s_play2ID = "PLAY2";
std::vector<Bot*> ABot;
Enemy* enemy = nullptr;
std::vector<tower*> m_towers2;
std::vector<Enemy2*> m_skeletons;
std::vector<Enemy3*> m_goblins;
std::vector<Enemy4*> m_bats;
std::vector<chest*> m_chests2;

Time time_rand;

void PlayState2::update() {

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}
	
	
	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->update();
	}
	for (int i = 0; i < m_towers2.size(); ++i) {
		m_towers2[i]->move(player, 2);
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->update();
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i] ->move(player);
	}
	for (int i = 0; i < ABot.size(); ++i) {
		ABot[i]->move(player);
	}
	
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->move(player);
	}
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->update();
	}
	for (int i = 0; i < m_bats.size(); ++i) {
		m_bats[i]->move(player);
	}
	for (int i = 0; i < m_bats.size(); ++i) {
		m_bats[i]->update();
	}
	for (int i = 0; i < ABot.size(); ++i) {
		ABot[i]->update();
	}
	//mush->update();
	//mush->move(player);


	player->update();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	if (player->healthBar <= 0)
	{
		Game::Instance()->getStateMachine()->changeState(new GameOverState());
	}
	
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	
}
void PlayState2::update1() {

}
void PlayState2::render() {

	//lvl1->drawMapLayer1();
	//lvl1->drawMapLayer2();
	
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
	for (int i = 0; i < m_bats.size(); ++i) {
		m_bats[i]->draw();
	}
	for (int i = 0; i < ABot.size(); ++i) {
		ABot[i]->draw();
	}
	//enemy->draw();
	//mush->draw();
	Game::Instance()->m_score->draw();
	player->draw();
}

bool PlayState2::onEnter() {
	
	//clear old
	
	m_skeletons.clear();
	m_goblins.clear();
	m_towers2.clear();
	m_gameObjects.clear();
	m_bats.clear();
	m_chests2.clear();
	//Music
	SoundManager::Instance()->load("assets/playState2.wav", "assets/playState2.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState2.wav", 0);

	
	TextureManager::Instance()->load("assets/Torch_Red.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Death.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Attack.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/bot/Run.png", Game::Instance()->getRenderer());

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
		player = new Player(new LoaderParams(200, 200, 100, 100, "assets/player1Idle.png"), character);
	}
	else if (character == 2) {
		player = new Player(new LoaderParams(200, 200, 64, 64, "assets/player2Sprite.png"), character);
	}
	else if (character == 3) {
		player = new Player(new LoaderParams(200, 200, 64, 64, "assets/player3Sprite.png"), character);
	}
	else if (character == 4) {
		player = new Player(new LoaderParams(200, 200, 64, 64, "assets/meguminIlde.png"), character);
	}
	Enemy2* skeleton = new Enemy2(new LoaderParams(100, 400, 64, 64, "assets/enemy2Run.png"));
	Enemy3* goblin = new Enemy3(new LoaderParams(1000, 200, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin1 = new Enemy3(new LoaderParams(1120, 260, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin2 = new Enemy3(new LoaderParams(150, 80, 150, 150, "assets/enemy3Run.png"));
	Enemy3* goblin3 = new Enemy3(new LoaderParams(560, 250, 150, 150, "assets/enemy3Run.png"));
	Enemy4* bat = new Enemy4(new LoaderParams(560, 100, 64, 64, "assets/enemy4Idle.png"));
	Enemy4* bat2 = new Enemy4(new LoaderParams(830, 20, 64, 64, "assets/enemy4Idle.png"));
	Enemy4* bat3 = new Enemy4(new LoaderParams(890, 60, 64, 64, "assets/enemy4Idle.png"));
	Enemy4* bat4 = new Enemy4(new LoaderParams(165, 110, 64, 64, "assets/enemy4Idle.png"));
	Bot* bot = new Bot(new LoaderParams(200, 200, 100, 100, "assets/bot/Run.png"));
	
	ABot.push_back(bot);

	if (difficulty == 2) {
		skeleton->damageRes = 1.5;
		goblin->damageRes = 1.5;
		goblin1->damageRes = 1.5;
		goblin2->damageRes = 1.5;
		goblin3->damageRes = 1.5;
	}
	m_skeletons.push_back(skeleton);
	m_goblins.push_back(goblin);
	m_goblins.push_back(goblin1);
	m_goblins.push_back(goblin2);
	m_goblins.push_back(goblin3);
	m_bats.push_back(bat);
	m_bats.push_back(bat2);
	m_bats.push_back(bat3);
	m_bats.push_back(bat4);
	
	//GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	//m_gameObjects.push_back(enemy);
	//m_gameObjects.push_back(player);


	//m_gameObjects.push_back(button1);
	player->getLevel1(0);
	player->getLevel2(1);
	player->getLevel3(0);

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
	for (int i = 0; i < ABot.size(); ++i) {
		ABot[i]->clean();
	}
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	m_gameObjects.clear();
	player->clean();
	m_towers2.clear();
	m_skeletons.clear();
	m_goblins.clear();
	ABot.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
	//TextureManager::Instance()->clearFromTextureMap("assets/inGamePauseState.png");
	Mix_HaltMusic();
	std::cout << "Exiting PlayState...\n";
	player->getLevel2(0);
	//mush->Setlv2(0);
	Map_lv2::getInstance()->CleanMap();
	return true;
	
}

//void PlayState::s_pauseState()
//{
	//Game::Instance()->getStateMachine()->pushState(new PauseState());
//}