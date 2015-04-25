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

#include "Screen.hpp"
#include "Game.hpp"


Screen::~Screen()
{
    //dtor
    fpsText.free();
    timerText.free();
}

void Screen::init()
{
}

void Screen::update()
{
    key = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(game::getEvent()) != 0)
    {
        if(game::getEvent()->type == SDL_QUIT) { game::setRunning(false); }
        else if(game::getEvent()->type == SDL_KEYDOWN)
        {
            if(key[SDL_SCANCODE_ESCAPE]) { game::setRunning(false); }
            else if(key[SDL_SCANCODE_S])
            {
                if (game::getTimer().isStarted()) { game::getTimer().stop(); }
                else { game::getTimer().start(); }
            }
            else if(key[SDL_SCANCODE_P])
            {
                if(game::getTimer().isPaused()) { game::getTimer().unpause(); }
                else { game::getTimer().pause(); }
            }

            else if(key[SDL_SCANCODE_2]) { game::setCurrent_state(game::MAINMENU); }
            else if(key[SDL_SCANCODE_1])
            {
                if(game::getCurrent_state() == game::EDITOR)
                {
                    /* Save as .. */
                    //std::cout << "save map size: " << textures.size() << std::endl;
                    game::getOffset()->x = game::getWidth();
                    game::getOffset()->y = game::getHeight();
                    game::getTextureMap()->saveMap(*game::getTexture_map(),"data/map2",40,30);
                    game::getTextureMap()->loadMap("data/map2");
                    game::setTexture_map(game::getTextureMap()->getMap());
                    //std::cout << "loaded map size: " << textures.size() << std::endl;
                }
                game::setCurrent_state(game::INGAME);
                // LOAD MAP

            }
            else if(key[SDL_SCANCODE_3]) { game::setCurrent_state(game::PAUSED); }
            else if(key[SDL_SCANCODE_0]) { game::setCurrent_state(game::GAMEOVER); }
            else if(key[SDL_SCANCODE_4])
            {
                game::setCurrent_state(game::EDITOR);
                // LOAD MAP.
                // SAVE MAP.
            }
            else if(key[SDL_SCANCODE_I] && game::getCurrent_state() == game::INGAME)
            {
                if(!game::inventoryIsDisplayed())
                    game::showInventory();
                else
                    game::hideInventory();
            }

        }
        else if(game::getEvent()->type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&x,&y);
            game::setMouseX(x);
            game::setMouseY(y);
        }
        else if(game::getEvent()->type == SDL_MOUSEBUTTONDOWN)
        {
            if(game::getCurrent_state() == game::EDITOR)
            {
                if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                {
                    std::cerr << selected;
                    if(selected == game::GROUND)
                        selected = game::WATER;
                    else if(selected == game::WATER)
                        selected = game::GRASS;
                    else// if(selected == game::GRASS)
                        selected = game::GROUND;
                }
            }
        }
    }


}

void Screen::draw()
{

}

void Screen::renderStart()
{
    SDL_RenderClear(game::getRenderer());



}

void Screen::renderEnd()
{

    tempText.str("");
    tempText << "FPS: " << game::getAvgFPS();
    fpsText.loadFromText(game::getRenderer(),tempText.str() ,game::getText_color(),game::getFont());

    tempText.str("");
    tempText << "Time: " << (game::getTimer().getTicks() / 1000.f);
    timerText.loadFromText(game::getRenderer(),tempText.str() ,game::getText_color(),game::getFont());

    fpsText.render(game::getRenderer(),200,30,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);
    timerText.render(game::getRenderer(),350,30,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);


    SDL_RenderPresent(game::getRenderer());
}



int Screen::getSelected()
{
    return selected;
}
