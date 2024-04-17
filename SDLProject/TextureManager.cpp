#include "TextureManager.h"
#include "Game.h"


TextureManager* TextureManager::instance = 0;

//TextureManager::~TextureManager() {

//}

/*void TextureManager::load(const char* fileName, SDL_Renderer* ren) {
	SDL_Surface* tmpSur = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSur);
	SDL_FreeSurface(tmpSur);
	textureMap[fileName] = tex;
}*/
SDL_Texture* TextureManager::loadMap(const char* fileName, SDL_Renderer* ren) {
	SDL_Surface* tmpSur = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSur);
	SDL_FreeSurface(tmpSur);
	return tex;
}

bool TextureManager::load(const char* fileName, SDL_Renderer* ren) {
	SDL_Surface* tmpSur = IMG_Load(fileName);
	if (tmpSur == 0) {
		return false;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSur);
	SDL_FreeSurface(tmpSur);
	if (tex != 0)
	{
		textureMap[fileName] = tex;
		return true;
	}
	return false;
}

void TextureManager::draw(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h) {
	SDL_Rect sourceR, desR;
	sourceR.x = 0;
	sourceR.y = 0;
	sourceR.h = h;
	sourceR.w = w;
	desR.x = x;
	desR.y = y;
	desR.h = h * 2;
	desR.w = w * 2;
	SDL_RenderCopy(ren, textureMap[fileName], &sourceR, &desR);
}

void TextureManager::drawFrame(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h, int currentRow, int currentFrame, int flip) {
	SDL_RendererFlip flag;
	if (flip == 1) {
		flag = SDL_FLIP_HORIZONTAL;
	}
	else {
		flag = SDL_FLIP_NONE;
	}
	SDL_Rect sourceR, desR;
	sourceR.x = w * currentFrame;
	sourceR.y = h * (currentRow-1);
	sourceR.h = h;
	sourceR.w = w;
	desR.x = x;
	desR.y = y;
	desR.h = h * 2;
	desR.w = w * 2;
	SDL_RenderCopyEx(ren, textureMap[fileName], &sourceR, &desR, 0, 0, flag);
}

void TextureManager::drawChar(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h, int currentRow, int currentFrame, int flip) {
	SDL_RendererFlip flag;
	if (flip == 1) {
		flag = SDL_FLIP_HORIZONTAL;
	}
	else {
		flag = SDL_FLIP_NONE;
	}
	SDL_Rect sourceR, desR;

	

	sourceR.x = w * currentFrame;
	sourceR.y = h * (currentRow - 1);
	sourceR.h = h;
	sourceR.w = w;
	desR.x = x;
	desR.y = y;
	desR.h = h*3/2;
	desR.w = w*3/2;
	SDL_RenderCopyEx(ren, textureMap[fileName], &sourceR, &desR, 0, 0, flag);
}


void TextureManager::clearFromTextureMap(const char* fileName)
{  
	textureMap.erase(fileName);
}

void TextureManager::drawMap(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h) {
	SDL_Rect sourceR, desR;
	sourceR.x = 32 * x;
	sourceR.y = 32 * y;
	sourceR.h = 32;
	sourceR.w = 32;
	desR.x = w;
	desR.y = h;
	desR.h = 32;
	desR.w = 32;
	SDL_RenderCopy(ren, textureMap[fileName], &sourceR, &desR);
}
void TextureManager::drawMap_Update(SDL_Texture* tex, SDL_Rect src, SDL_Rect des) {
	SDL_RenderCopy(Game::Instance()->getRenderer(), tex, &src, &des);
}
void TextureManager::drawOG(const char* fileName, SDL_Renderer* ren, int x, int y, int w, int h) {
	SDL_Rect sourceR, desR;
	sourceR.x = 0;
	sourceR.y = 0;
	sourceR.h = h;
	sourceR.w = w;
	desR.x = x;
	desR.y = y;
	desR.h = h;
	desR.w = w;
	SDL_RenderCopy(ren, textureMap[fileName], &sourceR, &desR);
}