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

#include <iostream>

using namespace EntitySystem;

Inventory::Inventory(int x, int y) {
    inventoryRect.x = x;
    inventoryRect.y = y;

}


Inventory::~Inventory() {}

void Inventory::init() {
    frame.loadFromFile("data/inventory.png");
    inventoryLocation = "data/savedata/"+game::getPlayerController()->getName()+"_inventory.lua";
    //inventoryRect.w = sizeX*32;
    //inventoryRect.h = sizeY*32;
    //inv_bg = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
    //                                SDL_TEXTUREACCESS_TARGET, sizeX*32, sizeY*32);
    //if(inv_bg == 0)
    //    std::cerr << "Failed to create inventory" << std::endl;

    //buildInventory();
    //loadInventory();
    text.loadFromText("Inventory" ,
                      *game::getTextColor(),game::getFont());
    l_interface.initLua();

    if(!l_interface.loadFile(inventoryLocation.c_str()))
        std::cerr << "Failed to Load LoadInventory.lua" << std::endl;

    if(!l_interface.loadFile("src/InventoryFunctions.lua"))
        std::cerr << "Failed to Load InventoryFunctions.lua" << std::endl;
}

void Inventory::loadInventory() {
    l_interface.loadFile(inventoryLocation.c_str());
   // l_interface.loadInventory(inventoryLocation.c_str());
    /// CHANGE TO OTHER FORMAT
    /// Inventoryclass should have a loadItem function and be
    /// accessed by game::getInventory()->loadItem from LuaInterface
    //inventoryItem *items; // = lua_functions::getItems();
    //l_interface.addItem("data/inventory1",12,4,4,6);

    return;
}

int Inventory::addItem(int id,int amount,int x, int y) {
    if(itemCount < 20) {//lua_functions::getItemCount() < 20)
        ItemData data = game::getItemManager()->getItem(id);
        if(items.find(x+y*6) != items.end()) {
            if(items.at(x+y*6).id >= 200 && items.at(x+y*6).id ==id) {
                int amt = 0;
                if(stackedItems.find(x+y*6) != stackedItems.end()) {
                    amt = stackedItems.at(x+y*6);
                    stackedItems.erase(x + y * 6);
                } else
                    items.emplace(std::pair<int, ItemData>(x+y*6, data));
                stackedItems.emplace(std::pair<int,int>(x+y*6,amt+1));
            }
        } else
            items.emplace(std::pair<int, ItemData>(x+y*6, data));
    } else
        return -1;
    return 0;
}

void Inventory::deleteItem(int id,int amount,int x,int y) {

    l_interface.deleteItem(inventoryLocation.c_str(),id,amount,x,y);
    items.erase(y*6+x);
}

void Inventory::draw() {
    //frame.render(game::getRenderer(),(SDL_Rect*)NULL);
    //SDL_RenderCopy(game::getRenderer(),inv_bg,nullptr,&inventoryRect);
    frame.render(inventoryRect.x,inventoryRect.y,nullptr);
    text.render(inventoryRect.x+20,inventoryRect.y+20,nullptr);


    renderItems();
}

void Inventory::renderItems() {
    for(auto item : items) {
        SDL_Rect itemRect{20+inventoryRect.x+((item.first%6)*16)+(item.first%6)*6,
                          inventoryRect.y+183+(((item.first-item.first%6)/6)*16)+
                                  ((item.first-item.first%6)/6)*5, 16,16};
        SDL_RenderCopy(game::getRenderer(),
                       game::getTextureManager()->getTexture(item.second.img),
                       nullptr,&itemRect);
        if(stackedItems.find(item.first) != stackedItems.end()) {
            // TODO Print amt of items
        }
    }
}

void Inventory::update() {
    //check if item is dropped or if new items arrive
}

/*void Inventory::buildInventory() {
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 32;
    clip.h = 32;

    SDL_SetRenderTarget(game::getRenderer(),inv_bg);
    frame.render(0,0,&clip);
    clip.x = 64;
    frame.render(inventoryRect.w-32,0,&clip);
    for(int j = 1;j<((inventoryRect.w-32) / 32);j++) {
        clip.x = 32;
        clip.y = 0;
        frame.render(j*32,0,&clip);
    }

    for(int i = 1;i<=(inventoryRect.h / 32);i++) {
        for(int j = 0;j<=((inventoryRect.w-32) / 32);j++) {
            if(i == 1 && j == 0) {
                clip.x = 0;
                clip.y = 0;
            } else if(i == ((inventoryRect.h-32)/32) && j == 0) {
                clip.x = 0;
                clip.y = 32;
            } else if(i == 1 && j == ((inventoryRect.w-32)/32)) {
                clip.x = 64;
                clip.y = 0;
            } else if(i == ((inventoryRect.h-32)/32) &&
                        j == ((inventoryRect.w-32)/32)) {
                clip.x = 64;
                clip.y = 32;
            } else if(i == 1) {
                clip.x = 32;
                clip.y = 0;
            } else if(i == ((inventoryRect.h-32)/32)) {
                clip.x = 32;
                clip.y = 32;
            } else if(j == 0) {
                clip.x = 0;
                clip.y = 10;
            } else if(j == ((inventoryRect.w-32)/32)) {
                clip.x = 64;
                clip.y = 10;
            } else {
                clip.x = 32;
                clip.y = 10;
            }
            frame.render(j*32,i*32,&clip);
        }
    }

    text.loadFromText("Inventory" ,
                        *game::getTextColor(),game::getFont());
    text.render(10,4,nullptr);
    SDL_SetRenderTarget(game::getRenderer(),nullptr);
}


*/