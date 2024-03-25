#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>

using namespace std;


class TextureManager {
public:
	//TextureManager() {};
	~TextureManager();
	
	bool load(const char* fileName, SDL_Renderer *ren);

	bool loadMap(std::string id, std::string filename);

	void draw(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h);
	void drawFrame(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h, int currentRow, int currentFrame, int flag);
	void drawChar(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h, int currentRow, int currentFrame, int flag);
	void drawMap(SDL_Texture* tex, SDL_Rect des);
	SDL_Texture* loadMap(const char* fileName, SDL_Renderer* ren);
	void clearFromTextureMap(const char* fileName);

	static TextureManager* Instance()
	{
		if (instance == 0)
		{
			instance = new TextureManager();
		}
		return instance;
	}
	


private:
	static TextureManager* instance;
	map<string, SDL_Texture*> textureMap;
};

