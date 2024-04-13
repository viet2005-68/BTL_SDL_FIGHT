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
std::vector<Enemy*> m_eyes;
std::vector<tower*> m_towers;
std::vector<Enemy2*> m_skeletons;
std::vector<Enemy3*> m_goblins;

void PlayState2::update() {

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}
	
	for (int i = 0; i < m_eyes.size(); ++i) {
		m_eyes[i]->update();
	}
	for (int i = 0; i < m_eyes.size(); ++i) {
		m_eyes[i]->move(player);
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->update();
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->move(player);
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->update();
	}
	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i] ->move(player);
	}
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->update();
	}
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->move(player);
	}
	mush->update();
	mush->move(player);


	player->update();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}
	if (player->healthBar <= 0)
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

	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->draw();
	}

	for (int i = 0; i < m_skeletons.size(); ++i) {
		m_skeletons[i]->draw();
	}
	
	for (int i = 0; i < m_goblins.size(); ++i) {
		m_goblins[i]->draw();
	}
	player->draw();
	enemy->draw();
	mush->draw();
	
}

bool PlayState2::onEnter() {
	
	//clear old
	m_eyes.clear();
	m_skeletons.clear();
	m_goblins.clear();
	m_towers.clear();
	m_gameObjects.clear();

	//Music
	SoundManager::Instance()->load("assets/playState2.wav", "assets/playState2.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/playState2.wav", 0);


	//TextureManager::Instance()->load("assets/inGamePauseButton.png", Game::Instance()->getRenderer());
	if (!TextureManager::Instance()->load("assets/player.png", Game::Instance()->getRenderer()))
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
	player = new Player(new LoaderParams(200, 200, 64, 64, "assets/player.png"));
	enemy = new Enemy(new LoaderParams(1000, 400, 150, 150, "assets/enemy1Run.png"));
	Enemy2* skeleton = new Enemy2(new LoaderParams(100, 400, 150, 150, "assets/enemy2Run.png"));
	Enemy3* goblin = new Enemy3(new LoaderParams(1000, 200, 150, 150, "assets/enemy3Run.png"));
	m_eyes.push_back(enemy);
	m_skeletons.push_back(skeleton);
	m_goblins.push_back(goblin);
	//GameObject* button1 = new MenuButton(new LoaderParams(1150, 10, 45, 36, "assets/inGamePauseButton.png"), s_pauseState);
	//m_gameObjects.push_back(enemy);
	//m_gameObjects.push_back(player);
	
	
	//m_gameObjects.push_back(button1);
	player->getLevel1(0);
	player->getLevel2(1);

	//player->collisionPos = lvl1->getCollisionPos();
	mush = new mushroom(new LoaderParams(200, 200, 150, 150, "assets/Idle.png"));
	mush->Setlv2(1);
	tower* newTower = new tower(new LoaderParams(330, 400, 100, 140, "assets/tower.png"));
	m_towers.push_back(newTower);
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState2::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->clean();
	}
	m_gameObjects.clear();
	player->clean();
	m_towers.clear();
	m_skeletons.clear();
	m_goblins.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/player.png");
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