#include "Camera.h"

#include "Game.h"

Camera* Camera::m_Instance = nullptr;


void Camera::Update(int player_x, int player_y)
{
    m_ViewBox.x = player_x + 80 / 2 - SCREEN_WIDTH / 2;
    m_ViewBox.y = player_y + 80 / 2 - SCREEN_HEIGHT / 2;

    if (m_ViewBox.x < 0)
    {
        m_ViewBox.x = 0;
    }

    if (m_ViewBox.y < 0)
    {
        m_ViewBox.y = 0;
    }

    if (m_ViewBox.x > (1440 - m_ViewBox.w))
    {
        m_ViewBox.x = (1440 - m_ViewBox.w);
    }

    if (m_ViewBox.y > (1280 - m_ViewBox.h))
    {
        m_ViewBox.y = (1280 - m_ViewBox.h);
    }

    m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
}
