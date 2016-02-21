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

#ifndef INGAME_H
#define INGAME_H

#include <memory>
#include <vector>

#include "TextInputBox.hpp"
#include "Screen.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

/**
 * This is the game-state of the game. Here we draw all game-related things
 * on the screen and deal with all input and events related to the game itself.
 */
struct InGame : public Screen {
public:
    InGame();

    /**
     * Not so much here at the moment, maby init charater/load player data and such..
     * Will call Screen::init()
     */
    void init();

    /**
     * Update maps and everything ingame.
     * Will call Screen::update()
     */
    void update();
    void updateEvents(SDL_Event *event);
    bool takingInput();

    /**
     * Draw maps and everything ingame.
     * Will call Screen::draw()
     */
    void draw();

    /**
     * A temporary user interface with some player information(hp, level, exp ..)
     * Drawn in the function draw() and the text is updated here.
     * TODO Implement a user interface with buttons and images.
     */
    void update_interface();

    /**
     * TODO Remove? Called in another location
     */
    void displayInventory(bool);

    ~InGame();
private:
    bool showInventory = false;

    int buf = 0;
    Texture tInterface;
    EntityManager inGameManager;
    std::stringstream tempText;
    TextInputBox textBox;
    Texture prompt;
    Texture nameText;
    Texture lvText;
    Texture hpText;
    Texture expText;
    Texture atkText;
    Texture defText;
    int updateFreq = 0;
    const Uint8 *key = 0;
};

#endif // INGAME_H
