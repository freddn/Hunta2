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

#include "Inventory.hpp"
#include "Game.hpp"
#include "HelperFunctions.hpp"

#include <iostream>

using namespace EntitySystem;

Inventory::Inventory(int x, int y) {
    inventoryRect.x = x;
    inventoryRect.y = y;
}

Inventory::~Inventory() {}

void Inventory::init() {
    frame.loadFromFile("data/inventory.png");

    inventoryLocation = "data/savedata/" +
        game::getPlayerController()->getName() + "_inventory.lua";

    text.loadFromText("Inventory", *game::getTextColor(), game::getFont());

    l_interface.initLua();

    if(!l_interface.loadFile(inventoryLocation.c_str())) {
        HelperFunctions::log(HelperFunctions::ERROR,
                             "Failed to Load LoadInventory.lua");
    }

    if(!l_interface.loadFile("src/InventoryFunctions.lua")) {
        HelperFunctions::log(HelperFunctions::ERROR,
                             "Failed to Load InventoryFunctions.lua");
    }
}

void Inventory::loadInventory() {
    l_interface.loadFile(inventoryLocation.c_str());
}

int Inventory::addItem(int id, int amount) {
    ItemData data = game::getItemManager()->getItem(id);

    for(int y=0;y<INVENTORY_HEIGHT;y++) {
        for(int x=0;x<INVENTORY_WIDTH;x++) {
            int index = x+(y*INVENTORY_WIDTH);
            if (items.find(index) != items.end()) {
                if (items.at(index).id >= 200 && items.at(index).id == id) {//TODO check stacksize?
                    int amt = 1;
                    if (stackedItems.find(index) != stackedItems.end()) {
                        amt = stackedItems.at(index);
                        stackedItems.erase(index);
                    } else {
                        items.emplace(std::pair<int, ItemData>(index, data));
                    }
                    /* Increase the stack by 1. */
                    stackedItems.emplace(std::pair<int, int>(index, amt + amount));
                    return 0;
                }
            }
        }
    }


    for(int y=0;y<INVENTORY_HEIGHT;y++) {
        for(int x=0;x<INVENTORY_WIDTH;x++) {
            int index = x + (y * INVENTORY_WIDTH);
            if (items.find(index) == items.end()) {
                items.emplace(std::pair<int, ItemData>(index, data));
                if(amount > 1) // TODO Check stacksize?
                    stackedItems.emplace(std::pair<int, int>(index, amount));
                return 0;
            }
        }
    }
    return -1;
}

int Inventory::addItem(int id, int amount, int x, int y) {
    /* We can only carry less than 20 items. */
    if(itemCount >= 20) {
        return -1;
    }

    ItemData data = game::getItemManager()->getItem(id);
    int index = x + (y*INVENTORY_WIDTH);
    if(items.find(index) != items.end()) {
        if(items.at(index).id >= 200 && items.at(index).id ==id) {
            int amt = 1;

            if(stackedItems.find(index) != stackedItems.end()) {
                amt = stackedItems.at(index);
                stackedItems.erase(index);
            } else {
                items.emplace(std::pair<int,ItemData>(index, data));
            }

            /* Increase the stack by 1. */
            stackedItems.emplace(std::pair<int,int>(index, amt+amount));
            return 0;
        }
    } else {
        items.emplace(std::pair<int,ItemData>(index, data));
        return 0;
    }

    return -1;
}

void Inventory::deleteItem(int id,int amount,int x,int y) {
    l_interface.deleteItem(inventoryLocation.c_str(), id,amount,x,y);
    items.erase(y*INVENTORY_WIDTH+x);
}

/*
 * Draws the frame, text, and all the items.
 */
void Inventory::draw() {
    frame.render(inventoryRect.x, inventoryRect.y, nullptr);
    text.render(inventoryRect.x+20, inventoryRect.y+20, nullptr);
    renderItems();
}

void Inventory::renderItems() {
    SDL_Rect srcRect{0, 0, 32, 32};

    for(auto item : items) {
        SDL_Rect itemRect{16+inventoryRect.x+((item.first%INVENTORY_WIDTH)*32)+
                          (item.first%INVENTORY_WIDTH)*2,
                          170+inventoryRect.y+
                          (((item.first-item.first%INVENTORY_WIDTH)/INVENTORY_WIDTH)*32)+
                          ((item.first-item.first%INVENTORY_WIDTH)/INVENTORY_WIDTH)*2,
                          32, 32};

        SDL_RenderCopy(game::getRenderer(),
                       game::getTextureManager()->getTexture(item.second.img),
                       &srcRect, &itemRect);

        if(stackedItems.find(item.first) != stackedItems.end()) {
            std::stringstream amt;
            amt.str("");
            amt << stackedItems.at(item.first);
            amount.loadFromText(amt.str(), *game::getTextColor(),
                                game::getDmgFont());
            amount.render(itemRect.x,itemRect.y,nullptr);
            // TODO Print amt of items
        }
    }
}

/*
 * Check if items are dropped or if new items are picked up.
 */
void Inventory::update() {
    /*if (game::getMouseController()->leftReleased()) {
        std::cout << "Mouse released at " <<
                     game::getMouseController()->getMouseX()-inventoryRect.x <<
                     "," <<
                     game::getMouseController()->getMouseY()-inventoryRect.y << std::endl;
    }
    */
    /* TODO: Check if the mouse has been released above an item, if so,
     * perhaps use the item. */
}
