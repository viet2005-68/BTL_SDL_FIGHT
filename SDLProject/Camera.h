#pragma once

#include "Point.h"
#include "Vector2D.h"
#include "SDL.h"
#include "Game.h"



class Camera
{
public:
    ~Camera() {}
    void Update(int player_x, int player_y);
    inline static Camera* GetInstance() {
        if (m_Instance == nullptr) m_Instance = new Camera();
        return m_Instance;
    }

    inline SDL_Rect GetViewBox() {
        return m_ViewBox;
    }
    inline Vector2D GetPosition() {
        return m_Position;
    }
    inline void SetTarget(Point* target) {
        m_Target = target;
    }
    // void Updatefloat() {};
    Camera() {
        m_ViewBox = { 0,0,1200,800 };
    }
private:

    //Camera(){}
    
    Point* m_Target;
    Vector2D m_Position;

    SDL_Rect m_ViewBox;

    static Camera* m_Instance;

};
