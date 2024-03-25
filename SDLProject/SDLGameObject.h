#pragma once
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void drawButton();
	virtual void update();
	virtual void clean();

	Vector2D& getPostiton() {
		return m_position;
	}

	Vector2D& getVelocity() {
		return m_velocity;
	}
	Vector2D m_position;

protected:
	
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	const char* m_textureID;
	Vector2D m_velocity;

};