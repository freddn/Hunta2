#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.hpp"

struct MainMenu : public Screen
{
    public:
        MainMenu();
        void init() override;
        void update() override;
        void draw() override;

        ~MainMenu() override;
    protected:
    private:
};

#endif // MAINMENU_H
