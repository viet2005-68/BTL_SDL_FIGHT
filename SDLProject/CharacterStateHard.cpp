#include "CharacterStateHard.h"

const const char* CharacterStateHard::s_characterHardID = "CHARACTERHARD";

void CharacterStateHard::update()
{
	//player1->update();
	if (m_char.size() != 0) {
		for (int i = 0; i < m_char.size(); ++i) {
			if (m_char[i] != NULL) {
				m_char[i]->update();
			}
		}
	}
}

void CharacterStateHard::update1()
{
	//player2->update();
}

void CharacterStateHard::render()
{
	TextureManager::Instance()->drawOG("assets/characterBackground.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
	TextureManager::Instance()->drawOG("assets/chooseYourCharacter.png", Game::Instance()->getRenderer(), 320, 50, 651, 31);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 90, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 190, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 290, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 390, 190, 48, 48);
	//player1->draw();
	//player2->draw();
	for (int i = 0; i < m_char.size(); ++i) {
		m_char[i]->draw();
	}
}

bool CharacterStateHard::onEnter()
{
	SoundManager::Instance()->load("assets/characterState.wav", "assets/characterState.wav", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("assets/characterState.wav", 0);
	if (!TextureManager::Instance()->load("assets/playerBorder.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player1.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player2.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player3.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/player4.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/chooseYourCharacter.png", Game::Instance()->getRenderer())) {
		return false;
	}
	if (!TextureManager::Instance()->load("assets/characterBackground.png", Game::Instance()->getRenderer())) {
		return false;
	}
	GameObject* player1 = new MenuButton(new LoaderParams(100, 200, 38, 38, "assets/player1.png"), s_player1);
	GameObject* player2 = new MenuButton(new LoaderParams(200, 200, 38, 38, "assets/player2.png"), s_player2);
	GameObject* player3 = new MenuButton(new LoaderParams(300, 200, 38, 38, "assets/player3.png"), s_player3);
	GameObject* player4 = new MenuButton(new LoaderParams(400, 200, 38, 38, "assets/player4.png"), s_player4);
	m_char.push_back(player1);
	m_char.push_back(player2);
	m_char.push_back(player3);
	m_char.push_back(player4);
	std::cout << "Choose your character...\n";
	return true;
}

bool CharacterStateHard::onExit()
{
	TextureManager::Instance()->clearFromTextureMap("assets/player1.png");
	TextureManager::Instance()->clearFromTextureMap("assets/player2.png");
	TextureManager::Instance()->clearFromTextureMap("assets/player3.png");
	TextureManager::Instance()->clearFromTextureMap("assets/player4.png");
	TextureManager::Instance()->clearFromTextureMap("assets/playerBorder.png");
	TextureManager::Instance()->clearFromTextureMap("assets/chooseYourCharacter.png");
	TextureManager::Instance()->clearFromTextureMap("assets/characterBackground.png");
	Mix_HaltMusic();
	std::cout << "Exiting CharacterState...\n";
	return true;
}

void CharacterStateHard::s_player1()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState(2, 1));
}

void CharacterStateHard::s_player2()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState(2, 2));
}

void CharacterStateHard::s_player3()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState(2, 3));
}
void CharacterStateHard::s_player4()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState(2, 4));
}