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

#include "MapController.hpp"
#include "Game.hpp"
#include "EntitySystem.hpp"

#include <iostream>

MapController::MapController() {}

MapController::~MapController() {}

void MapController::init(LuaInterface *lInterface) {

    /// Traverse all maps and check neighbors (?)
    this->lInterface = lInterface;

    std::cout << " - MapController::init() ..."<<std::endl;

    std::cerr << " ... Loading map data ..." << std::endl;
    lInterface->loadFile("data/maps/maps.lua");
    std::cerr << " ... Loading tile data ..." << std::endl;
    lInterface->loadFile("data/tiles/tiles.lua");
    std::cerr << " ... Loading environment data ..." << std::endl;
    lInterface->loadFile("data/environment/environment.lua");
    std::cerr << " ... Loading enemy data ..." << std::endl;
    lInterface->loadFile("data/enemies/enemies.lua");

    std::cerr << " ... Loading weapon data ..." << std::endl;
    lInterface->loadFile("data/items/weapons/weapons.lua");
    std::cerr << " ... Loading armor data ..." << std::endl;
    lInterface->loadFile("data/items/armor/armor.lua");
    std::cerr << " ... Loading misc item data ..." << std::endl;
    lInterface->loadFile("data/items/misc/misc.lua");
    std::cerr << " ... Loading usables data ..." << std::endl;
    lInterface->loadFile("data/items/usables/usables.lua");
    int i = 1;
    while(mapExists(i)) {
        lInterface->loadMap(i);
        i++;
    }
    //mapContainer.at(1)->loadNeighbors(&l_interface);
    //mapContainer.at(2)->loadNeighbors(&l_interface);
}

void MapController::draw() {
    for(auto &m : mapContainer) {
        m.second->draw();
    }
}

void MapController::update() {
    for(auto &m : mapContainer) {
        m.second->update();
    }
}

bool MapController::loadMap(int mapID) {
    std::cout << " - MapClass::loadMap() ... " << std::endl;
    if(mapContainer.find(mapID) == mapContainer.end()) {
        std::cout << "Map not found: " << mapID << std::endl;
        return false;
    } else {
        lInterface->loadMap(mapID);
        return true;
    }
}

void MapController::saveMaps() {
    lInterface->newMapDataFile("data/maps/maps.lua");
    for(auto &m : mapContainer) {
        std::cerr << "Save map: " << m.second->getMapID() << std::endl;
        m.second->save(lInterface);
    }
}

void MapController::setMap(std::shared_ptr<Map> tempMap) {
    currentMap = tempMap;
}

bool MapController::mapExists(int mapID) {
    if(mapContainer.count(mapID) < 1)
        return false;
    if(mapContainer.find(mapID) == mapContainer.end())
        return false;
    if(mapContainer.at(mapID) == nullptr)
        return false;
    if(mapContainer.at(mapID)->getMapID() != mapID)
        return false;
    return true;
}

std::shared_ptr<Map> MapController::getMap(int mapID) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        std::cerr << "Map "<<mapID << " = mapContainer.end()" << std::endl;
        return nullptr;
    }
    return mapContainer.at(mapID);
}

/// Inserts a tile into current map
void MapController::loadTile(int mapID,int id, int index,int x,int y) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        Map* tempMap(new Map());
        std::cerr << "New map but not complete......."<< std::endl;
        tempMap->setMapID(mapID);
        tempMap->setActive(true);
        std::shared_ptr<Map> temp{tempMap};
        mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(mapID,temp));
    }
    mapContainer.at(mapID)->loadTile(id,index,x,y,tiles.at(id));
}

void MapController::loadEnvironment(int mapID,int id, int index,int x,int y) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        Map* tempMap(new Map());
        tempMap->setMapID(mapID);

        std::shared_ptr<Map> temp {tempMap};
        mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(mapID,temp));
    }
    mapContainer.at(mapID)->loadEnvironment(id,index,x,y,environment.at(id));
}

void MapController::loadEnemy(int mapID, int id, int index,int x,int y) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        Map* tempMap(new Map());
        tempMap->setMapID(mapID);

        std::shared_ptr<Map> temp {tempMap};
        mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(mapID,temp));
    }
    EnemyData data = game::getEnemyDataController()->getEnemyData(id);

    mapContainer.at(mapID)->loadEnemy(id,index,x,y,enemies.at(id), data.width, data.height);
}

/// Loads a tile texture
void MapController::loadTileData(int id, std::string img, bool solid) {
    Texture *texture(new Texture());

    texture->loadFromFile(img);
    texture->setSolid(solid);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    tiles.insert(std::pair<int,std::string>(id,img));
}

/// Loads an environment texure
void MapController::loadEnvironmentData(int id, std::string img, bool solid) {
    Texture *texture(new Texture());

    texture->loadFromFile(img);
    texture->setSolid(solid);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    environment.insert(std::pair<int,std::string>(id,img));
}
/// Load an enemy texture
void MapController::loadEnemyData(int id, std::string img) {
    std::cout << id << std::endl;

    Texture *texture;
    texture = new Texture();
    texture->loadFromFile(img);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    enemies.insert(std::pair<int,std::string>(id,img));
}

/// Load info about existing maps.
void MapController::loadMapData(int id, int x,int y,int n,int e, int s, int w) {
    mapContainer.erase(id);
    Map* tempMap(new Map());
    tempMap->setMapID(id);
    tempMap->setX(x);
    tempMap->setY(y);
    tempMap->setMapAt(game::NORTH,n);
    tempMap->setMapAt(game::SOUTH,s);
    tempMap->setMapAt(game::EAST,e);
    tempMap->setMapAt(game::WEST,w);
    tempMap->init();
    tempMap->setActive(true);
    std::cerr << " ... map loaded:" << id<< std::endl;

    std::shared_ptr<Map> temp {tempMap};
    mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(id,temp));
}

int MapController::getMapID(int x, int y) {
    for(auto m : mapContainer) {
        if(m.second->getX() == x && m.second->getY() == y)
            return m.second->getMapID();
    }
    return 0;
}

Texture* MapController::tileAtIndex() {
    return NULL;
}

int MapController::getCurrentMap() {
    return currentMapID;
}

void MapController::setCurrentMap(int mapID) {
    currentMapID = mapID;
}

