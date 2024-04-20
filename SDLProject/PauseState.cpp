#include "PauseState.h"

const const char* PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	BestScore::GetInstance()->updateHighScore(Game::Instance()->m_score->getScore());
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
	Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	
}

void PauseState::update1()
{
}
void PauseState::update2()
{
}
void PauseState::update3()
{
}


void PauseState::render()
{
	TextureManager::Instance()->drawOG("assets/backgroundPause.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter() {
	Game::Instance()->playTime.pause();
	TextureManager::Instance()->load("assets/backgroundPause.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/continueButton.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/menuButton.png", Game::Instance()->getRenderer());
	GameObject* button1 = new MenuButton(new LoaderParams(540, 500, 115, 53, "assets/menuButton.png"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(540, 620, 115, 53, "assets/continueButton.png"), s_resumePlay);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/continueButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/menuButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/background2.png");

	InputHandler::Instance()->Reset();

	std::cout << "exiting PauseState\n";
	return true;
}