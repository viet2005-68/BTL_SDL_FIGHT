#pragma once
#include <fstream>
#include <iostream>
#include "WriteOnScreen.h"
#include <cstring>

class BestScore {
public:
    BestScore() {
        filename = "assets/score.txt";
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Không thể mở tệp: " << filename << std::endl;
            return;
        }
        file >> highScore;

        best_score = new WriteOnScreen("assets/font.ttf", 14);

    }

    static BestScore* GetInstance() {
        if (m_Instance == nullptr) {
            m_Instance = new BestScore();
        }
        return m_Instance;
    }
    
    void draw() {
        filename = "assets/score.txt";
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Can't not open file now " << filename << std::endl;
            return;
        }
        file >> highScore;

        best_score = new WriteOnScreen("assets/font.ttf", 18);
        std::string PrintScore = "HIGHEST SCORE: " + std::to_string(highScore);
        best_score->displayText(PrintScore, 420, 660, 240, 40);
    }
    void updateHighScore(int playerScore) {
        if (playerScore > highScore) {
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "Can't not open file: " << filename << std::endl;
                return;
            }
            file << playerScore;
        }
    }

    ~BestScore(){}

private:
    static BestScore* m_Instance;
    std::string filename;
    int highScore;
    WriteOnScreen* best_score;
};

