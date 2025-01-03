﻿#include "Map_lv2.h"
#include "texturemanager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SlimeEnemy.h"

Map_lv2* Map_lv2::m_Instance = nullptr;

SDL_Rect recthouse = { 102,0,128,192 };

SDL_Rect src, des;

Map_lv2::Map_lv2()
{

    TextureManager::Instance()->load("assets/Tileset.png", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/tile_24.png", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/1004.png", Game::Instance()->getRenderer());
    //tile_queue = new std::queue<Tile*>();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            Map_in[i][j] = new Tile(j * 32, i * 32, check_lv2[i][j]);
        }
    }
}

Map_lv2::~Map_lv2()
{
    SDL_DestroyTexture(m_Texture);

    //delete tile_queue;
    delete[] Map_in;
}

void Map_lv2::drawLayer3() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer3[i][j];
            des.x = j * 32;
            des.y = i * 32;
            switch (type)
            {
            case 76:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 4, 7, des.x, des.y);
                break;
            case 93:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 1, 9, des.x, des.y);
                break;
            case 92:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 0, 9, des.x, des.y);
                break;
            default:
                break;
            }
        }
    }
}
void Map_lv2::drawLayer1() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer1[i][j];
            des.x = j * 32;
            des.y = i * 32;
            switch (type)
            {
            case 80:
                TextureManager::Instance()->drawMap("assets/tile_24.png", Game::Instance()->getRenderer(), 0, 0, des.x, des.y);
                break;
            case 24:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 2, 2, des.x, des.y);
                break;

            default:
                break;
            }
        }
    }
}
void Map_lv2::drawLayer2() {
    int type = 0;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            type = layer2[i][j];
            des.x = j * 32;
            des.y = i * 32;
            switch (type)
            {
            case 1:
                TextureManager::Instance()->drawMap("assets/1004.png", Game::Instance()->getRenderer(), 0, 0, des.x, des.y);
                break;
            case 3:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 1, 0, des.x, des.y);
                break;
            case 12:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 0, 1, des.x, des.y);
                break;
            case 42:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 0, 4, des.x, des.y);
                break;
            case 53:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 1, 5, des.x, des.y);
                break;
            case 17:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 5, 1, des.x, des.y);
                break;
            case 52:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 0, 5, des.x, des.y);
                break;
            case 55:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 3, 5, des.x, des.y);
                break;
            case 47:
                TextureManager::Instance()->drawMap("assets/Tileset.png", Game::Instance()->getRenderer(), 5, 4, des.x, des.y);
                break;
            default:
                break;
            }
        }
    }
}
void Map_lv2::DrawMap()
{



    drawLayer1();
    drawLayer2();
    drawLayer3();
}
void Map_lv2::CleanMap()
{

}
bool Map_lv2::checkwall(SDL_Rect a, SDL_Rect b) {
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

bool Map_lv2::iswall(SDL_Rect player) {

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            if (Map_in[i][j]->type() != 0) {
                if (checkwall(player, Map_in[i][j]->getRect())) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Map_lv2::check_x_y(int x, int y) {
    if (Map_in[x][y]->type() == 1) {
        return false;
    }
    return true;
}
std::pair<int, int> Map_lv2::FindPath(SDL_Rect& player, SDL_Rect& destination) {

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

        if (current.first == destination.x / 32 && current.second == destination.y / 32) {

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
                    (check_lv2[neighbor_x][neighbor_y] != 1)) {
                    // tick valid box
                    visited[neighbor_x][neighbor_y] = true;
                    tile_queue.push({ neighbor_x, neighbor_y });
                }
            }
        }
    }


    return { 0,0 };
}

std::pair<int, int> Map_lv2::FindOptimalPath(SDL_Rect& player, SDL_Rect& destination) {

    std::priority_queue<std::pair<int, std::pair<int, int>>,
        std::vector<std::pair<int, std::pair<int, int>>>,
        std::greater<std::pair<int, std::pair<int, int>>>>
        tile_queue;

    int player_x = (player.x) / 32;
    int player_y = (player.y) / 32;

    int g = 0;
    int h = heuristic(player_x, player_y, destination.x / 32, destination.y / 32);
    tile_queue.push({ g + h, {player_x, player_y} });


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

        if (current.first == destination.x / 32 && current.second == destination.y / 32) {
            return current;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current.first + i;
                int neighbor_y = current.second + j;

                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    !visited[neighbor_x][neighbor_y] &&
                    (check_lv2[neighbor_x][neighbor_y] != 1)) {
                    visited[neighbor_x][neighbor_y] = true;

                    int g_neighbor = g + 1;
                    int h_neighbor = heuristic(neighbor_x, neighbor_y, destination.x / 32, destination.y / 32);

                    tile_queue.push({ g_neighbor + h_neighbor, {neighbor_x, neighbor_y} });
                }
            }
        }
    }


    return { 0, 0 };
}
std::pair<int, int> Map_lv2::FindPathAStar(SDL_Rect& player, SDL_Rect& destination) {
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> tile_queue;
    int player_x = player.x / 32;
    int player_y = player.y / 32;
    tile_queue.push({ 0, {player_x, player_y} });

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

    int g_cost[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            g_cost[i][j] = INT_MAX;
        }
    }
    g_cost[player_x][player_y] = 0;

    int h_cost[100][100];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            h_cost[i][j] = std::abs(i - destination.x / 32) + std::abs(j - destination.y / 32); // Ước lượng chi phí là khoảng cách Manhattan
        }
    }

    while (!tile_queue.empty()) {
        std::pair<int, std::pair<int, int>> current = tile_queue.top();
        tile_queue.pop();

        int current_x = current.second.first;
        int current_y = current.second.second;
        int current_f_cost = current.first;

        if (current_x == destination.x / 32 && current_y == destination.y / 32) {
            return { current_x, current_y };
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_x = current_x + i;
                int neighbor_y = current_y + j;

                if (neighbor_x >= 0 && neighbor_x < 25 &&
                    neighbor_y >= 0 && neighbor_y < 40 &&
                    !visited[neighbor_x][neighbor_y] &&
                    (check_lv2[neighbor_x][neighbor_y] != 1)) {

                    visited[neighbor_x][neighbor_y] = true;


                    int new_g_cost = g_cost[current_x][current_y] + 1;

                    if (new_g_cost < g_cost[neighbor_x][neighbor_y]) {

                        g_cost[neighbor_x][neighbor_y] = new_g_cost;
                        int new_f_cost = g_cost[neighbor_x][neighbor_y] + h_cost[neighbor_x][neighbor_y];

                        tile_queue.push({ new_f_cost, {neighbor_x, neighbor_y} });
                    }
                }
            }
        }
    }
    return { 0, 0 };
}


