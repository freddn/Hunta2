#ifndef SCREEN_H
#define SCREEN_H

#include <sstream>

#include "Texture.hpp"
//#include "Game.hpp"


class Screen
{
    public:
        Screen();

        void checkForInput();
        void renderStart();
        void renderEnd();
        int getSelected();
        virtual ~Screen();
    protected:
    private:
    const Uint8 *key = NULL;
    std::stringstream tempText;
    int x = 0;
    int y = 0;
    int selected = 0;
    Texture timerText;
    Texture fpsText;
};

#endif // SCREEN_H
