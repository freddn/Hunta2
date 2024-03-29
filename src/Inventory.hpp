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

#include "components/Texture.hpp"
#include "scripting/LuaInterface.hpp"
#include "components/ItemManager.hpp"

#define INVENTORY_WIDTH 5
#define INVENTORY_HEIGHT 4

/*
 * Inventory. Load items from file. Save items to file.
 */
class Inventory {
public:
    Inventory(int x, int y);
    ~Inventory();

    void init();
    void update();
    void draw();
    void loadInventory();

    int addItem(int id, int amount, int x, int y);
    int addItem(int id, int amount);
    void deleteItem(int id, int amount, int x, int y);

    void saveInventory();
    void renderItems();

private:
    LuaInterface *l_interface;
    SDL_Texture *inv_bg{nullptr};
    Texture frame;
    Texture textBox;
    int itemCount = 0;
    SDL_Rect inventoryRect;
    Texture amount;
    std::string inventoryLocation;
    std::map<int,ItemData> items;
    std::map<int,int> stackedItems;
};

#endif /* INVENTORY_HPP */
