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



MapClass::MapClass()
{

}

void MapClass::init(SDL_Renderer *renderer)
{
    std::cout << " - MapClass::init() ..."<<std::endl;
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
    std::cout << " - MapClass::loadMap() ... " << std::endl;
    bool success = true;
    currentMap = mapLoader.getMap(filename);
    if(currentMap.empty())
        success = false;
    return success;
}

void MapClass::saveMap(std::map<int,Texture*> temp_map,
                        const char* filename, int width, int height)
{
    std::cout << " - MapClass::saveMap() ..."<<std::endl;
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










