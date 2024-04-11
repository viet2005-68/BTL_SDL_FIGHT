#include "WriteOnScreen.h"
#include "Game.h"
WriteOnScreen::WriteOnScreen(const std::string& fontPath, int fontSize){

    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    color = { 255,255,255 };
}

WriteOnScreen::~WriteOnScreen() {
   
    TTF_CloseFont(font);
    TTF_Quit();
}

void WriteOnScreen::displayText(const std::string& message, int x, int y) {
  
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
   
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), surface);
    
    SDL_Rect messageRect = { x, y,200,50};
   
    SDL_RenderCopy(Game::Instance()->getRenderer(), texture, NULL, &messageRect);
  
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
