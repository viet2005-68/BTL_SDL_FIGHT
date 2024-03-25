#include "GameOverState.h"

const const char* GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update();
	}

	yesButton->update();

}

void GameOverState::render() {
	TextureManager::Instance()->draw("assets/GameOver.png", Game::Instance()->getRenderer(), 140, 200, 500, 88);

	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}

	yesButton->draw();
}

void GameOverState::s_gameQuit()
{
	//Game::Instance()->getStateMachine()->changeState(new MenuState());
	Game::Instance()->Quit();
}

void GameOverState::s_restartPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
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
	GameObject* noButton = new MenuButton(new LoaderParams(660, 400, 45, 36, "assets/exitHelpButton.png"), s_gameQuit);
	//GameObject* yesButton = new MenuButton(new LoaderParams(510, 400, 45, 36, "assets/yesButton.png"), s_restartPlay);
	m_gameObjects.push_back(noButton);
	//m_gameObjects.push_back(yesButton);
	std::cout << "entering GameOverState...\n";
	return true;
}

bool GameOverState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/exitHelpButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/yesButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/GameOver.png");
	std::cout << "exiting GameOverState...\n";
	return true;
}
