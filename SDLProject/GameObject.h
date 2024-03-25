#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "LoaderParams.h"

/*using namespace std;

class GameObject {
public:
	virtual void load(int x, int y, int width, int height, const char* textureID, SDL_Renderer* ren);
	virtual void draw(SDL_Renderer* pRenderer, int flip);
	virtual void update();
	//virtual void clean();
protected:
	const char* m_textureID;
	int m_currentRow = 1;
	int m_currentFrame;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};*/

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject(const LoaderParams* pParams) {}
	//virtual ~GameObject() {}
};