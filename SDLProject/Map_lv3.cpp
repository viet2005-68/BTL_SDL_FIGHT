#include "Map_lv3.h"
#include "texturemanager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SlimeEnemy.h"

Map_lv3* Map_lv3::m_Instance = nullptr;


SDL_Rect src3, des3;

Map_lv3::Map_lv3()
{

    TextureManager::Instance()->load("assets/lv3grass.png", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/lv3props.png", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/lv3struct.png", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/lv3wall.png",Game::Instance()->getRenderer());
    //tile_queue = new std::queue<Tile*>();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            Map_in[i][j] = new Tile3(j * 32, i * 32, check_lv3[i][j]);

        }
    }
}

Map_lv3::~Map_lv3()
{
    SDL_DestroyTexture(m_Texture);

    //delete tile_queue;
    delete[] Map_in;
}

void Map_lv3::drawLayer3() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer3[i][j];
            des3.x = j * 32;
            des3.y = i * 32;
            switch (type)
            {
            case 33:
                TextureManager::Instance()->drawMap("assets/lv3grass.png", Game::Instance()->getRenderer(), 0, 4, des3.x, des3.y);
                break;
            case 428:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 5, des3.x, des3.y);
                break;
            case 444:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 6, des3.x, des3.y);
                break;
            case 460:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 7, des3.x, des3.y);
                break;
            case 406:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 5, 4, des3.x, des3.y);
                break;
            case 422:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 5, 5, des3.x, des3.y);
                break;
            case 346:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 0, des3.x, des3.y);
                break;
            case 347:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(),10, 0, des3.x, des3.y);
                break;
            case 362:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 1, des3.x, des3.y);
                break;
            case 363:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 10, 1, des3.x, des3.y);
                break;
            case 994:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 1, 1, des3.x, des3.y);
                break;
            case 995:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 2, 1, des3.x, des3.y);
                break;
            case 1010:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 1, 2, des3.x, des3.y);
                break;
            case 1011:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 2, 2, des3.x, des3.y);
                break;
            case 1026:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 1, 3, des3.x, des3.y);
                break;
            case 1027:
                TextureManager::Instance()->drawMap("assets/lv3struct.png", Game::Instance()->getRenderer(), 2, 3, des3.x, des3.y);
                break;
            case 376:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 5, des3.x, des3.y);
                break;
            case 392:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 6, des3.x, des3.y);
                break;
            case 408:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 7, des3.x, des3.y);
                break;
            case 351:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(),14,0, des3.x, des3.y);
                break;
            case 367:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 14, 1, des3.x, des3.y);
                break;
            case 383:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 14, 2, des3.x, des3.y);
                break;
            case 378:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 2, des3.x, des3.y);
                break;
            case 379:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 10, 2, des3.x, des3.y);
                break;
            case 394:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 3, des3.x, des3.y);
                break;
            
            case 395:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 10, 3, des3.x, des3.y);
                break;
            case 420:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 3, 5, des3.x, des3.y);
                break;
            case 488:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 7, 9, des3.x, des3.y);
                break;
            case 504:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 7, 10, des3.x, des3.y);
                break;
            default:
                break;
            }
        }
    }
}
void Map_lv3::drawLayer1() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer1[i][j];
            des3.x = j * 32;
            des3.y = i * 32;
            switch (type)
            {
            case 17:
                TextureManager::Instance()->drawMap("assets/lv3grass.png", Game::Instance()->getRenderer(), 0, 3, des3.x, des3.y);
                break;
            case 13:
                TextureManager::Instance()->drawMap("assets/lv3grass.png", Game::Instance()->getRenderer(), 4, 1, des3.x, des3.y);
                break;
            case 33:
                TextureManager::Instance()->drawMap("assets/lv3grass.png", Game::Instance()->getRenderer(), 0, 4, des3.x, des3.y);
                break;
            default:
                break;
            }
        }
    }
}
void Map_lv3::drawLayer2() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer2[i][j];
            des3.x = j * 32;
            des3.y = i * 32;
            switch (type)
            {
            case 82:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 1, des3.x, des3.y);
                break;
            case 93:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 1, des3.x, des3.y);
                break;
            case 490:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 9, des3.x, des3.y);
                break;
            case 506:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 9, 10, des3.x, des3.y);
                break;
            case 122:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 9, 3, des3.x, des3.y);
                break;
            case 84:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 3, 1, des3.x, des3.y);
                break;
            case 162:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 6, des3.x, des3.y);
                break;
            case 163:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 6, des3.x, des3.y);
                break;
            case 164:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 3, 6, des3.x, des3.y);
                break;
            case 165:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 4, 6, des3.x, des3.y);
                break;
            case 178:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 7, des3.x, des3.y);
                break;
            case 179:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 7, des3.x, des3.y);
                break;
            case 180:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 3, 7, des3.x, des3.y);
                break;
            case 181:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 4, 7, des3.x, des3.y);
                break;
            case 123:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 10, 3, des3.x, des3.y);
                break;
            case 476:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 8, des3.x, des3.y);
                break;
            case 477:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 12, 8, des3.x, des3.y);
                break;
            case 478:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 13, 8, des3.x, des3.y);
                break;
            case 492:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 9, des3.x, des3.y);
                break;
            case 493:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 12, 9, des3.x, des3.y);
                break;
            case 494:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 13, 9, des3.x, des3.y);
                break;
            case 479:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 13, 9, des3.x, des3.y);
                break;
            case 508:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 11, 10, des3.x, des3.y);
                break;
            case 509:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 12, 10, des3.x, des3.y);
                break;
            case 510:
                TextureManager::Instance()->drawMap("assets/lv3props.png", Game::Instance()->getRenderer(), 13, 10, des3.x, des3.y);
                break;
            case 109:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 12, 2, des3.x, des3.y);
                break;
            case 110:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 13, 2, des3.x, des3.y);
                break;
            case 117:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 12, 3, des3.x, des3.y);
                break;
            case 126:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 13, 3, des3.x, des3.y);
                break;
            case 141:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 12, 4, des3.x, des3.y);
                break;
            case 142:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 13, 4, des3.x, des3.y);
                break;
            case 83:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 1, des3.x, des3.y);
                break;
            case 85:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 1, des3.x, des3.y);
                break;
            case 98:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 2, des3.x, des3.y);
                break;
            case 99:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 2, des3.x, des3.y);
                break;
            case 100:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(),3 , 2, des3.x, des3.y);
                break;
            case 114:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 3, des3.x, des3.y);
                break;
            case 115:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 3, des3.x, des3.y);
                break;
            case 116:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 3, 3, des3.x, des3.y);
                break;
            case 130:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 1, 4, des3.x, des3.y);
                break;
            case 131:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 2, 4, des3.x, des3.y);
                break;
            case 132:
                TextureManager::Instance()->drawMap("assets/lv3wall.png", Game::Instance()->getRenderer(), 3, 4, des3.x, des3.y);
                break;
            default:
                break;
            }
        }
    }
}
void Map_lv3::DrawMap()
{
    drawLayer1();

    drawLayer2();
    drawLayer3();
   
    
   
    
    
}
void Map_lv3::CleanMap()
{

}
bool Map_lv3::checkwall(SDL_Rect a, SDL_Rect b) {
    int left_a = a.x;
    int right_a = a.x + a.w;
    int top_a = a.y;
    int bottom_a = a.y + a.h;

    int left_b = b.x;
    int right_b = b.x + b.w;
    int top_b = b.y;
    int bottom_b = b.y + b.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

bool Map_lv3::iswall(SDL_Rect player) {

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            if (Map_in[i][j]->type() == 1) {
                if (checkwall(player, Map_in[i][j]->getRect())) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Map_lv3::check_x_y(int x, int y) {
    if (Map_in[x][y]->type() == 1) {
        return false;
    }
    return true;
}
int Map_lv3::FindBFSPath(SDL_Rect& player, SDL_Rect& destination, int x) {
    // Khởi tạo 

    std::queue<std::pair<int, int>> tile_queue;
    int player_x = player.x / 32;
    int player_y = player.y / 32;
    std::cout << player_x << " " << player_y << std::endl;
    tile_queue.push({ player_x, player_y });

    // Khởi tạo mảng visited để đánh dấu các ô đã được thăm
    bool visited[100][100];
    int distance[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            visited[i][j] = false;
            distance[i][j] = 0;
        }
    }
    visited[player_x][player_y] = true;
    if (x == 5) {
        visited[player_x - 1][player_y] = 1;
        visited[player_x + 1][player_y] = 1;
        visited[player_x][player_y + 1] = 1;
    }
    else if (x == 2) {
        visited[player_x - 1][player_y] = 1;
        visited[player_x + 1][player_y] = 1;
        visited[player_x][player_y - 1] = 1;
    }
    else if (x == 1) {
        visited[player_x + 1][player_y] = 1;
        visited[player_x][player_y - 1] = 1;
        visited[player_x][player_y + 1] = 1;
    }
    else {
        visited[player_x - 1][player_y] = 1;
        visited[player_x][player_y - 1] = 1;
        visited[player_x][player_y + 1] = 1;
    }
    distance[player_x][player_y] = 0;

    while (!tile_queue.empty()) {
        std::pair<int, int> current = tile_queue.front();
        tile_queue.pop();

        // Kiểm tra xem ô hiện tại là đích ??
        /*if (current.first == des3tination.x / 32 && current.second == des3tination.y / 32) {

            return current;
        }*/

        // Duyệt các ô lân cận của ô hiện tại
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                // check 
                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    visited[neighbor_x][neighbor_y] == 0 &&
                    (check_lv3[neighbor_x][neighbor_y] != 1)) {
                    // tick valid box
                    distance[neighbor_x][neighbor_y] = distance[current.first][current.second] + 1;
                    if (distance[(int)destination.x / 32][(int)destination.y / 32] != 0) break;
                    visited[neighbor_x][neighbor_y] = true;
                    tile_queue.push({ neighbor_x, neighbor_y });
                }
            }
        }
    }

    return distance[(int)destination.x / 32][(int)destination.y / 32];
}

