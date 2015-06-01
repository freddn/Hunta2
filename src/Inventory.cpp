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


using namespace EntitySystem;

Inventory::Inventory(int x, int y) {
    inventoryRect.x = x;
    inventoryRect.y = y;

}


Inventory::~Inventory() {}

void Inventory::init() {
    frame.loadFromFile(game::getRenderer(),"data/frame.png");
    inventoryRect.w = sizeX*32;
    inventoryRect.h = sizeY*32;
    inv_bg = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, sizeX*32, sizeY*32);
    if(inv_bg == 0)
        std::cerr << "Failed to create inventory" << std::endl;

    buildInventory();
    l_interface.initLua();
    if(!l_interface.load_File("src/LoadInventory.lua"))
        std::cerr << "Failed to Load LoadInventory.lua" << std::endl;

    if(!l_interface.load_File("src/InventoryFunctions.lua"))
        std::cerr << "Failed to Load InventoryFunctions.lua" << std::endl;
}

void Inventory::loadInventory() {
    l_interface.loadInventory("data/inventory1");
    inventoryItem *items = lua_functions::getItems();
    //l_interface.addItem("data/inventory1",12,4,4,6);
    int i = 0;
    while(items[i].id!= -1 && i < 20) {
        std::cerr << "item id: "<<items[i].id << std::endl;
        i++;
    }
}

int Inventory::addItem(int id,int amount,int x, int y) {
    if(lua_functions::getItemCount() < 20)
        l_interface.addItem("data/inventory1",id,amount,x,y);
    else
        return -1;
    return 0;
}

void Inventory::deleteItem(int id,int amount,int x,int y) {
    l_interface.deleteItem("data/inventory1",id,amount,x,y);
}

void Inventory::draw() {
    //frame.render(game::getRenderer(),(SDL_Rect*)NULL);
    SDL_RenderCopy(game::getRenderer(),inv_bg,nullptr,&inventoryRect);
}

void Inventory::update() {
    //check if item is dropped or if new items arrive
}

void Inventory::buildInventory() {
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 32;
    clip.h = 32;

    SDL_SetRenderTarget(game::getRenderer(),inv_bg);
    frame.render(game::getRenderer(),0,0,&clip);
    clip.x = 64;
    frame.render(game::getRenderer(),inventoryRect.w-32,0,&clip);
    for(int j = 1;j<((inventoryRect.w-32) / 32);j++) {
        clip.x = 32;
        clip.y = 0;
        frame.render(game::getRenderer(),j*32,0,&clip);
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
            frame.render(game::getRenderer(),j*32,i*32,&clip);
        }
    }

    text.loadFromText(game::getRenderer(),"Inventory" ,
                        *game::getText_color(),game::getFont());
    text.render(game::getRenderer(),10,4,nullptr);
    SDL_SetRenderTarget(game::getRenderer(),nullptr);
}


