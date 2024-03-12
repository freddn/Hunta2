#ifndef MAP_H
#define MAP_H


#define MAP_WIDTH 2048
#define MAP_HEIGTH 2048

#include <string>

#include "components/EntitySystem.hpp"
#include "scripting/LuaInterface.hpp"

using namespace EntitySystem;

class Map {
public:
    Map();
    void init();
    void draw();
    void update();
    void clear();

    bool hasEntities();

    void setActive(bool active);
    bool isActive();

    void setMapID(int id);
    int getMapID();

    void setMapAt(int dir, int mapID);
    int getMapAt(int dir);

    void setX(int x) {mapX = x;};
    void setY(int y) {mapY = y;};

    int getX() {return mapX;};
    int getY() {return mapY;};

    void save(LuaInterface *lInterface);
    void loadNeighbors(LuaInterface *lInterface);

    void loadTile(int id, int index, int x,int y, const std::string &img);
    void loadEnvironment(int id, int index, int x,int y, const std::string &img);
    void loadEnemy(int id, int index, int x,int y, const std::string &img, int width = 0, int height = 0);
    void loadItem(int id, int x, int y, int amount);

    void loadPlayer(int x,int y);
    void destroyPlayer();
    void setEditMode(bool mode);

    unsigned long getTileCount();

    void removeEntity(int index, int x,int y);

    virtual ~Map();
protected:
private:

    bool editMode = false;
    int mapID = 0;

    int mapX = 0;
    int mapY = 0;

    int neighbors[4] = {0,0,0,0};
    bool mapIsActive = false;
    EntityManager items;
    EntityManager tiles;
    EntityManager manager;
};

#endif // MAP_H
