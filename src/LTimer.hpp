#ifndef LTIMER_H
#define LTIMER_H

#include <SDL2/SDL.h>

/* A timer class. Can be used as stopwatch or clock.*/
class LTimer
{
    public:
        LTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();

        bool isStarted();
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








