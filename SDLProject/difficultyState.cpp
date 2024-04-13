#include "difficultyState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"

const const char* difficultyState::s_difficultyID = "DIFFICULTY";


void difficultyState::update()
{
	button2->update();
}
void difficultyState::update1()
{
	button1->update();
}



void difficultyState::render() {
	TextureManager::Instance()->draw("assets/background3.png", Game::Instance()->getRenderer(), 0, 0, 640, 400);
	button2->draw();
	button1->draw();
}

bool difficultyState::onEnter() {
	//SoundManager::Instance()->playMusic("assets/menuTheme.wav", 0);

	//Button
	TextureManager::Instance()->load("assets/background3.png", Game::Instance()->getRenderer());

	if (!TextureManager::Instance()->load("assets/easyButton.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/hardButton.png", Game::Instance()->getRenderer())) {
		return false;
	}

	std::cout << "Entering difficultyState...\n";
	return true;
}

bool difficultyState::onExit() {
	TextureManager::Instance()->clearFromTextureMap("assets/easyButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/hardButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/background.png");

	Mix_HaltMusic();

	std::cout << "exiting difficultyState...\n";
	return true;
}

void difficultyState::s_easy()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState2());
}

void difficultyState::s_hard()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState(2));
}

