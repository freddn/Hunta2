/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 *
 * This file is a part of the Hunta2 project.
 *
 * Hunta2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hunta2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

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

    mStartTicks = SDL_GetTicks();
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

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    mPaused = false;

    mStartTicks = SDL_GetTicks() - mPausedTicks;
    mPausedTicks = 0;
}

Uint32 LTimer::getTicks() {
    Uint32 time = 0;

    if(mStarted) {
        if(mPaused) {
            time = mPausedTicks;
        } else {
            time = SDL_GetTicks() - mStartTicks;
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











