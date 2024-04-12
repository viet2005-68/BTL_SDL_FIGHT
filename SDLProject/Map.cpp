#include "Map.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"

int layer1[25][40] = { 2,2,3,4,5,2,3,4,5,2,3,4,5,2,3,4,5,2,3,4,5,2,3,4,5,2,3,4,5,2,3,2,3,4,5,2,3,4,5,5,
8,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,8,9,10,11,11,
14,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,14,15,16,17,17,
20,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,20,21,22,23,23,
26,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,26,27,28,29,29,
8,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,8,9,10,11,11,
14,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,8,9,10,11,16,17,17,
20,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,14,15,16,17,22,23,23,
26,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,20,21,22,23,28,29,29,
8,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,26,27,8,9,10,11,11,
14,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,14,15,16,17,17,
20,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,20,21,22,23,23,
26,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,26,27,28,29,29,
8,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,8,9,10,11,11,
14,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,14,15,16,17,17,
20,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,20,21,22,23,23,
26,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,26,27,28,29,29,
8,8,9,10,11,8,9,10,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,8,9,10,11,11,
14,14,15,16,17,14,15,16,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,14,15,16,17,17,
20,20,21,22,23,20,21,22,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,20,21,22,23,23,
26,8,9,10,11,8,9,10,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,8,9,10,11,29,
26,14,15,16,17,14,15,16,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,17,14,15,16,14,15,16,17,17,
20,20,21,22,23,20,21,22,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,23,20,21,22,20,21,22,23,23,
26,26,27,28,29,26,27,28,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,29,26,27,28,26,27,28,29,29,
32,32,33,34,35,34,35,32,33,34,35,32,33,34,35,32,33,34,35,32,33,34,35,32,33,34,35,32,33,34,35,32,33,34,35,32,33,34,35,35 };

SDL_Rect srcR, desR;
void Map::LoadMap() {
	TextureManager::Instance()->load("assets/decoSet.png", Game::Instance()->getRenderer());
	if (TextureManager::Instance()->load("assets/groundSet.png", Game::Instance()->getRenderer()) && TextureManager::Instance()->load("assets/rockSet.png", Game::Instance()->getRenderer())) {
		std::cout << "get tile success...\n";
	}
	else {
		std::cout << "failed to get tile...\n";
	}
}

void Map::drawMapLayer1() {

	int type = 0;
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 40; ++j) {
			type = layer1[i][j];
			desR.x = j * 32;
			desR.y = i * 32;
			switch (type) {
			case 1:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 0, desR.x, desR.y);
				break;

			case 2:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 0, desR.x, desR.y);
				break;

			case 3:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 0, desR.x, desR.y);
				break;

			case 4:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 0, desR.x, desR.y);
				break;

			case 5:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 0, desR.x, desR.y);
				break;

			case 6:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 0, desR.x, desR.y);
				break;

			case 7:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 1, desR.x, desR.y);
				break;

			case 8:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 1, desR.x, desR.y);
				break;

			case 9:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 1, desR.x, desR.y);
				break;

			case 10:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 1, desR.x, desR.y);
				break;

			case 11:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 1, desR.x, desR.y);
				break;

			case 12:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 1, desR.x, desR.y);
				break;

			case 13:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 2, desR.x, desR.y);
				break;

			case 14:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 2, desR.x, desR.y);
				break;

			case 15:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 2, desR.x, desR.y);
				break;

			case 16:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 2, desR.x, desR.y);
				break;

			case 17:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 2, desR.x, desR.y);
				break;

			case 18:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 2, desR.x, desR.y);
				break;

			case 19:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 3, desR.x, desR.y);
				break;

			case 20:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 3, desR.x, desR.y);
				break;

			case 21:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 3, desR.x, desR.y);
				break;

			case 22:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 3, desR.x, desR.y);
				break;

			case 23:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 3, desR.x, desR.y);
				break;

			case 24:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 3, desR.x, desR.y);
				break;

			case 25:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 4, desR.x, desR.y);
				break;

			case 26:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 4, desR.x, desR.y);
				break;

			case 27:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 4, desR.x, desR.y);
				break;

			case 28:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 4, desR.x, desR.y);
				break;

			case 29:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 4, desR.x, desR.y);
				break;

			case 30:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 4, desR.x, desR.y);
				break;

			case 31:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 0, 5, desR.x, desR.y);
				break;

			case 32:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 1, 5, desR.x, desR.y);
				break;

			case 33:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 2, 5, desR.x, desR.y);
				break;

			case 34:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 3, 5, desR.x, desR.y);
				break;

			case 35:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 4, 5, desR.x, desR.y);
				break;
			case 36:
				TextureManager::Instance()->drawMap("assets/groundSet.png", Game::Instance()->getRenderer(), 5, 5, desR.x, desR.y);
				break;

			}
		}
	}

}
int layer2[25][40] = { 67,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,68,69,70,71,70,71,72,
					   73,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,74,75,76,77,76,77,78,
					   79,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,80,81,82,83,82,83,84,
					   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,88,
0,0,0,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,86,0,91,92,
0,0,0,89,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,90,0,0,0,
87,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
91,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,87,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,86,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,91,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,90,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,89,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,86,0,
0,0,0,0,0,0,0,87,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,90,0,
0,0,0,0,0,0,0,91,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
37,38,39,40,41,38,39,40,41,38,39,40,41,38,39,40,41,38,39,40,41,38,39,40,38,39,40,41,38,39,40,41,38,39,40,38,39,40,41,42,
43,44,45,46,47,44,45,46,47,44,45,46,47,44,45,46,47,44,45,46,47,44,45,46,44,45,46,47,44,45,46,47,44,45,46,44,45,46,47,48 };


