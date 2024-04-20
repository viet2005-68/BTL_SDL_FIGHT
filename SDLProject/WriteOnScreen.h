#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class WriteOnScreen {
public:
    WriteOnScreen(const std::string& fontPath, int fontSize);
    ~WriteOnScreen();

    void displayText(const std::string& message, int x, int y, int w, int h);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color color;
};