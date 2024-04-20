#include "CharacterStateHard.h"

const const char* CharacterStateHard::s_characterHardID = "CHARACTERHARD";

void CharacterStateHard::update()
{
	player1->update();
}

void CharacterStateHard::update1()
{
	player2->update();
}

void CharacterStateHard::update2()
{
	player3->update();
}

void CharacterStateHard::update3()
{
	player4->update();
}


void CharacterStateHard::render()
{
	TextureManager::Instance()->drawOG("assets/characterBackground.png", Game::Instance()->getRenderer(), 0, 0, 1280, 800);
	TextureManager::Instance()->drawOG("assets/chooseYourCharacter.png", Game::Instance()->getRenderer(), 320, 50, 651, 31);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 90, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 190, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 290, 190, 48, 48);
	TextureManager::Instance()->draw("assets/playerBorder.png", Game::Instance()->getRenderer(), 390, 190, 48, 48);
	player1->draw();
	player2->draw();
	player3->draw();
	player4->draw();
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
	std::cout << "Choose your character...\n";
	return true;
}

bool CharacterStateHard::onExit()
{
	Game::Instance()->playTime.reset();
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