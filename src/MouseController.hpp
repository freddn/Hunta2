/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 * Copyright (C) 2015  Lucas Sköldqvist <frusen@gungre.ch>
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

#ifndef MOUSECONTROLLER_HPP
#define MOUSECONTROLLER_HPP

#include <SDL2/SDL.h>

enum {
    STATE_NONE,
    STATE_DOWN,
    STATE_UP
};

enum {
    LEFT_BTN,
    RIGHT_BTN
};

class MouseController {
public:
    MouseController();
    MouseController(bool x, bool y);
    virtual ~MouseController();

    void init();
    void update(SDL_Event *e);
    void clear();

    void setMouseX(int x);
    void setMouseY(int y);

    int getMouseX();
    int getMouseY();

    bool leftReleased();
    bool rightReleased();

    void setCenteredX(bool c);
    void setCenteredY(bool c);

private:
    /* For left and right button. */
    int btn_state[2];

    int mouseX = 0;
    int mouseY = 0;
};

#endif /* MOUSECONTROLLER_HPP */
