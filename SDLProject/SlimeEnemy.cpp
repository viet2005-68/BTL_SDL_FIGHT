#include "SlimeEnemy.h"
#include <iostream>
#include "Map.h"
#include "Vector2D.h"

#include "Camera.h"

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
    Vector2D cam = Camera::GetInstance()->GetPosition();

    m_currentFrame = int(((SDL_GetTicks() / tick) % frame));

    SDLGameObject::update();
    
    enemyRect.x = m_position.m_x - cam.m_x + 20;
    enemyRect.y = m_position.m_y - cam.m_y;
}

void SlimeEnemy::clean() {}

void SlimeEnemy::move(Player*& player) {
    // ... (existing code for enemy death handling)
    //VecX = 0;
    
    
       // m_position.m_x += 1;
    int distance = sqrt(pow(m_position.m_x - player->m_position.m_x, 2) - pow(m_position.m_y - player->m_position.m_y, 2));
    std::pair<int, int> next_tile = Map::getInstance()->FindOptimalPath(enemyRect, player->playerRect);

    if (next_tile.first != 0 && next_tile.second != 0 && distance >= 50) {
        Vector2D cam = Camera::GetInstance()->GetPosition();

        // Nếu tìm thấy đường đi, tính toán vector vận tốc để di chuyển enemy đến ô tiếp theo
        int dx = next_tile.first * 32 - m_position.m_x;
        int dy = next_tile.second * 32 - m_position.m_y;

        // Chuẩn hóa vector vận tốc và nhân với tốc độ di chuyển mong muốn
        float length = sqrt(dx * dx + dy * dy);
        float velocity_x = 1 * dx / length;
        float velocity_y = 1 * dy / length;

        // Cập nhật vị trí của enemy
        m_position.m_x += velocity_x;
        m_position.m_y += velocity_y;
        enemyRect.x = m_position.m_x + 32 - cam.m_x;
        enemyRect.y = m_position.m_y  - cam.m_y;
        if (Map::getInstance()->iswall(enemyRect)) {
            m_position.m_x -= velocity_x;
            m_position.m_y -= velocity_y;
        }
    }
    else {
        Vector2D cam = Camera::GetInstance()->GetPosition();
        m_position.m_x += 1;
        enemyRect.x = m_position.m_x + 32 - cam.m_x;
        enemyRect.y = m_position.m_y - cam.m_y;

    }
   /* else {
        SDL_Rect rect = { 0,0,32,32 };
        std::pair<int, int> next = Map::getInstance()->FindPath(enemyRect, rect);
        if (next.first != 0 && next.second != 0) {
            Vector2D cam = Camera::GetInstance()->GetPosition();

            // Nếu tìm thấy đường đi, tính toán vector vận tốc để di chuyển enemy đến ô tiếp theo
            int dx = next.first * 32 - m_position.m_x;
            int dy = next.second * 32 - m_position.m_y;

            // Chuẩn hóa vector vận tốc và nhân với tốc độ di chuyển mong muốn
            float length = sqrt(dx * dx + dy * dy);
            float velocity_x = 1 * dx / length;
            float velocity_y = 1 * dy / length;

            // Cập nhật vị trí của enemy
            m_position.m_x += velocity_x;
            m_position.m_y += velocity_y;
            enemyRect.x = m_position.m_x  - cam.m_x;
            enemyRect.y = m_position.m_y  - cam.m_y;
            if (Map::getInstance()->iswall(enemyRect)) {
                m_position.m_x -= velocity_x;
                m_position.m_y -= velocity_y;
            }
        }
    }*/

    
}
