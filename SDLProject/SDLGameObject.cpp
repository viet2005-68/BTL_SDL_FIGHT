#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "LoaderParams.h"


SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	TextureManager::Instance()->load(m_textureID, Game::Instance()->getRenderer());
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() < 0) {
		TextureManager::Instance()->drawChar(m_textureID, Game::Instance()->getRenderer(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, 1);
	}
	else {
		TextureManager::Instance()->drawChar(m_textureID, Game::Instance()->getRenderer(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, 0);
	}
}




void SDLGameObject::drawButton() {
	TextureManager::Instance()->drawFrame(m_textureID, Game::Instance()->getRenderer(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, 0);
}

void SDLGameObject::update() {
	m_position += m_velocity;
	
}

void SDLGameObject::clean() {
	
}

void SDLGameObject::drawBig()
{
	if (m_velocity.getX() < 0) {
		TextureManager::Instance()->drawFrame(m_textureID, Game::Instance()->getRenderer(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, 1);
	}
	else {
		TextureManager::Instance()->drawFrame(m_textureID, Game::Instance()->getRenderer(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, 0);
	}
}
