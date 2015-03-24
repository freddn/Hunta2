#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    //ctor
}

MainMenu::~MainMenu()
{
    //dtor
}



void MainMenu::render()
{
    Screen::renderStart();
    /* Render the menu */



    Screen::renderEnd();

}

void MainMenu::checkForInput()
{



    Screen::checkForInput();
}


