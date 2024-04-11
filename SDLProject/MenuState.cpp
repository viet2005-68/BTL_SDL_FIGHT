#include "MenuState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"

const const char* MenuState::s_menuID = "MENU";



void MenuState::update()
{

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}

	button1->update();
}

void MenuState::update1()
{
	button3->update();
}



void MenuState::render() {
	TextureManager::Instance()->draw("assets/background.png", Game::Instance()->getRenderer(), 0, 0, 640, 400);

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}

	button1->draw();
	button3->draw();

}

bool MenuState::onEnter() {

	//Button sound
	SoundManager::Instance()->load("assets/Confirm.wav", "confirm", SOUND_SFX);

	//Background music
	SoundManager::Instance()->load("assets/menuTheme.wav", "assets/menuTheme.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/menuTheme.wav", 0);

	//Button
	TextureManager::Instance()->load("assets/background.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/Mute.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/Unmute.png", Game::Instance()->getRenderer());
	if (!TextureManager::Instance()->load("assets/playButton.png", Game::Instance()->getRenderer())) {
		return false;
	}

	if (!TextureManager::Instance()->load("assets/exitButton.png", Game::Instance()->getRenderer())) {
		return false;
	}
	//GameObject* button1 = new MenuButton(new LoaderParams(100, 400, 115, 53, "assets/playButton.png"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 640, 115, 53, "assets/exitButton.png"), s_exitFromMenu);

	//GameObject* button3 = new MenuButton(new LoaderParams(100, 520, 115, 53, "assets/helpButton.png"), s_help);

	GameObject* button4 = new MenuButton(new LoaderParams(1200, 10, 36, 36, "assets/Mute.png"), s_volumeMute);
	GameObject* button5 = new MenuButton(new LoaderParams(1100, 10, 36, 36, "assets/Unmute.png"), s_volumeUnmute);
	//m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	//m_gameObjects.push_back(button3);
	m_gameObjects.push_back(button4);
	m_gameObjects.push_back(button5);

	std::cout << "Entering MenuState...\n";
	return true;
}

bool MenuState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/playButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/exitButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/background.png");
	TextureManager::Instance()->clearFromTextureMap("assets/Mute.png");
	TextureManager::Instance()->clearFromTextureMap("assets/Unmute.png");

	//Mix_HaltMusic();

	std::cout << "exiting MenuState...\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState(new difficultyState());
}

void MenuState::s_help()
{
	Game::Instance()->getStateMachine()->changeState(new HelpState());
}
void MenuState::s_exitFromMenu()
{
	Game::Instance()->Quit();
}

void MenuState::s_volumeMute()
{
	std::cout << "Mute" << endl;
	Mix_VolumeMusic(0);
	Mix_Volume(-1, 0);
}

void MenuState::s_volumeUnmute()
{
	std::cout << "Unmute" << endl;
	Mix_VolumeMusic(100);
	Mix_Volume(-1, 100);
}
