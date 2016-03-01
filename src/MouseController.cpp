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

#include "MouseController.hpp"
#include "Texture.hpp"
#include "Shape.hpp"

MouseController::MouseController() {
    btn_state[LEFT_BTN] = STATE_NONE;
    btn_state[RIGHT_BTN] = STATE_NONE;
}

MouseController::~MouseController() {
}

/*
 * Update mouse related variables.
 */
void MouseController::update(SDL_Event *e) {
    /* If the mouse is moved, update the variables tracking the position. */
    if(e->type == SDL_MOUSEMOTION) {
        mouseX = e->motion.x;
        mouseY = e->motion.y;
    }

    /* If the mouse button is held down, set the state to STATE_DOWN.
     * When the mouse button is released, set the state to STATE_UP if it has
     * previously been STATE_DOWN. */
    if(e->type == SDL_MOUSEBUTTONDOWN) {
        if(e->button.button == SDL_BUTTON_LEFT) {
            btn_state[LEFT_BTN] = STATE_DOWN;
        } else if(e->button.button == SDL_BUTTON_RIGHT) {
            btn_state[RIGHT_BTN] = STATE_DOWN;
        }
    } else if(e->type == SDL_MOUSEBUTTONUP) {
        if(e->button.button == SDL_BUTTON_LEFT) {
            if(btn_state[LEFT_BTN] == STATE_DOWN) {
                btn_state[LEFT_BTN] = STATE_UP;
            }
        } else if(e->button.button == SDL_BUTTON_RIGHT) {
            if(btn_state[RIGHT_BTN] == STATE_DOWN) {
                btn_state[RIGHT_BTN] = STATE_UP;
            }
        }
    }
}

/*
 * Clear the mouse state.
 *
 * We only want the STATE_UP to be valid for one update because it is supposed
 * to represent a button release.
 */
void MouseController::clear() {
    if(btn_state[LEFT_BTN] == STATE_UP) {
        btn_state[LEFT_BTN] = STATE_NONE;
    }

    if(btn_state[RIGHT_BTN] == STATE_UP) {
        btn_state[RIGHT_BTN] = STATE_NONE;
    }
}

void MouseController::setMouseX(int x) {
    mouseX = x;
}

void MouseController::setMouseY(int y) {
    mouseY = y;
}

int MouseController::getMouseX() {
    return mouseX;
}

int MouseController::getMouseY() {
    return mouseY;
}

bool MouseController::leftReleased() {
    if(btn_state[LEFT_BTN] == STATE_UP)
        return true;
    return false;
}

bool MouseController::rightReleased() {
    if(btn_state[RIGHT_BTN] == STATE_UP)
        return true;
    return false;
}
