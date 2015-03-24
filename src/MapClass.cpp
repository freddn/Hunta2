#include "MapClass.hpp"



MapClass::MapClass()
{

}

void MapClass::init(SDL_Renderer *renderer)
{
    ground_T.loadFromFile(renderer,"data/ground.png");
    water_T.loadFromFile(renderer,"data/water.png");
    grass_T.loadFromFile(renderer,"data/grass.png");

    lua_functions::setGrass(grass_T.clone());
    lua_functions::setGround(ground_T.clone());
    lua_functions::setWater(water_T.clone());

    mapLoader.init();
    mapCreator.init();
}

MapClass::~MapClass()
{
    currentMap.erase(currentMap.begin(),currentMap.end());
    grass_T.free();
    ground_T.free();
    water_T.free();
}

bool MapClass::loadMap(const char* filename)
{
    bool success = true;
    currentMap = mapLoader.getMap(filename);
    if(currentMap.empty())
        success = false;
    return success;
}

void MapClass::saveMap(std::map<int,Texture*> temp_map,
                        const char* filename, int width, int height)
{
    mapCreator.newMap(temp_map,filename,width,height);
}

void insertTile(Texture *texture)
{

}

void MapClass::setMap(std::map<int,Texture*> tempMap)
{
    currentMap = tempMap;
}

std::map<int,Texture*> MapClass::getMap()
{
    return currentMap;
}

Texture* MapClass::tileAtIndex()
{
    return NULL;
}

Texture* MapClass::getGrassTile()
{
    return grass_T.clone();
}

Texture* MapClass::getGroundTile()
{
    return ground_T.clone();
}

Texture* MapClass::getWaterTile()
{
    return water_T.clone();
}










