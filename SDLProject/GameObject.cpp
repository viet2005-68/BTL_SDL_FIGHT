/*#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int x, int y, int width, int height, const char* textureID, SDL_Renderer* ren) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;
	m_currentFrame = 1;
	TextureManager::Instance()->load(textureID, ren);
}

void GameObject::draw(SDL_Renderer* ren, int flip) {
	TextureManager::Instance()->drawFrame(m_textureID, ren, m_x, m_y, m_width, m_height, m_currentRow,  m_currentFrame, flip);
}

void GameObject::update() {
	//m_x += 1;
	m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
}
*/