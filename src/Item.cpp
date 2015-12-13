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

#include "Item.hpp"


Item::Item(int id) {
    itemID = id;
}

Item::Item(int id, bool ground) {
    onGround = ground;
    itemID = id;
}

Item::Item(int id, bool ground, int amt) {
    onGround = ground;
    itemID = id;
    amount = amt;
}

Item::~Item() {
    //dtor
}

int Item::getID() {
    return itemID;
}
int Item::getAmount() {
    return amount;
}

