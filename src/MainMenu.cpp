#include "MainMenu.hpp"
#include "Game.hpp"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}
void MainMenu::init()
{
    std::cout << " - MainMenu::init() ..."<<std::endl;
    frame.loadFromFile(game::getRenderer(),"data/frame.png");

    button.x = 50;
    button.y = 50;
    button.w = 32*10;
    button.h = 32*3;
    startGame = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_TARGET, button.w, button.h);

    if(startGame == 0)
    {
        std::cerr << "Failed to create Start Game button" << std::endl;
    }
}

void MainMenu::draw()
{
    Screen::renderStart();
    /* Render the menu */
    button.y = 50;
    //startGame.render(game::getRenderer(),0,0,NULL,SDL_FLIP_NONE,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&button);



    Screen::renderEnd();

}

void MainMenu::update()
{



    Screen::update();
}


