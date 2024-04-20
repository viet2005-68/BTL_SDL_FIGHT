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

void difficultyState::update2()
{

}
void difficultyState::update3()
{

}

void difficultyState::render() {
	TextureManager::Instance()->drawOG("assets/background3.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
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
	TextureManager::Instance()->clearFromTextureMap("assets/background3.png");

	Mix_HaltMusic();

	std::cout << "exiting difficultyState...\n";
	return true;
}

void difficultyState::s_easy()
{
	Game::Instance()->getStateMachine()->changeState(new CharacterState());
}

void difficultyState::s_hard()
{
	Game::Instance()->getStateMachine()->changeState(new CharacterStateHard());
}