std::pair<int, int> Map_lv3::FindPath(SDL_Rect& player, SDL_Rect& destination) {

    std::queue<std::pair<int, int>> tile_queue;
    int player_x = player.x / 32;
    int player_y = player.y / 32;
    std::cout << player_x << " " << player_y << std::endl;
    tile_queue.push({ player_x, player_y });

    bool visited[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            visited[i][j] = false;
        }
    }
    visited[player_x][player_y] = true;

    while (!tile_queue.empty()) {
        std::pair<int, int> current = tile_queue.front();
        tile_queue.pop();

        SDL_Rect check = { current.first * 32,current.second * 32,32,32 };
        if (checkwall(check, destination)) {

            return current;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                // check 
                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    !visited[neighbor_x][neighbor_y] &&
                    (check_lv3[neighbor_x][neighbor_y] != 1)) {
                    // tick valid box
                    visited[neighbor_x][neighbor_y] = true;
                    tile_queue.push({ neighbor_x, neighbor_y });
                }
            }
        }
    }


    return { 0,0 };
}
std::pair<int, int> Map_lv3::FindOptimalPath(SDL_Rect& player, SDL_Rect& destination) {

    // khởi tạo
    std::priority_queue<std::pair<int, std::pair<int, int>>,
        std::vector<std::pair<int, std::pair<int, int>>>,
        std::greater<std::pair<int, std::pair<int, int>>>>
        tile_queue;

    int player_x = (player.x) / 32;
    int player_y = (player.y) / 32;

    int g = 0;
    int h = heuristic(player_x, player_y, destination.x / 32, destination.y / 32);
    tile_queue.push({ g + h, {player_x, player_y} });

    // Khởi tạo mảng visited đánh dấu các ô đã được thăm

    bool visited[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            visited[i][j] = false;
        }
    }

    visited[player_x][player_y] = true;

    while (!tile_queue.empty()) {
        std::pair<int, int> current = tile_queue.top().second;
        tile_queue.pop();

        // Kiểm tra xem ô hiện tại phải là đích ?
        SDL_Rect check = { current.first * 32,current.second * 32,32,32 };
        if (checkwall(check, destination)) {

            return current;
        }

        // Duyệt các ô lân cận 
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                // Kiểm tra xem ô lân cận
                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    !visited[neighbor_x][neighbor_y] &&
                    (check_lv3[neighbor_x][neighbor_y] != 1)) {
                    // Đánh dấu ô lân cận 
                    visited[neighbor_x][neighbor_y] = true;

                    // Tính toán giá trị g và h cho ô lân cận
                    int g_neighbor = g + 1;
                    int h_neighbor = heuristic(neighbor_x, neighbor_y, destination.x / 32, destination.y / 32);

                    // Thêm ô lân cận vào 
                    tile_queue.push({ g_neighbor + h_neighbor, {neighbor_x, neighbor_y} });
                }
            }
        }
    }


    return { 0, 0 };
}
std::pair<int, int> Map_lv3::FindPathAStar(SDL_Rect& player, SDL_Rect& destination) {
    // Khởi tạo  
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> tile_queue;
    int player_x = player.x / 32;
    int player_y = player.y / 32;
    tile_queue.push({ 0, {player_x, player_y} }); // Chi phí ban đầu là 0

    // Khởi tạo mảng visited
    bool visited[40][40];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            visited[i][j] = false;
        }
    }
    /*if (player_x > 100) player.x = 0;
    if (player_y > 100 || player.y < 0) player.y = 0;
    if (player_x < 0) {
        return { 0,0 };
    }
    if (player_y < 0) {
        return { 0,0 };
    }*/
    visited[player_x][player_y] = true;

    // Khởi tạo mảng g_cost để lưu trữ chi phí di chuyển đến mỗi ô
    int g_cost[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            g_cost[i][j] = INT_MAX; // Khởi tạo chi phí ban đầu
        }
    }
    g_cost[player_x][player_y] = 0; // Chi phí di chuyển đến ô người chơi là 0

    // Khởi tạo mảng h_cost để lưu trữ ước lượng chi phí di chuyển đến đích
    int h_cost[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            h_cost[i][j] = std::abs(i - destination.x / 32) + std::abs(j - destination.y / 32); // Ước lượng chi phí là khoảng cách Manhattan
        }
    }

    while (!tile_queue.empty()) {
        // Lấy ô có chi phí f (tổng chi phí g + h) nhỏ nhất ra khỏi hàng đợi
        std::pair<int, std::pair<int, int>> current = tile_queue.top();
        tile_queue.pop();

        int current_x = current.second.first;
        int current_y = current.second.second;
        int current_f_cost = current.first;

        // Kiểm tra xem ô hiện tại có phải là đích hay không
        SDL_Rect check = { current_x * 32,current_y * 32,32,32 };
        if (checkwall(check, destination)) {

            return { current_x, current_y };
        }


        // Duyệt các ô lân cận của ô hiện tại
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current_x + i;
                int neighbor_y = current_y + j;

                // Kiểm tra xem ô lân cận có hợp lệ hay không
                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    !visited[neighbor_x][neighbor_y] &&
                    (check_lv3[neighbor_x][neighbor_y] != 1)) {
                    // Đánh dấu ô lân cận là đã được thăm
                    visited[neighbor_x][neighbor_y] = true;

                    // Tính toán chi phí di chuyển đến ô lân cận
                    int new_g_cost = g_cost[current_x][current_y] + 1; // Chi phí di chuyển là 1
                    // Kiểm tra xem có nên cập nhật chi phí và vị trí trong hàng đợi hay không
                    if (new_g_cost < g_cost[neighbor_x][neighbor_y]) {
                        // Cập nhật chi phí g và tính toán chi phí f mới
                        g_cost[neighbor_x][neighbor_y] = new_g_cost;
                        int new_f_cost = g_cost[neighbor_x][neighbor_y] + h_cost[neighbor_x][neighbor_y];

                        // Cập nhật vị trí với chi phí f mới
                        tile_queue.push({ new_f_cost, {neighbor_x, neighbor_y} });
                    }
                }
            }
        }
    }

    // Nếu không tìm thấy đích, trả về {0, 0}
    return { 0, 0 };
}


