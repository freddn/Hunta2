#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.hpp"

/* This class represents the main menu. */
struct MainMenu : public Screen
{
    public:
        MainMenu();

        void init();
        void update();
        void draw();

        ~MainMenu();
    private:
        Texture frame;
        SDL_Texture *startGame;
        SDL_Rect button;
};

#endif // MAINMENU_H
