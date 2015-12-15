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

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Texture.hpp"
#include "EntitySystem.hpp"
#include "LuaInterface.hpp"
#include "ItemManager.hpp"

using namespace EntitySystem;

/*
 * Inventory. Load items from file. Save items to file.
 */
class Inventory : Component {
public:
    Inventory(int x, int y);
    ~Inventory();

    void init();
    void update();
    void draw();
    void loadInventory();

    int addItem(int id, int amount, int x, int y);
    void addItem(int id, int amount);
    void deleteItem(int id, int amount, int x, int y);

    void saveInventory();
    void renderItems();

private:
    LuaInterface l_interface;
    SDL_Texture *inv_bg{nullptr};
    Texture frame;
    Texture text;
    int sizeX = 6;
    int sizeY = 9;
    int itemCount = 0;
    SDL_Rect inventoryRect;
    Texture amount;
    std::string inventoryLocation;
    std::map<int,ItemData> items;
    std::map<int,int> stackedItems;
};

#endif /* INVENTORY_HPP */
