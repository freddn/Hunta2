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

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.hpp"

/* This class represents the main menu.
 * TODO Implement a settings screen, save game, and load game screen.
 * TODO Also implement an ingame menu where you can save quit or go to settings.
 */
struct MainMenu : public Screen {
public:
    MainMenu();

    /**
     * Will load all textures
     */
    void init();

    /**
     * Check for mouse movement and clicks on the menu items.
     */
    void update();

    /**
     * Draws all textures in the menu and background.
     */
    void draw();

    bool mouseOverRect(SDL_Rect r);
    ~MainMenu();
private:
    /* Textures of the main menu */
    Texture frame;
    Texture text;
    Texture buttonBg;
    Texture background;

    SDL_Rect backgroundRect;
    SDL_Rect button;

    /* Button specific rect and booleans */
    SDL_Rect newGame;
    bool newGameHoover = false;
    bool newGamePressed = false;

    SDL_Rect loadGame;
    bool loadGameHoover = false;
    bool loadGamePressed = false;

    SDL_Rect settings;
    bool settingsHoover = false;
    bool settingsPressed = false;

    SDL_Rect quitGame;
    bool quitGameHoover = false;
    bool quitGamePressed = false;
};

#endif // MAINMENU_H
