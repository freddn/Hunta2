#include "LTimer.hpp"

LTimer::LTimer() {
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start() {
    mStarted = true;
    mPaused = false;

    mStartTicks = SDL_GetTicks64();
    mPausedTicks = 0;
}

void LTimer::stop() {
    mStarted = false;
    mPaused = false;

    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause() {
    if(mStarted && !mPaused) {
        mPaused = true;

        mPausedTicks = SDL_GetTicks64() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    mPaused = false;

    mStartTicks = SDL_GetTicks64() - mPausedTicks;
    mPausedTicks = 0;
}

Uint64 LTimer::getTicks() {
    Uint64 time = 0;

    if(mStarted) {
        if(mPaused) {
            time = mPausedTicks;
        } else {
            time = SDL_GetTicks64() - mStartTicks;
        }
    }
    return time;
}

bool LTimer::isStarted() {
    return mStarted;
}

bool LTimer::isPaused() {
    return mPaused;
}

LTimer::~LTimer() {
    //dtor
}











