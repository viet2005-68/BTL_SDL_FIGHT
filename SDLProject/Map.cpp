#include "Map.h"
#include "texturemanager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Camera.h"
#include <vector>
#include "SlimeEnemy.h"
Map* Map::m_Instance = nullptr;

SDL_Rect recthouse = {1152,0,128,192};



Map::Map()
{
    Grass = TextureManager::Instance()->loadMap("assets/100.png", Game::Instance()->getRenderer());
    Box = TextureManager::Instance()->loadMap("assets/1004.png", Game::Instance()->getRenderer());
    Water = TextureManager::Instance()->loadMap("assets/110.png", Game::Instance()->getRenderer());
    Wall = TextureManager::Instance()->loadMap("assets/107.png", Game::Instance()->getRenderer());
    row = 40;
    col = 45;
    house = TextureManager::Instance()->loadMap("assets/Goblin_House.png", Game::Instance()->getRenderer());

    LoadMap(lv1);

    Map_Src.x = Map_Src.y = 0;
    Map_Src.w = Map_Src.h = 32;

    MAP_des.x = MAP_des.y = 0;
    MAP_des.w = MAP_des.h = 32;
   
    //tile_queue = new std::queue<Tile*>();
}

Map::~Map()
{
    SDL_DestroyTexture(Grass);
    SDL_DestroyTexture(Water);
    SDL_DestroyTexture(Box);
    SDL_DestroyTexture(Wall);
    //delete tile_queue;
    delete [] Map_in;
}
void Map::LoadMap(int arr[40][45])
{
    // std::ifstream map_file(filename);

    int x;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Vector2D cam = Camera::GetInstance()->GetPosition();
            x = arr[i][j];
            //std::cout << x << "      FKKFD" << endl;
            Map_in[i][j] = new Tile(j * 32, i * 32, x);
            if (x == 0) {
                Map_in[i][j]->Text(Grass);
            }
            else if (x == 3) {
                Map_in[i][j]->Text(Water);
            }
            else if (x == 4) {
                Map_in[i][j]->Text(Box);
            }
            else {
                Map_in[i][j]->Text(Wall);
            }

        }
    }
    

}

void Map::DrawMap()
{

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Map_in[i][j]->draw();
        }
    }
    TextureManager::Instance()->drawMap(house, recthouse);
   // tile_queue = new std::queue<Tile*>();
}
void Map::CleanMap()
{

}
bool Map::checkwall(SDL_Rect a, SDL_Rect b) {
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

bool Map::iswall(SDL_Rect player) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (Map_in[i][j]->type() == 1 || Map_in[i][j]->type() == 4) {
                if (checkwall(player, Map_in[i][j]->getRect())) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Map::check_x_y(int x, int y) {
    if (Map_in[x][y]->type() == 1 || Map_in[x][y]->type() == 4) {
        return false;
    }
    return true;
}
std::pair<int, int> Map::FindPath(SDL_Rect& player, SDL_Rect& destination) {
    // Khởi tạo hàng đợi và thêm vị trí người chơi vào hàng đợi
    
    std::queue<std::pair<int, int>> tile_queue;
    int player_x = player.x / 32;
    int player_y = player.y / 32;
    std::cout << player_x << " " << player_y << std::endl;
    tile_queue.push({ player_x, player_y });
    if (player_x < 0 || player_x > 45) {
        return { 0,0 };
    }
    if (player.y < 0) {
        return { 0, 0 };
    }
    // Khởi tạo mảng visited để đánh dấu các ô đã được thăm
    bool visited[100][100];
    for (int i = 0; i < 40 ; i++) {
        for (int j = 0; j < 45; j++) {
            visited[i][j] = false;
        }
    }
    visited[player_x][player_y] = true;

    while (!tile_queue.empty()) {
        std::pair<int, int> current = tile_queue.front();
        tile_queue.pop();

        // Kiểm tra xem ô hiện tại có phải là đích hay không
        if (current.first == destination.x / 32 && current.second == destination.y / 32) {
            // Nếu tìm thấy đích, trả về true
            return current;
        }

        // Duyệt các ô lân cận của ô hiện tại
        for (int i = -1; i <= 2; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                // Kiểm tra xem ô lân cận có hợp lệ hay không
                if (neighbor_x >= 0 && neighbor_x < row &&
                    neighbor_y >= 0 && neighbor_y < col &&
                    !visited[neighbor_x][neighbor_y] &&
                    (lv1_check[neighbor_x][neighbor_y] != 1)) {
                    // Đánh dấu ô lân cận là đã được thăm và thêm vào hàng đợi
                    visited[neighbor_x][neighbor_y] = true;
                    tile_queue.push({ neighbor_x, neighbor_y });
                }
            }
        }
    }

    // Nếu không tìm thấy đích, trả về false
    return { 0,0 };
}

std::pair<int, int> Map::FindOptimalPath(SDL_Rect& player, SDL_Rect& destination) {

    // Khởi tạo priority_queue và thêm vị trí người chơi vào
    std::priority_queue<std::pair<int, std::pair<int, int>>,
        std::vector<std::pair<int, std::pair<int, int>>>,
        std::greater<std::pair<int, std::pair<int, int>>>>
        tile_queue;
    destination.w = 32;
    destination.h = 32;
    int player_x = player.x  / 32;
    int player_y = player.y / 32;

    int g = 0;
    int h = heuristic(player_x, player_y, destination.x / 32, destination.y / 32);
    tile_queue.push({ g + h, {player_x, player_y} });

    // Khởi tạo mảng visited để đánh dấu các ô đã được thăm
    
    bool visited[100][100];
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 45; j++) {
            visited[i][j] = false;
        }
    }
    if (player_x > 100) player.x = 0;
    if (player_y > 1000 || player.y < 0) player.y = 1;
    if (player_x < 0 || player_x > 45) {
        return { 0,0 };
    }
    if (player_y < 0 || player_y > 40) {
        return { 0,0 };
    }
    visited[player_x][player_y] = true;

    while (!tile_queue.empty()) {
        std::pair<int, int> current = tile_queue.top().second;
        tile_queue.pop();

        // Kiểm tra xem ô hiện tại có phải là đích hay không
        if (isDestination(destination,player)) {
            // Nếu tìm thấy đích, trả về true
            return current;
        }

        // Duyệt các ô lân cận của ô hiện tại
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                // Kiểm tra xem ô lân cận có hợp lệ hay không
                if (neighbor_x >= 0 && neighbor_x < row &&
                    neighbor_y >= 0 && neighbor_y < col &&
                    !visited[neighbor_x][neighbor_y] &&
                    (lv1_check[neighbor_x][neighbor_y] != 1)) {
                    // Đánh dấu ô lân cận là đã được thăm
                    visited[neighbor_x][neighbor_y] = true;

                    // Tính toán giá trị g và h cho ô lân cận
                    int g_neighbor = g + 1;
                    int h_neighbor = heuristic(neighbor_x, neighbor_y, destination.x / 32, destination.y / 32);

                    // Thêm ô lân cận vào priority_queue
                    tile_queue.push({ g_neighbor + h_neighbor, {neighbor_x, neighbor_y} });
                }
            }
        }
    }

    // Nếu không tìm thấy đích, trả về {0, 0}
    return { 0, 0 };
}
