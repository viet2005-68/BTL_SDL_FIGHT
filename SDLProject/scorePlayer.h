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
		m_font_score = new WriteOnScreen("assets/ThaleahFat.ttf",13);
	}
	void draw() {
		m_font_score->displayText(std::to_string(scorePlayer),500,0,32,50);
	}
	~ScorePlayer() {
		delete m_font_score;
	}
	void Setscore(int x) {
		scorePlayer += x;
	}
	void reset() {
		scorePlayer = 0;
	}
	int getScore() {
		return scorePlayer;
	}
private:
	int scorePlayer;
	SDL_Rect m_score;
	WriteOnScreen* m_font_score;
};