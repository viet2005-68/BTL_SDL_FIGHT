#include "Game.h"

const int FPS = 90;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Uint32 frameStart, frameTime;
	Game::Instance()->init("LegendKnight.exe", 1280, 800, 0);
	while (Game::Instance()->running()) {
		frameStart = SDL_GetTicks();

		Game::Instance()->handleEvent();
		Game::Instance()->update();
		Game::Instance()->render();
		
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	Game::Instance()->clean();
	return 0;
}