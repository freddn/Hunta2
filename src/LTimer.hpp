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

#ifndef LTIMER_H
#define LTIMER_H

#include <SDL2/SDL.h>

/* A timer class. Can be used as stopwatch or clock.
 * This timer is used everywhere where we need some type of time control.
 * For example we have one timer when we calculate the fps and one that
 * controls the attack delays and such.
 */
class LTimer {
public:
    LTimer();

    /**
     * Starts the timer.
     */
    void start();

    /**
     * Stop the timer and reset the time.
     */
    void stop();

    /**
     * Stop the timer but don't reset time.
     */
    void pause();

    /**
     * Restart the timer after a pause.
     */
    void unpause();

    /**
     * Will return the time that the timer has been running.
     */
    Uint32 getTicks();

    /**
     * Check if the timer is started.
     */
    bool isStarted();

    /**
     * Check if the timer is paused.
     */
    bool isPaused();

    virtual ~LTimer();
protected:
private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;

    bool mPaused;
    bool mStarted;
};

#endif








