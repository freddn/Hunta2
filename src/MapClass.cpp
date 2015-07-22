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

#include "MapClass.hpp"
#include "Game.hpp"
#include "EntitySystem.hpp"

MapClass::MapClass() {

}

void MapClass::init() {

    /// Traverse all maps and check neighbors (?)


    std::cout << " - MapClass::init() ..."<<std::endl;
    /*ground_T.loadFromFile("data/ground.png");
    water_T.loadFromFile("data/water.png");
    grass_T.loadFromFile("data/grass.png");

    lua_functions::setGrass(grass_T);
    lua_functions::setGround(ground_T);
    lua_functions::setWater(water_T);
*/
    l_interface.initLua();
    l_interface.loadFile("src/LoadMap.lua");
    l_interface.loadFile("src/CreateMap.lua");

    std::cerr << " ... Loading map data ..." << std::endl;
    l_interface.loadFile("data/maps/maps.lua");
    std::cerr << " ... Loading tile data ..." << std::endl;
    l_interface.loadFile("data/tiles/tiles.lua");
    std::cerr << " ... Loading environment data ..." << std::endl;
    l_interface.loadFile("data/environment/environment.lua");
    std::cerr << " ... Loading enemy data ..." << std::endl;
    l_interface.loadFile("data/enemies/enemies.lua");

    std::cerr << " ... Loading weapon data ..." << std::endl;
    l_interface.loadFile("data/items/weapons/weapons.lua");
    std::cerr << " ... Loading armor data ..." << std::endl;
    l_interface.loadFile("data/items/armor/armor.lua");
    std::cerr << " ... Loading misc item data ..." << std::endl;
    l_interface.loadFile("data/items/misc/misc.lua");
    std::cerr << " ... Loading usables data ..." << std::endl;
    l_interface.loadFile("data/items/usables/usables.lua");


    mapContainer.at(1)->loadNeighbors(&l_interface);
}

void MapClass::draw() {
    for(auto &m : mapContainer) {
        m.second->draw();
    }
}

void MapClass::update() {
    for(auto &m : mapContainer) {
        m.second->update();
    }
}

MapClass::~MapClass() {
    //currentMap.erase(currentMap.begin(),currentMap.end());
    //grass_T.free();
    //ground_T.free();
    //water_T.free();
}

bool MapClass::loadMap(int mapID) {
    std::cout << " - MapClass::loadMap() ... " << std::endl;
    if(mapContainer.find(mapID) == mapContainer.end()) {
        std::cout << "Map not found: " << mapID << std::endl;
        return false;
    } else {
        l_interface.loadMap(mapID);
        return true;
    }
}

void MapClass::clearCurrentMap() {
    //for(auto iter = currentMap->begin(); iter != currentMap->end();iter++) {
        //if(iter->second != nullptr) {
        //    delete (Texture*)iter->second;
        //}
        //currentMap->erase(currentMap->begin(),currentMap->end());
    //}
}

void MapClass::saveMaps() {
    l_interface.newMapDataFile("data/maps/maps.lua");
    for(auto &m : mapContainer) {
        std::cerr << "Save map: " << m.second->getMapID() << std::endl;
        m.second->save(&l_interface);
    }


}

void MapClass::setMap(std::shared_ptr<Map> tempMap) {
    currentMap = tempMap;
}

bool MapClass::mapExists(int mapID) {
    //std::cerr << mapContainer.count(mapID) << std::endl;
    //std::cerr << "map empty " << mapContainer.size() << std::endl;
    //std::cerr << "map count" << std::endl;
    if(mapContainer.count(mapID) < 1)
        return false;
    //std::cerr << "map end" << std::endl;
    if(mapContainer.find(mapID) == mapContainer.end())
        return false;
    //std::cerr << "map null" << std::endl;
    if(mapContainer.at(mapID) == nullptr)
        return false;
    //std::cerr << "map id" << std::endl;

    if(mapContainer.at(mapID)->getMapID() != mapID)
        return false;
    //std::cerr << "entities" << std::endl;
    //if(!mapContainer.at(mapID)->hasEntities())
     //   return false;
    //std::cerr << "pass" << std::endl;
    return true;
}

std::shared_ptr<Map> MapClass::getMap(int mapID) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        std::cerr << "Map "<<mapID << " = mapContainer.end()" << std::endl;
        return nullptr;
    }
    return mapContainer.at(mapID);
}

/// Inserts a tile into current map
void MapClass::loadTile(int mapID,int id, int index,int x,int y) {
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

void MapClass::loadEnvironment(int mapID,int id, int index,int x,int y) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        Map* tempMap(new Map());
        tempMap->setMapID(mapID);

        std::shared_ptr<Map> temp {tempMap};
        mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(mapID,temp));
    }
    mapContainer.at(mapID)->loadEnvironment(id,index,x,y,environment.at(id));
}

void MapClass::loadEnemy(int mapID, int id, int index,int x,int y) {
    if(mapContainer.find(mapID) == mapContainer.end()) {
        Map* tempMap(new Map());
        tempMap->setMapID(mapID);

        std::shared_ptr<Map> temp {tempMap};
        mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(mapID,temp));
    }
    mapContainer.at(mapID)->loadEnemy(id,index,x,y,enemies.at(id));
}

/// Loads a tile texture
void MapClass::loadTileData(int id, std::string img, bool solid) {
    Texture *texture(new Texture());

    texture->loadFromFile(img);
    texture->setSolid(solid);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    tiles.insert(std::pair<int,std::string>(id,img));
}

/// Loads an environment texure
void MapClass::loadEnvironmentData(int id, std::string img, bool solid) {
    Texture *texture(new Texture());

    texture->loadFromFile(img);
    texture->setSolid(solid);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    environment.insert(std::pair<int,std::string>(id,img));
}
/// Load an enemy texture
void MapClass::loadEnemyData(int id, std::string img, int hp,int level, int atk) {
    Texture *texture(new Texture());

    texture->loadFromFile(img);

    std::shared_ptr<Texture> temp {texture};
    loadedTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(img,temp));
    enemies.insert(std::pair<int,std::string>(id,img));
}

/// Load info about existing maps.
void MapClass::loadMapData(int id, int x,int y,int n,int e, int s, int w) {
    if(mapContainer.find(id) != mapContainer.end())
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
    std::cerr << "MAP LOADED!!!!!!!!!! : " << id<< std::endl;

    std::shared_ptr<Map> temp {tempMap};
    mapContainer.insert(std::pair<int,std::shared_ptr<Map>>(id,temp));
}

int MapClass::getMapID(int x, int y) {
    for(auto m : mapContainer) {
        if(m.second->getX() == x && m.second->getY() == y)
            return m.second->getMapID();
    }
    return 0;
}

Texture* MapClass::tileAtIndex() {
    return NULL;
}

int MapClass::getCurrentMap() {
    return currentMapID;
}

void MapClass::setCurrentMap(int mapID) {
    currentMapID = mapID;
}

