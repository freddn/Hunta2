#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.hpp"

class MainMenu : public Screen
{
    public:
        MainMenu();

        void checkForInput();
        void render();

        virtual ~MainMenu();
    protected:
    private:
};

#endif // MAINMENU_H
