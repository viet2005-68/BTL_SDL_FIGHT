#ifndef TIMER_H
#define TIMER_H
#include "WriteOnScreen.h"
#include <SDL.h>
#include <cstring>
#include <cmath>
#include <sstream>
#include <iomanip>

class Time {
public:
    Time() : m_startTime(SDL_GetTicks()), m_pausedTime(0), m_paused(false) {}


    double getElapsedTime() const {
        if (m_paused) {
            return (m_pausedTime - m_startTime) / 1000.0;
        }
        else {
            return (SDL_GetTicks() - m_startTime) / 1000.0;
        }
    }



    void reset() {
        m_startTime = SDL_GetTicks();
    }
    void pause() {
        if (!m_paused) {
            m_pausedTime = SDL_GetTicks();
            m_paused = true;
        }
    }

    void resume() {
        if (m_paused) {
            m_startTime += SDL_GetTicks() - m_pausedTime;
            m_paused = false;
        }
    }
    void printTimeOnScreen(double t, int x, int y, int w, int h) {
        text_time = new WriteOnScreen("assets/font.ttf", 18);
        int time = int(t + 0.5);
        text_time->displayText(std::to_string(time), x, y, w, h);
    }
    void prinTimeCount(double t, int x, int y, int w, int h) {
        timeonscreen = new WriteOnScreen("assets/font.ttf", 18);
        timeonscreen->displayText(getElapsedTimeInMinutesAndSeconds(), x, y, w, h);
    }
    std::string getElapsedTimeInMinutesAndSeconds() const {
        int totalSeconds = getElapsedTime();
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        return oss.str();
    }

private:

    WriteOnScreen* text_time;
    Uint32 m_startTime;
    Uint32 m_pausedTime;
    WriteOnScreen* timeonscreen;
    bool m_paused;
};

#endif // TIMER_H