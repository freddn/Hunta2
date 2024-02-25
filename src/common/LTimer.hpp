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
    Uint64 getTicks();

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
    Uint64 mStartTicks;
    Uint64 mPausedTicks;

    bool mPaused;
    bool mStarted;
};

#endif








