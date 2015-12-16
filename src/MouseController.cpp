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
}

MouseController::MouseController(bool x, bool y) {
    controllX = x;
    controllY = y;
}

MouseController::~MouseController() {
}

void MouseController::init() {
    position = &entity->getComponent<Position>();
    if(entity->hasComponent<Texture>()) {
        width = entity->getComponent<Texture>().getWidth();
        height = entity->getComponent<Texture>().getHeight();
    } else if(entity->hasComponent<Shape>()) {
        width = entity->getComponent<Shape>().getWidth();
        height = entity->getComponent<Shape>().getHeight();
    }
    setCenteredX(true);
}

/*
 * Update mouse related variables.
 */
void MouseController::update(SDL_Event event) {
    /* If the mouse is moved, update the variables tracking the position. */
    if(event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }

    /* If the mouse button is held down, set the state to STATE_DOWN.
     * When the mouse button is released, set the state to STATE_UP if it has
     * previously been STATE_DOWN. */
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        state = STATE_DOWN;
    } else if(event.type == SDL_MOUSEBUTTONUP) {
        if(state == STATE_DOWN) {
            state = STATE_UP;
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
    if(state == STATE_UP) {
        state = STATE_NONE;
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
    if(state == STATE_UP)
        return true;
    return false;
}

bool MouseController::rightMouseButton() {
    return rMouseBtn;
}

bool MouseController::leftMouseButton() {
    return lMouseBtn;
}

void MouseController::setRMouseBtn(bool rMouse) {
    rMouseBtn = rMouse;
}

void MouseController::setLMouseBtn(bool lMouse) {
    lMouseBtn = lMouse;
}

void MouseController::setCenteredX(bool c) {
    if(!c)
        width = 0;
}

void MouseController::setCenteredY(bool c) {
    if(!c)
        height = 0;
}