int** Map::getCollisionPos() {
	int** collision = new int* [25];
	for (int i = 0; i < 25; ++i) {
		collision[i] = new int[40];
	}
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 40; ++j) {
			if (layer2[i][j] != 0) {
				collision[i][j] = 1;
			}
			else {
				collision[i][j] = 0;
			}
		}
	}
	return collision;
}


void Map::drawMapLayer2() {
	int type = 0;
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 40; ++j) {
			type = layer2[i][j];
			desR.x = j * 32;
			desR.y = i * 32;
			switch (type) {
			case 37:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 0, desR.x, desR.y);
				break;

			case 38:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 0, desR.x, desR.y);
				break;

			case 39:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 0, desR.x, desR.y);
				break;

			case 40:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 0, desR.x, desR.y);
				break;

			case 41:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 0, desR.x, desR.y);
				break;

			case 42:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 0, desR.x, desR.y);
				break;

			case 43:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 1, desR.x, desR.y);
				break;

			case 44:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 1, desR.x, desR.y);
				break;

			case 45:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 1, desR.x, desR.y);
				break;

			case 46:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 1, desR.x, desR.y);
				break;

			case 47:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 1, desR.x, desR.y);
				break;

			case 48:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 1, desR.x, desR.y);
				break;

			case 49:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 2, desR.x, desR.y);
				break;

			case 50:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 2, desR.x, desR.y);
				break;

			case 51:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 2, desR.x, desR.y);
				break;

			case 52:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 2, desR.x, desR.y);
				break;

			case 53:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 2, desR.x, desR.y);
				break;

			case 54:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 2, desR.x, desR.y);
				break;

			case 55:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 3, desR.x, desR.y);
				break;

			case 56:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 3, desR.x, desR.y);
				break;

			case 57:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 3, desR.x, desR.y);
				break;

			case 58:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 3, desR.x, desR.y);
				break;

			case 59:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 3, desR.x, desR.y);
				break;

			case 60:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 3, desR.x, desR.y);
				break;

			case 61:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 4, desR.x, desR.y);
				break;

			case 62:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 4, desR.x, desR.y);
				break;

			case 63:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 4, desR.x, desR.y);
				break;

			case 64:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 4, desR.x, desR.y);
				break;

			case 65:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 4, desR.x, desR.y);
				break;

			case 66:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 4, desR.x, desR.y);
				break;

			case 67:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 5, desR.x, desR.y);
				break;

			case 68:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 5, desR.x, desR.y);
				break;

			case 69:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 5, desR.x, desR.y);
				break;

			case 70:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 5, desR.x, desR.y);
				break;

			case 71:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 5, desR.x, desR.y);
				break;

			case 72:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 5, desR.x, desR.y);
				break;

			case 73:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 6, desR.x, desR.y);
				break;

			case 74:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 6, desR.x, desR.y);
				break;

			case 75:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 6, desR.x, desR.y);
				break;

			case 76:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 6, desR.x, desR.y);
				break;

			case 77:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 6, desR.x, desR.y);
				break;

			case 78:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 6, desR.x, desR.y);
				break;

			case 79:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 0, 7, desR.x, desR.y);
				break;

			case 80:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 1, 7, desR.x, desR.y);
				break;

			case 81:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 2, 7, desR.x, desR.y);
				break;

			case 82:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 3, 7, desR.x, desR.y);
				break;

			case 83:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 4, 7, desR.x, desR.y);
				break;

			case 84:
				TextureManager::Instance()->drawMap("assets/rockSet.png", Game::Instance()->getRenderer(), 5, 7, desR.x, desR.y);
				break;

			case 85:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 0, 0, desR.x, desR.y);
				break;

			case 86:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 1, 0, desR.x, desR.y);
				break;

			case 87:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 2, 0, desR.x, desR.y);
				break;

			case 88:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 3, 0, desR.x, desR.y);
				break;

			case 89:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 0, 1, desR.x, desR.y);
				break;

			case 90:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 1, 1, desR.x, desR.y);
				break;

			case 91:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 2, 1, desR.x, desR.y);
				break;

			case 92:
				TextureManager::Instance()->drawMap("assets/decoSet.png", Game::Instance()->getRenderer(), 3, 1, desR.x, desR.y);
				break;
			}
		}
	}
}