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

/* This class represents the main menu. */
struct MainMenu : public Screen {
public:
    MainMenu();

    void init();
    void update();
    void draw();
    void buildButton();
    bool mouseOverRect(SDL_Rect r);
    ~MainMenu();
private:
    Texture frame;
    Texture text;
    SDL_Texture *buttonBg{nullptr};
    std::stringstream tempText;
    SDL_Rect button;
    SDL_Rect newGame;
    SDL_Rect loadGame;
    SDL_Rect settings;
    SDL_Rect quitGame;

};

#endif // MAINMENU_H
