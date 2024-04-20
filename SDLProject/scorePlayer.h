#pragma once
#include <SDL.h>
#include "WriteOnScreen.h"
#include <cstring>
#include <string>

class ScorePlayer {
public:
	ScorePlayer() {
		scorePlayer = 0;
		m_score = { 0,500,14,14 };
		m_font_score = new WriteOnScreen("assets/font.ttf", 18);
	}
	void draw() {
		m_font_score->displayText("SCORE: " + std::to_string(scorePlayer), 800, 10, 220, 50);
	}
	~ScorePlayer() {
		delete m_font_score;
	}
	void Setscore(int x) {
		scorePlayer += x;
	}
	int getScore() {
		return scorePlayer;
	}
	void reset() {
		scorePlayer = 0;
	}
private:
	int scorePlayer;
	SDL_Rect m_score;
	WriteOnScreen* m_font_score;
};