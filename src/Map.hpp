#ifndef MAP_H
#define MAP_H


#define MAP_WIDTH 2048
#define MAP_HEIGTH 2048

#include <string>

#include "EntitySystem.hpp"
#include "LuaInterface.hpp"

#include "Tile.hpp"
#include "Environment.hpp"
#include "Enemy.hpp"


using namespace EntitySystem;

class Map {
public:
    Map();
    void init();
    void draw();
    void update();
    void close();

    bool hasEntities();

    void setActive(bool active);
    bool isActive();

    void setMapID(int id);
    int getMapID();

    void setNorth(int id) {north = id;};
    void setSouth(int id) {south = id;};
    void setWest(int id) {west = id;};
    void setEast(int id) {east = id;};

    int getNorth() {return north;};
    int getSouth() {return south;};
    int getWest() {return west;};
    int getEast() {return east;};

    void setX(int x) {mapX = x;};
    void setY(int y) {mapY = y;};

    int getX() {return mapX;};
    int getY() {return mapY;};

    void save(LuaInterface *lInterface);

    void loadTile(int mapID, int id, int index, int x,int y, std::string img);
    void loadEnvironment(int mapID,int id, int index, int x,int y, std::string img);
    void loadEnemy(int mapID, int id, int index, int x,int y, std::string img);

    void loadPlayer(int x,int y);
    void destroyPlayer();
    void setEditMode(bool mode);

    void removeEntity(int index, int x,int y);

    virtual ~Map();
protected:
private:

    bool editMode = false;
    int mapID = 0;

    int mapX = 0;
    int mapY = 0;

    int north = 0;
    int west = 0;
    int south = 0;
    int east = 0;
    bool mapIsActive = false;

    EntityManager tiles;
    EntityManager manager;


};

#endif // MAP_H
