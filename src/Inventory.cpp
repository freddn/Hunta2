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

#include "Inventory.hpp"

#include "Game.hpp"


using namespace EntitySystem;

Inventory::Inventory(int x, int y) : sizeX(x), sizeY(y)
{

}


Inventory::~Inventory()
{

}

void Inventory::init()
{
    frame.loadFromFile(game::getRenderer(),"data/frame.png");
    inv_bg = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, sizeX*32, sizeY*32);
    SDL_SetRenderTarget(game::getRenderer(),inv_bg);

    //SDL_Rect clipRect = {0,0,32,32};
    //SDL_Rect destRect = {0,0,32,32};

    for(int y = 0;y<sizeY;y++)
    {
        for(int x = 0;x<sizeX;x++)
        {
            if(x == 0)
            {
                //SDL_RenderCopy(game::getRenderer(),frame,NULL,NULL);
                //frame.render(game::getRenderer(),NULL,0,NULL,SDL_FLIP_NONE);
            }
        }
    }

    SDL_SetRenderTarget(game::getRenderer(),NULL);
}

void Inventory::loadInventory()
{

}

void Inventory::draw()
{
    frame.render(game::getRenderer(),(SDL_Rect*)NULL,0,NULL,SDL_FLIP_NONE);
}

void Inventory::update()
{
    //check if item is dropped or if new items arrive
}




