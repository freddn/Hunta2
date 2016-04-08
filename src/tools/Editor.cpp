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

#include "Editor.hpp"
#include "../Global.hpp"
#include "../Enums.hpp"

Editor::Editor() {
}

Editor::~Editor() {
}

void Editor::init() {
    loadIcon("data/x.png", 0,game::X);
    game::getTextureMapController()->update();
}

void Editor::loadIcon(std::string img, int id, std::size_t type) {
    Icon* tempIcon;
    if(type == game::ENEMY) {
        EnemyData data = game::getEnemyDataController()->getEnemyData(id);
        tempIcon = new Icon(img,data.width,data.height);
    } else
        tempIcon = new Icon(img);
    tempIcon->setID(id);
    tempIcon->setType(type);
    if(selectedCount == 0)
        tempIcon->setSelected(true);
    std::shared_ptr<Icon> temp {tempIcon};

    icons.insert(std::pair<int,std::shared_ptr<Icon>>(selectedCount, temp));
    selectedCount++;
}

void Editor::draw() {
    Screen::renderStart();

    //tileManager.draw();

    //environmentManager.draw();
    //enemyManager.draw();
    //itemManager.draw();
    game::getTextureMapController()->draw();
    //int pos = 5;
    for(unsigned int pos = 5,i = firstIcon;i < lastIcon;i++) {
        icons.at(i)->setY(60);
        icons.at(i)->setX(pos*34);
        icons.at(i)->draw();
        pos++;
    }

    Screen::renderEnd();
}

void Editor::update() {
    //SDL_PumpEvents();
    SDL_Rect* offset = game::getOffset();
    const Uint8 *key = SDL_GetKeyboardState(NULL);

    if(key[SDL_SCANCODE_UP]) {
        //if(offset->y > 0)
            offset->y = offset->y - 4;
    } else if(key[SDL_SCANCODE_DOWN]) {
        //if(offset->y < game::getHeight())
            offset->y = offset->y + 4;
    } else if(key[SDL_SCANCODE_LEFT]) {
        //if(offset->x > 0)
            offset->x = offset->x - 4;
    } else if(key[SDL_SCANCODE_RIGHT]) {
        //if(offset->x < game::getWidth())
            offset->x = offset->x + 4;
    } else if(key[SDL_SCANCODE_S]) {

        if(mapUpdated) {
            /*TODO move to game::pollEvents and implement a saving function
             in editor */
        }
    }
    game::getTextureMapController()->update();
    Screen::update();
}

void Editor::setSelected(int n) {
    icons.at(selected)->setSelected(false);
    if(n < 0)
        selected = 0;
    else
        selected = n;

    if(selected >= lastIcon && lastIcon < icons.size()) {
        lastIcon++;
        firstIcon++;
    } else if(selected < firstIcon) {
        lastIcon--;
        firstIcon--;
    }

    if(selected == icons.size())
        selected = icons.size()-1;

    icons.at(selected)->setSelected(true);
}

int Editor::getSelected() {
    return selected;
}

/// Place a tile, environment or enemy..
void Editor::place() {
    int mouseX = 0;
    int mouseY = 0;
    int tempX = 0;
    int tempY = 0;
    int index = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    /// Get the position on the map that was pressed.
    if(mouseX+game::getOffset()->x >= 0) {
        tempX = (mouseX+game::getOffset()->x)-((mouseX+game::getOffset()->x)%32);
    }
    else
        tempX = (mouseX+game::getOffset()->x-32)-((mouseX+game::getOffset()->x)%32);

    if(mouseY+game::getOffset()->y >= 0)
        tempY = (mouseY+game::getOffset()->y)-((mouseY+game::getOffset()->y)%32);
    else
        tempY = (mouseY+game::getOffset()->y-32)-((mouseY+game::getOffset()->y)%32);

    /// Check what map to edit
    if(tempX < 0 && tempX >= -MAP_WIDTH)
        mapX = -1;
    else if(tempX >= 0 && tempX < MAP_WIDTH)
        mapX = 0;
    else if(tempX < 0 && tempX < (mapX+2)*MAP_WIDTH)
        mapX = ((tempX - (tempX % MAP_WIDTH)) / MAP_WIDTH) - 1;
    else if(tempX >= MAP_WIDTH && tempX >= (mapX-2)*MAP_WIDTH)
        mapX = ((tempX - (tempX % MAP_WIDTH)) / MAP_WIDTH);

    if(tempY < 0 && tempY >= -MAP_HEIGHT)
        mapY = -1;
    else if(tempY >= 0 && tempY < MAP_HEIGHT)
        mapY = 0;
    else if(tempY < 0 && tempY < (mapY+2)*MAP_HEIGHT)
        mapY = ((tempY - (tempY % MAP_HEIGHT)) / MAP_HEIGHT) - 1;
    else if(tempY >= MAP_HEIGHT && tempY >= (mapY-2)*MAP_HEIGHT)
        mapY = ((tempY - (tempY % MAP_HEIGHT)) / MAP_HEIGHT);

    MapController *mapController = game::getTextureMapController();
    int mapID = mapController->getMapID(mapX,mapY);
    if(mapID == 0) {
        int i = 1;
        while(mapController->mapExists(i)) {
            i++;
        }
        mapID = i;
        int n = mapController->getMapID(mapX,mapY-1);
        int s = mapController->getMapID(mapX,mapY+1);
        int w = mapController->getMapID(mapX-1,mapY);
        int e = mapController->getMapID(mapX+1,mapY);
        if(n != 0)
            mapController->getMap(n)->setMapAt(game::SOUTH,mapID);
        if(e != 0)
            mapController->getMap(e)->setMapAt(game::WEST,mapID);
        if(s != 0)
            mapController->getMap(s)->setMapAt(game::NORTH,mapID);
        if(w != 0)
            mapController->getMap(w)->setMapAt(game::EAST,mapID);
        mapController->loadMapData(mapID,mapX,mapY,n,e,s,w);
    }
    /// Set x and y pos according to current map.
    int relX = tempX - mapX*MAP_WIDTH;
    int relY = tempY - mapY*MAP_HEIGHT;

    index = (relX/32)+((relY/32)*64);

    /// Load the entity onto the map
    switch(icons.at(selected)->getType()) {
    case game::TILE:
        mapController->loadTile(mapID,icons.at(selected)->getID(), index, relX,relY);
        break;
    case game::ENVIRONMENT:
        mapController->loadEnvironment(mapID,icons.at(selected)->getID(), index, relX,relY);
        break;
    case game::ENEMY:
        mapController->loadEnemy(mapID, icons.at(selected)->getID(),index, relX,relY);
        break;
    case game::X:
        mapController->getMap(mapID)->removeEntity(index, tempX,tempY);
    }

    mapUpdated = true;
    game::setHasChanged(true);
}

