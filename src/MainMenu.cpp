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
    button.w = 32*8;
    button.h = 32*2;
    startGame = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_TARGET, button.w, button.h);

    if(startGame == 0)
    {
        std::cerr << "Failed to create Start Game button" << std::endl;
    }


    buildButton();


}

void MainMenu::draw()
{
    Screen::renderStart();
    /* Render the menu */
    button.y = 100;
    button.x = 32*6;
    //startGame.render(game::getRenderer(),0,0,NULL,SDL_FLIP_NONE,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&button);

    button.y += 80;
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&button);
    button.y += 80;
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&button);
    button.y += 80;
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&button);



    Screen::renderEnd();

}

void MainMenu::update()
{



    Screen::update();
}

void MainMenu::buildButton()
{
    SDL_Rect temp;
    temp.x = 0;
    temp.y = 0;
    temp.w = 32;
    temp.h = 32;

    SDL_SetRenderTarget(game::getRenderer(),startGame);
    //frame.render(game::getRenderer(),x,y,&temp,0,NULL,SDL_FLIP_NONE);
    for(int i = 0;i<=(button.h / 32);i++)
    {
        for(int j = 0;j<=(button.w / 32);j++)
        {
            if(i == 0 && j == 0)
            {
                temp.x = 0;
                temp.y = 0;

            }
            else if(i == ((button.h-32)/32) && j == 0)
            {
                temp.x = 0;
                temp.y = 32;
            }
            else if(i == 0 && j == ((button.w-32)/32))
            {
                temp.x = 64;
                temp.y = 0;
            }
            else if(i == ((button.h-32)/32) && j == ((button.w-32)/32))
            {
                temp.x = 64;
                temp.y = 32;
            }
            else if(i == 0)
            {
                temp.x = 32;
                temp.y = 0;
            }
            else if(i == ((button.h-32)/32))
            {
                temp.x = 32;
                temp.y = 32;
            }
            else if(j == 0)
            {
                temp.x = 0;
                temp.y = 10;
            }
            else if(j == ((button.w-32)/32))
            {
                temp.x = 64;
                temp.y = 10;
            }
            else
            {
                temp.x = 32;
                temp.y = 10;
            }
            frame.render(game::getRenderer(),j*32,i*32,&temp,0,NULL,SDL_FLIP_NONE);
        }
    }
    SDL_SetRenderTarget(game::getRenderer(),NULL);
}


