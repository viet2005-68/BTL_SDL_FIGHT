#pragma once
#include "TextureManager.h"

class Map
{
public:
	void LoadMap();
	void drawMapLayer1();
	void drawMapLayer2();
	void drawMapLayer3();
	int** getCollisionPos();
	int collision[25][40];
};