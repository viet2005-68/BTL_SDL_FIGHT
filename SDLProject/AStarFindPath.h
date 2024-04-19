#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <limits> 

struct Node {
    int x, y;
    bool bObstacle;
    bool bVisited;
    float fGlobalGoal;
    float fLocalGoal; // Khoảng cách ước tính tới mục tiêu nếu đi qua nút này
    Node* parent; 
    std::vector<Node*> vecNeighbours; // Danh sách các nút lân cận
};

class AstarFindPath {
public:
    AstarFindPath(std::vector<std::vector<int>> map) {
        this->map = map;
        nMapWidth = 40;
        nMapHeight = 25;

        // KT
        nodes = new Node[nMapWidth * nMapHeight];
        for (int y = 0; y < nMapHeight; y++) {
            for (int x = 0; x < nMapWidth; x++) {
                nodes[y * nMapWidth + x].x = x;
                nodes[y * nMapWidth + x].y = y;
                nodes[y * nMapWidth + x].bObstacle = map[y][x] == 1;
                nodes[y * nMapWidth + x].bVisited = false;
                nodes[y * nMapWidth + x].parent = nullptr;
                nodes[y * nMapWidth + x].vecNeighbours.clear();
            }
        }

        // Connect node in map
        for (int y = 0; y < nMapHeight; y++) {
            for (int x = 0; x < nMapWidth; x++) {
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        // check node  ?? in map
                        if (nx >= 0 && nx < nMapWidth && ny >= 0 && ny < nMapHeight) {
                            nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[ny * nMapWidth + nx]);
                        }
                    }
                }
            }
        }
    }

    // distance of bird fly
    float Heuristic(Node* node, Node* endNode) {
        int dx = abs(node->x - endNode->x);
        int dy = abs(node->y - endNode->y);
        return sqrt(dx * dx + dy * dy);
    }

    std::pair<int, int> FindPath(int startX, int startY, int endX, int endY) {
        // Khởi tạo
        Node* nodeStart = &nodes[startY * nMapWidth + startX];
        Node* nodeEnd = &nodes[endY * nMapWidth + endX];

        // Khởi tạo các nut
        std::list<Node*> listNotTestedNodes;
        listNotTestedNodes.push_back(nodeStart);

        // Khởi tạo ban đầu
        for (int y = 0; y < nMapHeight; y++) {
            for (int x = 0; x < nMapWidth; x++) {
                nodes[y * nMapWidth + x].bVisited = false;
                nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
                nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
                nodes[y * nMapWidth + x].parent = nullptr;
            }
        }

        nodeStart->fLocalGoal = 0.0f;
        nodeStart->fGlobalGoal = Heuristic(nodeStart, nodeEnd);

        while (!listNotTestedNodes.empty()) {
            // 1. Lấy nút có fGlobalGoal thấp nhất
            Node* nodeCurrent = listNotTestedNodes.front();
            listNotTestedNodes.pop_front();

            // 2. Đánh dấu nút hiện tại là đã được khám phá
            nodeCurrent->bVisited = true;

            // 3. Duyệt qua các nút lân cận
            for (Node* nodeNeighbour : nodeCurrent->vecNeighbours) {
                // Bỏ qua nút chướng ngại vật hoặc đã được khám phá
                if (nodeNeighbour->bObstacle || nodeNeighbour->bVisited) continue;

                // 4. Tính toán chi phí di chuyển đến nút lân cận
                float fPossibleLowerGoal = nodeCurrent->fLocalGoal + Distance(nodeCurrent, nodeNeighbour);

                // 5. Cập nhật trạng thái nút lân cận
                if (fPossibleLowerGoal < nodeNeighbour->fLocalGoal) {
                    nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->fLocalGoal = fPossibleLowerGoal;
                    nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + Heuristic(nodeNeighbour, nodeEnd);

                    // Thêm nút lân cận vào danh sách chưa kiểm tra nếu chưa có
                    if (std::find(listNotTestedNodes.begin(), listNotTestedNodes.end(), nodeNeighbour) == listNotTestedNodes.end()) {
                        listNotTestedNodes.push_back(nodeNeighbour);
                    }
                }
            }

            if (nodeCurrent == nodeEnd) {
                std::vector<Node> path;
                Node* pathNode = nodeEnd->parent;
                while (pathNode!= nullptr &&nodeCurrent->parent != nodeStart) {
                    nodeCurrent = nodeCurrent->parent;
                }
                    
                    return { nodeCurrent->x, nodeCurrent->y };
                
            }
        }

       
        return { 0,0 };
    }
   

private:
    std::vector<std::vector<int>> map; 
    int nMapWidth; 
    int nMapHeight; 
    Node* nodes;
    float Distance(Node* nodeA, Node* nodeB) {
        int dx = abs(nodeA->x - nodeB->x);
        int dy = abs(nodeA->y - nodeB->y);
        return sqrt(dx*dx + dy*dy); 
    }
};

