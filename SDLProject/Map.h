#pragma once
#include "TextureManager.h"
struct Tile_map
{
	Tile_map(int x_des, int y_des,int type) {
	    mBox.x = x_des;
		mBox.y = y_des;
		mBox.w = 32;
		mBox.h = 32;
		mtype = type;
	}
	
	SDL_Rect getRect() {
		return mBox;
	}
	int getType() {
		return mtype;
	}
private:
	int mtype;
	SDL_Rect mBox;
};
class Map
{
public:
	void LoadMap();
	void drawMapLayer1();
	void drawMapLayer2();
	void drawMapLayer3();
	
	//bool check_wall(SDL_Rect Rect);
	static Map* getInstance() {
		if (m_Instance == nullptr) {
			m_Instance = new Map();
		}
		return m_Instance;
	}
	bool checkwall(SDL_Rect a, SDL_Rect b);
	bool iswall(SDL_Rect player);
	
private:
	static Map* m_Instance;
	Tile_map * Map_in[25][40];
	
};