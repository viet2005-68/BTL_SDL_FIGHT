#pragma once
#include <SDL.h>

class TimeOnPlay {
private:
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;

public:
    TimeOnPlay() : startTicks(0), pausedTicks(0), paused(false), started(false) {}

    static TimeOnPlay *getInstance() {
        if (m_Instance == nullptr)
        {
            m_Instance = new TimeOnPlay();
        }
        return m_Instance;  
    }

    void start() {
        started = true;
        paused = false;
        startTicks = SDL_GetTicks();
    }

    void stop() {
        started = false;
        paused = false;
    }

    void pause() {
        if (started && !paused) {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }

    void unpause() {
        if (paused) {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
            pausedTicks = 0;
        }
    }

    Uint32 getTicks() {
        if (started) {
            if (paused) {
                return pausedTicks;
            }
            else {
                return SDL_GetTicks() - startTicks;
            }
        }
        return 0;
    }
private:
    static TimeOnPlay* m_Instance;
};
