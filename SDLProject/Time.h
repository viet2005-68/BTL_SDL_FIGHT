#ifndef TIMER_H
#define TIMER_H
#include "WriteOnScreen.h"
#include <SDL.h>
#include <cstring>
#include <cmath>
class Time {
public:
    Time() : m_startTime(SDL_GetTicks()) {}


    double getElapsedTime() const {
        return (SDL_GetTicks() - m_startTime) / 1000.0;
    }


    void reset() {
        m_startTime = SDL_GetTicks();
    }
    void printTimeOnScreen(double t, int x, int y, int w, int h) {
        text_time = new WriteOnScreen("assets/font.ttf",18);
        int time = int(t+0.5);
        text_time->displayText(std::to_string(time), x, y, w,h);
    }
private:
    WriteOnScreen* text_time;
    Uint32 m_startTime;
};

#endif // TIMER_H