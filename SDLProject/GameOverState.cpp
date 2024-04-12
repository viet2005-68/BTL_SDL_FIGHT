#include "GameOverState.h"

const const char* GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	yesButton->update();

}

void GameOverState::update1() {
	noButton->update();
}

void GameOverState::render() {
	TextureManager::Instance()->draw("assets/GameOver.png", Game::Instance()->getRenderer(), 140, 200, 500, 88);
	yesButton->draw();
	noButton->draw();
}

void GameOverState::s_gameQuit()
{
	Game::Instance()->getStateMachine()->changeState(new MenuState());
	//Game::Instance()->Quit();
}

void GameOverState::s_restartPlay()
{
	Game::Instance()->getStateMachine()->changeState(new difficultyState());
}

bool GameOverState::onEnter()
{

	if (!SoundManager::Instance()->load("assets/GameOver.wav", "assets/GameOver.wav", SOUND_MUSIC)) {
		return false;
	}
	SoundManager::Instance()->playMusic("assets/GameOver.wav", 0);

	if (!TextureManager::Instance()->load("assets/GameOver.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/exitHelpButton.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("assets/yesButton.png", Game::Instance()->getRenderer()))
	{
		return false;
	}
	std::cout << "entering GameOverState...\n";
	return true;
}

bool GameOverState::onExit() {
	TextureManager::Instance()->clearFromTextureMap("assets/exitHelpButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/yesButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/GameOver.png");
	std::cout << "exiting GameOverState...\n";
	return true;
}
