#include "GameOverState.h"

const const char* GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	noButton->update();
}

void GameOverState::update1()
{
	yesButton->update();
}

void GameOverState::update2()
{

}

void GameOverState::update3()
{

}

void GameOverState::render() {
	TextureManager::Instance()->draw("assets/background2.png", Game::Instance()->getRenderer(), 0, 0, 640, 400);
	TextureManager::Instance()->draw("assets/GameOver.png", Game::Instance()->getRenderer(), 140, 200, 500, 88);
	yesButton->draw();
	noButton->draw();
	yourScore = new WriteOnScreen("assets/font.ttf", 36);
	std::string str = "YOUR SCORE: " + std::to_string(Game::Instance()->m_score->getScore());
	yourScore->displayText(str, 400, 600, 400, 80);
}

void GameOverState::s_gameQuit()
{
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	Game::Instance()->getStateMachine()->changeState(new MenuState());
	//Game::Instance()->Quit();
}

void GameOverState::s_restartPlay()
{
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
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
	if (!TextureManager::Instance()->load("assets/background2.png", Game::Instance()->getRenderer()))
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
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	
	std::cout << "entering GameOverState...\n";
	return true;
}

bool GameOverState::onExit() {
	TextureManager::Instance()->clearFromTextureMap("assets/yesButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/noButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/GameOver.png");
	std::cout << "exiting GameOverState...\n";
	return true;
}
