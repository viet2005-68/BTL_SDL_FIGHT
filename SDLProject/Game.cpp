#include "Game.h"

Game* Game::g_instance = 0;


void Game::init(const char* title, int w, int h, bool fullscreen) {
	int flag = 0;
	TTF_Init();
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

	//TextureManager::Instance()->load("assets/playerRun.png", renderer);
	//m_go.load(0, 0, 250, 250, "assets/BossIdle.png", renderer);
	//m_player.load(300, 293, 79, 43, "assets/playerRun.png", renderer);
	
	//m_player = new Player();
	//m_enemy = new Enemy();
	//m_boss = new Enemy();

	//m_player->load(0, 0, 80, 80, "assets/player.png", renderer);

	//m_boss->load(0, 0, 250, 250, "assets/bossRun.png", renderer);
	//m_enemy->load(0, 0, 150, 150, "assets/enemy1Run.png", renderer);

	//m_gameObjects.push_back(m_player);
	//m_gameObjects.push_back(m_enemy);
	//m_gameObjects.push_back(m_boss);

	//m_gameObjects.push_back(new Player(new LoaderParams(0, 0, 80, 80, "assets/player.png")));
	//m_gameObjects.push_back(new Enemy(new LoaderParams(0, 0, 250, 250, "assets/bossRun.png")));
	//m_gameObjects.push_back(new Enemy(new LoaderParams(0, 0, 150, 150, "assets/enemy1Run.png")));

	TextureManager::Instance()->load("assets/background.png", Game::Instance()->getRenderer());

	m_score = new ScorePlayer();

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
}

void Game::render() {
	SDL_RenderClear(renderer);
	//TextureManager::Instance()->draw("assets/player.png", renderer, 0, 0, 80, 64);
	//TextureManager::Instance()->drawFrame("assets/playerRun.png", renderer, 100, 100, 80, 64, currentFrame);
	//m_go.draw(renderer);
	//m_player.draw(renderer);

	m_pGameStateMachine->render();

	//for (int i = 0; i < m_gameObjects.size(); ++i) {
		//m_gameObjects[i]->draw();
	//}

	//m_player->draw(renderer);

	SDL_RenderPresent(renderer);
}

void Game::handleEvent() {

	InputHandler::Instance()->handleEvent();

	//if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		//m_pGameStateMachine->changeState(new PlayState());
	//}
}

void Game::update() {
	//currentFrame = int(((SDL_GetTicks() / 100) % 8));
	//m_go.update();
	//m_player.update();

	m_pGameStateMachine->update();

	//for (int i = 0; i < m_gameObjects.size(); ++i) {
		//m_gameObjects[i]->update();
	//}
	//m_player->update();
}

void Game::Quit() {
	isRunning = false;
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned..." << endl;
}
