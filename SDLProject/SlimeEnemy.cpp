#include "SlimeEnemy.h"
#include <iostream>
#include "Vector2D.h"


SlimeEnemy::SlimeEnemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    enemyRect.w = 30;
    enemyRect.h = 40;
    enemyRect.x = m_position.m_x;
    enemyRect.y = m_position.m_y;
    VecX = 1;
    //VecX = 1;
    //find_road = new AStar();
    //VecY = 0;
}

void SlimeEnemy::draw() {
    
    TextureManager::Instance()->drawChar("assets/healthUnder.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y, barWidth, barHeight, 1, 0, 0);
    TextureManager::Instance()->drawChar("assets/health.png", Game::Instance()->getRenderer(), enemyRect.x, enemyRect.y, healthBar, 8, 1, 0, 0);
    SDLGameObject::draw();
    SDL_RenderDrawRect(Game::Instance()->getRenderer(), &(enemyRect));
    SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 255, 255, 255);
}

void SlimeEnemy::update() {
  
    m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

    SDLGameObject::update();
    
   enemyRect.x = m_position.m_x + 20;
   enemyRect.y = m_position.m_y ;
}

void SlimeEnemy::clean() {}

void SlimeEnemy::move(Player*& player) {
    // ... (existing code for enemy death handling)
    //VecX = 0;
    
    
       // m_position.m_x += 1;
   
    
}
