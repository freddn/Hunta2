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
#include "../components/Button.hpp"

/* This class represents the main menu.
 * TODO Implement a settings screen, save game, and load game screen.
 * TODO Also implement an ingame menu where you can save quit or go to settings.
 */
struct MainMenu : public Screen {
public:
    MainMenu();

    /**
     * Initiate all buttons and textures.
     */
    void init();

    /**
     * Update menu items.
     */
    void update();

    /**
     * Draws all textures in the menu and background.
     */
    void draw();

    ~MainMenu();
private:
    /* Textures of the main menu */
    Texture frame;
    Texture background;
    SDL_Rect backgroundRect;
    /* Button specific rect and booleans */
    Button newGame;
    Button loadGame;
    Button settings;
    Button quit;
};

#endif // MAINMENU_H
