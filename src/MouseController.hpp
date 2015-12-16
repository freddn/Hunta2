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

#include "EntitySystem.hpp"
#include "Position.hpp"
#include <SDL2/SDL.h>

enum {
    STATE_NONE,
    STATE_DOWN,
    STATE_UP
};

class MouseController : EntitySystem::Component {
public:
    MouseController();
    MouseController(bool x, bool y);
    virtual ~MouseController();

    void init();
    void update(SDL_Event event);
    void clear();

    void setMouseX(int x);
    void setMouseY(int y);

    int getMouseX();
    int getMouseY();

    bool leftReleased();

    bool rightMouseButton();
    bool leftMouseButton();

    void setRMouseBtn(bool rMouse);
    void setLMouseBtn(bool lMouse);
    void setCenteredX(bool c);
    void setCenteredY(bool c);

private:
    Position *position = nullptr;

    int state = STATE_NONE;

    bool rMouseBtn = false;
    bool lMouseBtn = false;
    bool controllX = true;
    bool controllY = true;

    int width = 32;
    int height = 32;

    int mouseX = 0;
    int mouseY = 0;
};

#endif /* MOUSECONTROLLER_HPP */
