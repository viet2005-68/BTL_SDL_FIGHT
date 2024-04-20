#include "VictoryState.h"

const const char* VictoryState::s_VictoryID = "VICTORY";

void VictoryState::update()
{
	noButton->update();
}

void VictoryState::update1()
{
	yesButton->update();
}

void VictoryState::update2()
{

}

void VictoryState::update3()
{

}

void VictoryState::render() {
	TextureManager::Instance()->drawOG("assets/Victory.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
	TextureManager::Instance()->draw("assets/GameOver.png", Game::Instance()->getRenderer(), 140, 200, 500, 88);
	yesButton->draw();
	noButton->draw();
	yourScore = new WriteOnScreen("assets/font.ttf", 36);
	std::string str = "YOUR SCORE: " + std::to_string(Game::Instance()->m_score->getScore());
	yourScore->displayText(str, 400, 600, 400, 80);
}

void VictoryState::s_gameQuit()
{
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	Game::Instance()->getStateMachine()->changeState(new MenuState());
	//Game::Instance()->Quit();
}

void VictoryState::s_restartPlay()
{
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	Game::Instance()->getStateMachine()->changeState(new difficultyState());
}

bool VictoryState::onEnter()
{

	if (!TextureManager::Instance()->load("assets/Victory.png", Game::Instance()->getRenderer()))
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

bool VictoryState::onExit() {
	TextureManager::Instance()->clearFromTextureMap("assets/yesButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/noButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/GameOver.png");
	std::cout << "exiting GameOverState...\n";
	return true;
}
