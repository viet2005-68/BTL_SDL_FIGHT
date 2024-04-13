#include "Game.h"
#include "SDL_ttf.h"
#include "scorePlayer.h"
Game* Game::g_instance = 0;



void Game::init(const char* title, int w, int h, bool fullscreen) {
	TTF_Init();
	int flag = 0;
	if (fullscreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	(SDL_Init(SDL_INIT_EVERYTHING));
	cout << "Game initialized..." << endl;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flag);
	cout << "Window created..." << endl;
	renderer = SDL_CreateRenderer(window, -1, 0);
	cout << "Renderer created..." << endl;
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	
	m_score = new ScorePlayer();

	TextureManager::Instance()->load("assets/background.png", Game::Instance()->getRenderer());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	m_pGameStateMachine->render();

	SDL_RenderPresent(renderer);
}

void Game::handleEvent() {
	
	InputHandler::Instance()->handleEvent();

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::update() {
	

	m_pGameStateMachine->update();

	
}

void Game::Quit() {
	isRunning = false;
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete m_pGameStateMachine;
	m_gameObjects.clear();
	SDL_Quit();
	cout << "Game cleaned..." << endl;
}

