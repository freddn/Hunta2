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
#include "Inventory.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include "Character.hpp"

#include "EntitySystem.hpp"
#include "EntityCreator.hpp"

using namespace EntitySystem;

/**
 * This is the game-state of the game. Here we draw all game-related things
 * on the screen and deal with all input and events related to the game itself.
 */
struct InGame : public Screen {
public:
    InGame();

    /**
     *
     */
    void init();

    /**
     *
     */
    void update();

    /**
     *
     */
    void draw();

    /**
     *
     */
    void displayInventory(bool);
    ~InGame();
private:
    bool showInventory = false;

    Inventory inv{445,150};
    int buf = 0;
    EntityCreator creator;
    EntityManager inGameManager;
    Item stick_T;
    Position playerPos;

    const Uint8 *key;
};

#endif // INGAME_H
