#include "HelpState.h"

const const char* HelpState::s_helpID = "HELP";

void HelpState::update()
{
	m_gameObjects[0]->update();
}

void HelpState::update1()
{

}

void HelpState::update2()
{

}

void HelpState::update3()
{

}

void HelpState::render()
{
	TextureManager::Instance()->drawOG("assets/helpBackground.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

bool HelpState::onEnter()
{
	if (!TextureManager::Instance()->load("assets/exitHelpButton.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/helpBackground.png", Game::Instance()->getRenderer())) {
		return false;
	}
	GameObject* exit = new MenuButton(new LoaderParams(1130, 25, 45, 37, "assets/exitHelpButton.png"), s_helpToMain);
	GameObject* note = new MenuButton(new LoaderParams(60, 0, 506, 398, "assets/note.png"), s_helpToMain);
	m_gameObjects.push_back(exit);
	m_gameObjects.push_back(note);
	std::cout << "entering HelpState\n";
	return true;
}

bool HelpState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("assets/exitHelpButton.png");
	TextureManager::Instance()->clearFromTextureMap("assets/note.png");
	TextureManager::Instance()->clearFromTextureMap("assets/helpBackground.png");
	std::cout << "Exiting HelpState...\n";
	return true;
}

void HelpState::s_helpToMain()
{
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}