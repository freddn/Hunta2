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

#ifndef ITEM_HPP
#define ITEM_HPP

#include "Texture.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

/**
 * The item-class. An item can be picked up if it's on the ground. It will go
 * to the inventory if picked up.
 */
struct Item : Component {
public:
    Item(int id);
    Item(int id, bool ground, EntityManager *manager);
    void init();
    void pickUp();
    void getInfo();
    void draw();
    void update();
    virtual ~Item();
protected:
private:
    int itemID = -1;
    bool onGround = false;
    EntityManager *manager;
};

#endif // ITEM_HPP






