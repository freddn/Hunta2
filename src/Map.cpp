#include "Map.hpp"

#include "Enums.hpp"
#include "Global.hpp"

#include "components/Position.hpp"
#include "components/Texture.hpp"
#include "components/GPhysics.hpp"
#include "components/Enemy.hpp"
#include "components/Health.hpp"
#include "components/Character.hpp"
#include "components/Weapon.hpp"
#include "components/Camera.hpp"

#include "components/Tile.hpp"
#include "components/Environment.hpp"
#include "components/Enemy.hpp"
#include "components/Item.hpp"
#include "components/Environment.hpp"


Map::Map() {}

Map::~Map() {}

void Map::init() {
    items.init(game::getOffset());
    tiles.init(game::getOffset());
    manager.init(game::getOffset());

    tiles.setOffset(mapX*MAP_WIDTH,mapY*MAP_HEIGHT);
}

void Map::setMapID(int id) { mapID = id; }
int Map::getMapID() { return mapID; }

void Map::setActive(bool active) {
    mapIsActive = active;
}

void Map::setMapAt(int dir, int mapID) {
    if(dir >= 0 && dir < 4)
        neighbors[dir] = mapID;
}

int Map::getMapAt(int dir) {
    return neighbors[dir];
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

void Map::clear() {
    tiles.clear();
    manager.clear();
    return;
}

/// Just to be safe..
bool Map::hasEntities() {
    bool entities = false;
    if(!mapIsActive)
        return false;

    if((tiles.getEntities() && !tiles.getEntities()->empty()) ||
        (tiles.getEntitiesByIndex() != nullptr && !tiles.getEntitiesByIndex()->empty()))
        entities = true;
    if(!manager.getEntities()->empty() ||
        !manager.getEntitiesByIndex()->empty())
        entities = true;
    return entities;
}

void Map::loadTile(int id, int index, int x,int y, const std::string &img) {
    Entity *tile = &tiles.addEntity(index);
    tile->addComponent<Position>(x + mapX*MAP_WIDTH, y + mapY*MAP_HEIGHT);
    tile->addComponent<Texture>(img,false);
    tile->addComponent<Tile>(id);
}

void Map::loadEnvironment(int id, int index, int x,int y, const std::string &img) {
    Entity *env = manager.addEntity(index,false);
    if(env != nullptr) {
        env->addComponent<Environment>(id);
        env->addComponent<Position>(x + mapX*MAP_WIDTH,y + mapY*MAP_HEIGHT);
        env->addComponent<Texture>(img,false);
        env->addComponent<GPhysics>();
        env->addGroup(game::ENVIRONMENT);
    }
}

void Map::loadEnemy(int id, int index, int x,int y, const std::string &img, int width, int height) {
    Entity *enemy = manager.addEntity(index,false);
    EnemyData data = game::getEnemyDataController()->getEnemyData(id);
    if(enemy != nullptr) {
        enemy->addComponent<Position>(x + mapX*MAP_WIDTH,y + mapY*MAP_HEIGHT);
        if(width > 0 && height > 0)
            enemy->addComponent<Texture>(img,true, width, height);
        else
            enemy->addComponent<Texture>(img,true);
        enemy->addComponent<GPhysics>();
        enemy->addComponent<Health>(data.hp);
        enemy->addComponent<Enemy>(manager, id, data.exp, data.name, data.atk);
        enemy->addGroup(game::ENEMY);
    }
}

void Map::loadItem(int id, int x, int y, int amount) {
    Entity *item = manager.addEntity(x+y*MAP_WIDTH,false);
    ItemData data = game::getItemManager()->getItem(id);
    if(item != nullptr) {
        item->addComponent<Position>(x+ mapX*MAP_WIDTH,y+ mapY*MAP_HEIGHT);
        item->addComponent<Texture>(data.img,true);
        item->addComponent<Item>(id);
        item->addGroup(game::ITEM);
    }
}

void Map::loadPlayer(int x,int y) {
    for(auto& ent : manager.getEntitiesByGroup(game::PLAYER))
        ent->destroy();

    Entity *player = &manager.addEntity();
    if(player != nullptr) {
        player->addComponent<Position>(x + mapX*MAP_WIDTH,y + mapY*MAP_HEIGHT);
        const std::string c("data/gubbenew.png");
        //const std::string c("data/character.png");
        player->addComponent<Texture>(c.c_str(),true); // 32x32 clip
        player->addComponent<GPhysics>();
        player->addComponent<Health>(game::getPlayerController()->getHp());
        
        const std::string s("data/sword.png");
        //
        player->addComponent<Weapon>(s.c_str(), manager);
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
        x = x - (x%32) - mapX*MAP_WIDTH;
        int y = tile.second->getComponent<Position>().getY();
        y = y - (y%32) - mapY*MAP_HEIGHT;
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        lInterface->appendMapData("loadTile",mapID,"/tiles.lua",id,index,x,y);
    }

    lInterface->newMapFile(mapID, "/environment.lua");

    for(auto &ent : manager.getEntitiesByGroup(game::ENVIRONMENT)) {
        int id = ent->getComponent<Environment>().getID();
        int x = ent->getComponent<Position>().getX();
        x = x - (x%32) - mapX*MAP_WIDTH;
        int y = ent->getComponent<Position>().getY();
        y = y - (y%32) - mapY*MAP_HEIGHT;
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        lInterface->appendMapData("loadEnvironment", mapID,
                                  "/environment.lua",id,index,x,y);
    }

    lInterface->newMapFile(mapID, "/enemies.lua");

    for(auto &ent : manager.getEntitiesByGroup(game::ENEMY)) {
        int id = ent->getComponent<Enemy>().getID();
        int x = ent->getComponent<Position>().getX();
        x = x - (x%32) - mapX*MAP_WIDTH;
        int y = ent->getComponent<Position>().getY();
        y = y - (y%32) - mapY*MAP_HEIGHT;
        int index = (x/32) + (y/32)*(MAP_WIDTH/32);
        lInterface->appendMapData("loadEnemy", mapID,"/enemies.lua",id,index,x,y);
    }

    lInterface->appendMapDataInfo("data/maps/maps.lua",mapID,mapX,mapY,
                                  neighbors[game::NORTH], neighbors[game::EAST],
                                  neighbors[game::SOUTH],neighbors[game::WEST]);

}

void Map::loadNeighbors(LuaInterface *lInterface) {
    for(int i = 0;i<4;i++){
        if(neighbors[i] != 0)
            lInterface->loadMap(neighbors[i]);
    }
}

unsigned long Map::getTileCount() {
    return tiles.getEntitiesByIndex()->size();
}
