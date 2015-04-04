#include "MainMenu.hpp"

MainMenu::~MainMenu()
{

}
void MainMenu::init()
{
    std::cout << " - MainMenu::init() ..."<<std::endl;
}

void MainMenu::draw()
{
    Screen::renderStart();
    /* Render the menu */



    Screen::renderEnd();

}

void MainMenu::update()
{



    Screen::update();
}


