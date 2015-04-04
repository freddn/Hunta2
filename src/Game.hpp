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

//#include "Character.hpp"
//#include "Item.hpp"
//#include "Enemy.hpp"

/*
 * Game class. Contains game-loop. State of the game. Init of map/data.
 * This class holds alot of important game related objects.
 */
namespace game
{
    /* Will init the needed states and then start the game-loop. */
    void start();
    /* Initiates SDL, creates a window, buffer and so on. */
    bool init_game();
    /* Quit SDL and deallocate stuff. */
    void close();

    /* The different states of the game. */
    enum State {MAINMENU=0,INGAME=1,PAUSED=2,GAMEOVER=3, EDITOR=4};
    /* Some tiles.(used in the editor) */
    enum Selected {GRASS,GROUND,WATER};
    enum Direction {NORTH,SOUTH,EAST,WEST};
    /* Different entity types. */
    enum EntityGroup : std::size_t
    {
        PLAYER,
        ITEM,
        ENEMY,
        ENVIRONMENT
    };
    /* Getters. */
    SDL_Event *getEvent();
    SDL_Rect *getOffset();
    SDL_Rect *getRect();
    SDL_Rect *getBackground();
    SDL_Window *getGWindow();
    SDL_Renderer *getRenderer();
    SDL_Texture *getBuffer();
    SDL_Color getText_color();

    TTF_Font * getFont();

    int getCurrent_state();
    MapClass *getTextureMap();
    std::map<int,Texture*> *getTexture_map();
    int getWidth();
    int getT_width();
    int getHeight();
    int getT_height();
    int getMouseX();
    int getMouseY();
    int getMaxFPS();

    bool getHasChanged();
    float getAvgFPS();
    LTimer getTimer();

    bool inventoryIsDisplayed();
    void showInventory();
    void hideInventory();

    /* Setters. */
    void setHasChanged(bool boolean);
    void setTexture_map(std::map<int,Texture*> temp_map);
    void setBuffer(SDL_Texture * temp);
    void setCurrent_state(int temp);
    void setRectX(int x);
    void setMouseX(int x);
    void setMouseY(int y);
    void setRunning(bool boolean);
}


#endif // GAME_H
