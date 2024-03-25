#pragma once
#include <string>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, const char* textureID) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
	{
	}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	const char* getTextureID() const { return m_textureID; }
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	const char* m_textureID;
};
