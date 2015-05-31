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

#include "Editor.hpp"


Editor::Editor() {
    //ctor

    r_select = SDL_CreateRGBSurface(0,36,36,32,0,0,0,0);
    SDL_FillRect(r_select,NULL,SDL_MapRGB(r_select->format,255,0,0));
    rect_select = SDL_CreateTextureFromSurface(game::getRenderer(),r_select);
    //

    rground.x = 0;
    rground.y = 2;
    rground.w = 32;
    rground.h = 32;

    rwater.x = 32*2;
    rwater.y = 2;
    rwater.w = 32;
    rwater.h = 32;

    rgrass.x = 32*4;
    rgrass.y = 2;
    rgrass.w = 32;
    rgrass.h = 32;

    sel.y = 0;
    sel.w = 36;
    sel.h = 36;
}

Editor::~Editor() {
    //dtor
    SDL_FreeSurface(r_select);
    SDL_DestroyTexture(rect_select);
}



void Editor::draw() {
    Screen::renderStart();

    game::setRectX(game::getMouseX()-(game::getMouseX()%32)); // which is faster/better
    game::getRect()->y = game::getMouseY()-(game::getMouseY()%32); // ??

    switch(selected) {
    case(game::GRASS):
        sel.x = rgrass.x -2;
        break;
    case(game::GROUND):
        sel.x = rground.x -2;
        break;
    case(game::WATER):
        sel.x = rwater.x -2;
        break;
    }

    if(game::getHasChanged()) {
        SDL_SetRenderTarget(game::getRenderer(),game::getBuffer());
        for(auto iter = game::getTextureMap()->begin();
            iter != game::getTextureMap()->end();iter++) {
            if(((Texture*)iter->second)->getX() > -32 &&
                ((Texture*)iter->second)->getX() < game::getBackground()->w &&
                ((Texture*)iter->second)->getY() > -32 &&
                ((Texture*)iter->second)->getY() < game::getBackground()->h) {

                ((Texture*)iter->second)->render(game::getRenderer(),(SDL_Rect*)NULL,
                                                    (double)0.0,NULL,SDL_FLIP_NONE);
            }
        }
        SDL_SetRenderTarget(game::getRenderer(),NULL);
        game::setHasChanged(false);
    }
    SDL_RenderCopy( game::getRenderer(),game::getBuffer(),
                    game::getOffset(),game::getBackground());
    SDL_RenderCopy(game::getRenderer(),rect_select,NULL,&sel);

    game::getTextureMapObject()->getGroundTile()->render( game::getRenderer(),rground.x,
                                                    rground.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);
    game::getTextureMapObject()->getWaterTile()->render(game::getRenderer(),rwater.x,
                                                    rwater.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);
    game::getTextureMapObject()->getGrassTile()->render(  game::getRenderer(),rgrass.x,
                                                    rgrass.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);

    //CLICK EVENT..
    Screen::renderEnd();
}

void Editor::update() {
    key = SDL_GetKeyboardState(NULL);
    if(key[SDL_SCANCODE_UP]) {
        if(game::getOffset()->y > 0)
            game::getOffset()->y = game::getOffset()->y - 4;
    } else if(key[SDL_SCANCODE_DOWN]) {
        if(game::getOffset()->y < game::getHeight())
            game::getOffset()->y = game::getOffset()->y + 4;
    } else if(key[SDL_SCANCODE_LEFT]) {
        if(game::getOffset()->x > 0)
            game::getOffset()->x = game::getOffset()->x - 4;
    } else if(key[SDL_SCANCODE_RIGHT]) {
        if(game::getOffset()->x < game::getWidth())
            game::getOffset()->x = game::getOffset()->x + 4;
    }

    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        int tempX = (game::getMouseX()+game::getOffset()->x)-((game::getMouseX()+game::getOffset()->x)%32);
        int tempY = (game::getMouseY()+game::getOffset()->y)-((game::getMouseY()+game::getOffset()->y)%32);
        int index = (tempX/32)+((tempY/32)*40);

        if(game::getTextureMap()->count(index) < 2)
        {
            if(game::getTextureMap()->count(index) != 0)
                game::getTextureMap()->erase(index);

            Texture *temp;

            switch(selected) {
            case game::GROUND:
                temp = game::getTextureMapObject()->getGroundTile()->clone();
                break;
            case game::WATER:
                temp = game::getTextureMapObject()->getWaterTile()->clone();
                break;
            case game::GRASS:
                temp = game::getTextureMapObject()->getGrassTile()->clone();
                break;
            };

            temp->setXRect(tempX);
            temp->setYRect(tempY);
            game::getTextureMap()->insert(std::pair<int,Texture*>(index,temp));

            game::setHasChanged(true);
        }
    }
    else if(game::getEvent()->type == SDL_MOUSEBUTTONDOWN) {
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            //std::cerr << selected;
            if(!selBool) {
                selBool = true;
                if(selected == game::GROUND)
                    selected = game::WATER;
                else if(selected == game::WATER)
                    selected = game::GRASS;
                else// if(selected == game::GRASS)
                    selected = game::GROUND;
            }
        }
    }
    else
        selBool = false;

    Screen::update();
}




