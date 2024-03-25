#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "TextureManager.h"



struct Tile {
public:
    Tile() {}
    Tile(int x, int y, int type) {
        mBox.x = x;
        mBox.y = y;
        mBox.w = 32;
        mBox.h = 32;
        mtype = type;
    }

    void Text(SDL_Texture* tex) {
        TileTex = tex;
    }

    void draw() {
        TextureManager::Instance()->drawMap(TileTex, mBox);
    }
    SDL_Rect getRect() {
        return mBox;
    }
    int type() {
        return mtype;
    }
private:

    SDL_Rect mBox;
    SDL_Texture* TileTex;
    int mtype;
};
class Map
{
public:
    Map();
    ~Map();
    void CleanMap();
    void LoadMap(int arr[40][45]);
    void DrawMap();
    static Map* getInstance() {
        if (m_Instance == nullptr) { m_Instance = new Map(); }
        return m_Instance;
    }
    //bool checkwall(SDL_Rect player_box, sdl_rect)
    bool iswall(SDL_Rect player);

    bool checkwall(SDL_Rect a, SDL_Rect b);


private:
    SDL_Rect Map_Src, MAP_des;
    static Map* m_Instance;
    SDL_Texture* Box;
    SDL_Texture* Grass;
    SDL_Texture* Water;
    SDL_Texture* Wall;
    int row;
    int col;
    Tile* Map_in[60][60];
};

#endif // MAP_H
