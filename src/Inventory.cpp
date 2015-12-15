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

void Inventory::addItem(int id, int amount) {
    ItemData data = game::getItemManager()->getItem(id);

    for(int i=0;i<12;i++) {
        if(items.find(i) != items.end()) {
            if(items.at(i).id >= 200 && items.at(i).id == id) {
                int amt = 1;
                if(stackedItems.find(i) != stackedItems.end()) {
                    amt = stackedItems.at(i);
                    stackedItems.erase(i);
                } else {
                    items.emplace(std::pair<int,ItemData>(i, data));
                }

                /* Increase the stack by 1. */
                stackedItems.emplace(std::pair<int,int>(i, amt+1));
                return;
            }
        }
    }

    for(int i=0;i<12;i++) {
        if (items.find(i) == items.end()) {
            items.emplace(std::pair<int,ItemData>(i, data));
            return;
        }
    }
}

int Inventory::addItem(int id, int amount, int x, int y) {
    /* We can only carry less than 20 items. */
    if(itemCount >= 20) {
        return -1;
    }

    ItemData data = game::getItemManager()->getItem(id);

    if(items.find(x+(y*3)) != items.end()) {
        if(items.at(x+(y*3)).id >= 200 && items.at(x+(y*3)).id ==id) {
            int amt = 1;

            if(stackedItems.find(x+(y*3)) != stackedItems.end()) {
                amt = stackedItems.at(x+(y*3));
                stackedItems.erase(x+(y*3));
            } else {
                items.emplace(std::pair<int,ItemData>(x+(y*3), data));
            }

            /* Increase the stack by 1. */
            stackedItems.emplace(std::pair<int,int>(x+(y*3), amt+1));
        }
    } else {
        items.emplace(std::pair<int,ItemData>(x+(y*3), data));
    }
    
    return 0;
}

void Inventory::deleteItem(int id,int amount,int x,int y) {
    l_interface.deleteItem(inventoryLocation.c_str(), id,amount,x,y);
    items.erase(y*6+x);
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
        SDL_Rect itemRect{16+inventoryRect.x+((item.first%3)*32)+(item.first%3)*2,
                          170+inventoryRect.y+(((item.first-item.first%3)/3)*32)+
                                  ((item.first-item.first%3)/3)*2,
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
}
