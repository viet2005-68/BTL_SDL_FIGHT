#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Time {
public:
    Time() : m_startTime(SDL_GetTicks()) {}


    double getElapsedTime() const {
        return (SDL_GetTicks() - m_startTime) / 1000.0;
    }


    void reset() {
        m_startTime = SDL_GetTicks();
    }

private:
    Uint32 m_startTime;
};

#endif // TIMER_H