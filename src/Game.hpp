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
//#include "Character.hpp"
#include "Tile.hpp"
//#include "Item.hpp"
#include "Editor.hpp"
#include "InGame.hpp"
#include "MapClass.hpp"

//#include "Inventory.hpp"

namespace game
{
    void start();
    bool init_game();
    void close();

    enum State {MAINMENU=0,INGAME=1,PAUSED=2,GAMEOVER=3, EDITOR=4};
    enum Selected {GRASS,GROUND,WATER};

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
