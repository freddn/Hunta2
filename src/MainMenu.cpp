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

    button = {50,50,32*8,32*2};

    newGame =  {32*6, 100,button.w,button.h};
    loadGame = {32*6, 180,button.w,button.h};
    settings = {32*6, 260,button.w,button.h};
    quitGame = {32*6, 340,button.w,button.h};

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
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&newGame);
    text.loadFromText(game::getRenderer(),"New Game" ,
                        game::getText_color(),game::getFont());
    text.render(game::getRenderer(),newGame.x+20,newGame.y+18,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&loadGame);
    text.loadFromText(game::getRenderer(),"Load Game" ,
                        game::getText_color(),game::getFont());
    text.render(game::getRenderer(),loadGame.x+20,loadGame.y+18,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&settings);
    text.loadFromText(game::getRenderer(),"Settings" ,
                        game::getText_color(),game::getFont());
    text.render(game::getRenderer(),settings.x+20,settings.y+18,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(game::getRenderer(),startGame,NULL,&quitGame);
    text.loadFromText(game::getRenderer(),"Quit game" ,
                        game::getText_color(),game::getFont());
    text.render(game::getRenderer(),quitGame.x+20,quitGame.y+18,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);

    Screen::renderEnd();
}

void MainMenu::update()
{
    /* Check if button is pressed. */
    if(game::getEvent()->type == SDL_MOUSEBUTTONDOWN)
    {
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if(mouseOverRect(newGame))
            {
                game::setCurrent_state(game::INGAME);
                std::cerr << "new game\n";
            }
            else if(mouseOverRect(loadGame))
            {
                game::setCurrent_state(game::INGAME);
                std::cerr << "load game\n";
            }
            else if(mouseOverRect(settings))
            {
                std::cerr << "settings\n";
            }
            else if(mouseOverRect(quitGame))
            {
                std::cerr << "quit game\n";
            }
        }
    }

    Screen::update();
}

bool MainMenu::mouseOverRect(SDL_Rect r)
{
    if(game::getMouseX() < r.x+r.w && game::getMouseX() > r.x &&
        game::getMouseY() < r.y+r.h && game::getMouseY() > r.y)
    {
       return true;
    }
    return false;
}

void MainMenu::buildButton()
{
    SDL_Rect temp;
    temp.x = 0;
    temp.y = 0;
    temp.w = 32;
    temp.h = 32;

    SDL_SetRenderTarget(game::getRenderer(),startGame);

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


