#include "Map.hpp"

#include "Game.hpp"

#include "Position.hpp"
#include "Texture.hpp"
#include "GPhysics.hpp"
#include "Enemy.hpp"
#include "HealthBar.hpp"
#include "Character.hpp"
#include "Weapon.hpp"
#include "Camera.hpp"



Map::Map() {
    //ctor
}

Map::~Map() {
    //dtor
}
void Map::setMapID(int id) { mapID = id; }
int Map::getMapID() { return mapID; }

void Map::setActive(bool active) {
    mapIsActive = active;
}

bool Map::isActive() {
    return mapIsActive;
}

void Map::update() {
    if(editMode) {

    }
    manager.refresh();
    manager.update();

}

void Map::draw() {
    tiles.draw();
    manager.draw();
}

void Map::close() {

}

/// Just to be safe..
bool Map::hasEntities() {
    bool entities = false;
    if(!mapIsActive) {
        return false;
    }

    if(tiles.getEntities() && !tiles.getEntities()->empty() ||
        tiles.getEntitiesByIndex() != nullptr && !tiles.getEntitiesByIndex()->empty())
        entities = true;
    if(!manager.getEntities()->empty() ||
        !manager.getEntitiesByIndex()->empty())
        entities = true;
    return entities;
}

void Map::loadTile(int mapID, int id, int index, int x,int y, std::string img) {
    //std::cerr << "loaded tile " <<index<<" to map:"<<mapID << std::endl;
    Entity *tile = &tiles.addEntity(index);
    tile->addComponent<Position>(x, y);
    tile->addComponent<Texture>(img,false);
    tile->addComponent<Tile>(id);
}

void Map::loadEnvironment(int mapID, int id, int index, int x,int y, std::string img) {
    Entity *env = manager.addEntity(index,false);
    if(env != nullptr) {
        //std::cerr << "environment added..."<<std::endl;
        env->addComponent<Position>(x,y);
        env->addComponent<Texture>(img,false);
        env->addComponent<GPhysics>();
        env->addComponent<Environment>(id);
        env->addGroup(game::ENVIRONMENT);
    }
}

void Map::loadEnemy(int mapID, int id, int index, int x,int y, std::string img) {
    Entity *enemy = manager.addEntity(index,false);
    if(enemy != nullptr) {
        enemy->addComponent<Position>(x,y);
        enemy->addComponent<Texture>(img,true);
        enemy->addComponent<GPhysics>();
        enemy->addComponent<HealthBar>(20);
        enemy->addComponent<Enemy>(manager, id);
        enemy->addGroup(game::ENEMY);
    }
}

void Map::loadPlayer(int x,int y) {
    for(auto& ent : manager.getEntitiesByGroup(game::PLAYER))
        ent->destroy();

    Entity *player = &manager.addEntity();
    if(player != nullptr) {
        player->addComponent<Position>(x,y);
        player->addComponent<Texture>("data/gubbe_box1.png",true); // 32x32 clip
        player->addComponent<GPhysics>();
        player->addComponent<HealthBar>(100);
        player->addComponent<Weapon>("data/sword.png", manager);
        player->addComponent<Camera>();
        player->addComponent<Character>(manager);
        player->addGroup(game::PLAYER);
    }
}

void Map::destroyPlayer() {
    for(auto &player : manager.getEntitiesByGroup(game::PLAYER))
        player->destroy();
}

void Map::setEditMode(bool mode) {
    editMode = mode;
}

void Map::removeEntity(int index,int x, int y) {
    manager.destroyEntity(index,x,y);
}

void Map::save(LuaInterface *lInterface) {

    lInterface->newMapFile(mapID, "/tiles.lua");

    for(auto &tile : *tiles.getEntitiesByIndex()) {

        int id = tile.second->getComponent<Tile>().getID();
        int x = tile.second->getComponent<Position>().getX();
        x = x - (x%32);
        int y = tile.second->getComponent<Position>().getY();
        y = y - (y%32);
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        //std::cerr << "id " << mapID << " i " << index << " x "<< x<< " y " << y << std::endl;
        lInterface->appendMapData("loadTile",mapID,"/tiles.lua",id,index,x,y);
    }

    lInterface->newMapFile(mapID, "/environment.lua");

    for(auto &ent : manager.getEntitiesByGroup(game::ENVIRONMENT)) {
        int id = ent->getComponent<Environment>().getID();
        int x = ent->getComponent<Position>().getX();
        x = x - (x%32);
        int y = ent->getComponent<Position>().getY();
        y = y - (y%32);
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        lInterface->appendMapData("loadEnvironment", mapID,"/environment.lua",id,index,x,y);
    }

    lInterface->newMapFile(mapID, "/enemies.lua");

    for(auto &ent : manager.getEntitiesByGroup(game::ENEMY)) {
        int id = ent->getComponent<Enemy>().getID();
        int x = ent->getComponent<Position>().getX();
        x = x - (x%32);
        int y = ent->getComponent<Position>().getY();
        y = y - (y%32);
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        lInterface->appendMapData("loadEnemy", mapID,"/enemies.lua",id,index,x,y);
    }
}