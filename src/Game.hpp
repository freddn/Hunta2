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

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <map>

#include "LTimer.hpp"
#include "Tile.hpp"
#include "Editor.hpp"
#include "InGame.hpp"
#include "MapClass.hpp"
#include "MainMenu.hpp"

//#include "Character.hpp"
//#include "Item.hpp"
//#include "Enemy.hpp"

/*
 * Game class. Contains game-loop. State of the game. Init of map/data.
 * This class holds alot of important game related objects.
 */
namespace game {
    /* Will init the needed states and then start the game-loop. */
    void start();
    /* Initiates SDL, creates a window, buffer and so on. */
    bool init_game();
    /* Quit SDL and deallocate stuff. */
    void close();

    /* The different states of the game. */
    enum State {MAINMENU,INGAME,PAUSED,GAMEOVER, EDITOR};
    /* Some tiles.(used in the editor) */
    enum Selected {GRASS,GROUND,WATER};
    enum Direction {NORTH,SOUTH,EAST,WEST};
    /* Different entity types. */
    enum EntityGroup : std::size_t {PLAYER, ITEM, ENEMY, ENVIRONMENT,PROJECTILE};
    /* Getters. */
    SDL_Event *getEvent();
    SDL_Rect *getOffset();
    SDL_Rect *getRect();
    SDL_Rect *getBackground();
    SDL_Window *getGWindow();
    SDL_Renderer *getRenderer();
    SDL_Texture *getBuffer();
    SDL_Color *getText_color();

    TTF_Font * getFont();

    int getCurrent_state();
    MapClass *getTextureMapObject();
    std::map<int,Texture*> *getTextureMap();
    int getWidth();
    int getTWidth();
    int getHeight();
    int getTHeight();
    int getMouseX();
    int getMouseY();
    int getMaxFPS();

    bool getHasChanged();
    float getAvgFPS();
    LTimer* getTimer();

    /* Setters. */
    void setHasChanged(bool boolean);
    void setTextureMap(std::map<int,Texture*> *temp_map);
    void setBuffer(SDL_Texture *temp);
    void setCurrent_state(int temp);
    void setRectX(int x);
    void setMouseX(int x);
    void setMouseY(int y);
    void setRunning(bool boolean);
}


#endif // GAME_H
