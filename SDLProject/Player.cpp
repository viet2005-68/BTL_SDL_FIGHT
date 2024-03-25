#include "Player.h"
#include "InputHandler.h"
#include <cstdlib>
#include "Game.h"
#include "Camera.h"
#include "Map.h"


Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	TextureManager::Instance()->load("assets/Arrow.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/dust.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealthUnder.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/playerHealth.png", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/heart.png", Game::Instance()->getRenderer());
	playerRect.w = 75;
	playerRect.h = 91;
	VecX = 0;
	VecY = 0;
}

void Player::draw()
{
	SDLGameObject::draw();
	TextureManager::Instance()->draw("assets/playerHealthUnder.png", Game::Instance()->getRenderer(), 65, 20, 100, 27);
	TextureManager::Instance()->draw("assets/playerHealth.png", Game::Instance()->getRenderer(), 65, 20, healthBar, 27);
	TextureManager::Instance()->draw("assets/heart.png", Game::Instance()->getRenderer(), 4, 20, 28, 28);

	TextureManager::Instance()->drawChar("assets/Arrow.png", Game::Instance()->getRenderer(), playerRect.x + 30, playerRect.y - 20, 13, 13, 1, 0, 0);
	if (run == 1 && m_velocity.getX() > 0) {
		TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x - 5, playerRect.y + 60, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 0);
	}
	else if (run == 1 && m_velocity.getX() < 0) {
		TextureManager::Instance()->drawFrame("assets/dust.png", Game::Instance()->getRenderer(), playerRect.x + 55, playerRect.y + 60, 16, 12, 1, ((SDL_GetTicks() / 200) % 3), 1);
	}
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(playerRect));
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Player::update()
{
	VecX = 0;
	VecY = 0;

	//playerRect.x = m_position.getX() + 100;
	//playerRect.y = m_position.getY();

	int tick = 50;
	frame = 11;
	m_currentRow = 4;
	run = 0;
	attack = 0;

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) == true && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_x -= 5;
		//chieu am
		m_velocity.setX(-0.001);
		VecX -= 5;
		m_currentRow = 5;
		frame = 8;
		run = 1;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_y -= 5;
		VecY -= 5;
		m_currentRow = 5;
		frame = 8;
		run = 1;
		//move();

	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_y += 5;
		m_currentRow = 5;
		VecY += 5;
		frame = 8;
		run = 1;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J) == false) {
		m_position.m_x += 5;
		//chieu duong
		VecX += 5;
		m_velocity.setX(0.001);
		m_currentRow = 5;
		frame = 8;
		run = 1;
		//move();

	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_J)) {
		m_currentRow = 1;
		frame = 7;
		attack = 1;
		//move();
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_K)) {
		m_currentRow = 2;
		frame = 7;
		tick = 300;
		//move();
	}

	if (attacked == 1) {
		m_currentRow = 6;
		frame = 4;
		tick = 300;
	}
	move();
	m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

	//Sound
	if (run == 1) {
		attacked = 0;
		SoundManager::Instance()->playSound("assets/walk.wav", 0);
	}
	else if (attack == 1) {
		attacked = 0;
		SoundManager::Instance()->playSound("assets/enemy1Damaged.wav", 0);
	}
	else if (attacked == 1) {
		SoundManager::Instance()->playSound("assets/damaged.wav", 0);
	}
	else {
		Mix_HaltChannel(-1);
	}

	SDLGameObject::update();
}
void Player::move() {
	Vector2D cam = Camera::GetInstance()->GetPosition();
	playerRect.x = m_position.m_x + 110;
	playerRect.y = m_position.m_y + 91;
	if (playerRect.x < 0 || (playerRect.x > 1440) || Map::getInstance()->iswall(playerRect)) {
		
		m_position.m_x -= VecX;
		std::cout << "ttttttt" << std::endl;
	}
	
	if (playerRect.y < 0 || (playerRect.y > 1440) || Map::getInstance()->iswall(playerRect)) {
	
		m_position.m_y -= VecY;
		std::cout << "ttttttt" << std::endl;
	}
}
void Player::clean()
{
}