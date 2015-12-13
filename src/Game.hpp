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

#define SCREEN_FPS 60
#define TICKS_PER_FRAME (1000 / SCREEN_FPS)

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTimer.hpp"
#include "MapController.hpp"
#include "Editor.hpp"
#include "TextureManager.hpp"
#include "ItemManager.hpp"
#include "PlayerController.hpp"
#include "UIController.hpp"
#include "EnemyDataController.hpp"

/**
 * Game class. Contains game-loop. State of the game. Init of map/data.
 * This class holds alot of important game related objects.
 */
namespace game {
    /**
     * Will init the needed states and then start the game-loop.
     */
    void start();

    /** Check for SDL events */
    void pollEvents();

    void newGame(std::string nick);

    /** Initiates SDL, creates a window, buffer and so on. */
    bool init_game(bool fullscreen);

    /** Quit SDL and deallocate stuff. */
    void close();

    /** The different states of the game. */
    enum State {    MAINMENU,
                    CHARCREATION,
                    INGAME,
                    PAUSED,
                    GAMEOVER,
                    EDITOR };

    /** Some directions the character can have. */
    enum Direction {    NORTH,
                        SOUTH,
                        WEST,
                        EAST };

    /** Different tiles used by the Editor. */
    enum Selected { GRASS,
                    GROUND,
                    WATER };

    /** Different entity types. */
    enum EntityGroup : std::size_t {    PLAYER,
                                        ITEM,
                                        ENEMY,
                                        ENVIRONMENT,
                                        PROJECTILE,
                                        TILE,
                                        X };

    /** Getters for important game variables/objects. */
    Editor *getEditor();
    SDL_Event *getEvent();
    SDL_Rect *getOffset();
    SDL_Rect *getBackground();
    SDL_Window *getGWindow();
    SDL_Renderer *getRenderer();
    SDL_Texture *getBuffer();
    SDL_Color *getTextColor();
    TTF_Font *getFont();
    TTF_Font * getDmgFont();
    int getCurrentState();
    PlayerController *getPlayerController();
    MapController *getTextureMapController();
    EnemyDataController *getEnemyDataController();
    ItemManager *getItemManager();
    TextureManager *getTextureManager();
    Inventory *getInventory();
    std::shared_ptr<Map> getTextureMap();
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

    /** Setters. */
    void setHasChanged(bool boolean);
    void setTextureMap(std::shared_ptr<Map> temp_map);
    void setBuffer(SDL_Texture *temp);
    void setCurrent_state(int temp);
    void setMouseX(int x);
    void setMouseY(int y);
    void setRunning(bool boolean);
}


#endif // GAME_H
