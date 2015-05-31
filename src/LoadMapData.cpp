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

#include "LoadMapData.hpp"


using namespace lua_functions;

LoadMapData::LoadMapData()
{
    //std::map<int,Texture*> mamppp = lua_functions::getCurrentMap();

    //l_interface.newMapFile("data/map233",width/32,height/32);


    //l_interface.load_tiles("data/map1");

    //l_interface.getTile();

    // Testing lua functionallity..


}

LoadMapData::~LoadMapData()
{
    //dtor
}

void LoadMapData::init()
{
    std::cout << " - LoadMapData::init() ..."<<std::endl;
    l_interface.initLua();
    l_interface.load_File("src/LoadMap.lua");
}

void LoadMapData::insertTiles()
{

}

void insertTile()
{


}

std::map<int,Texture*> * LoadMapData::getMap(const char* filename)
{
    std::cout << " - LoadMapData::getMap() ..."<<std::endl;
    l_interface.load_tiles(filename);
    return lua_functions::getCurrentMap();
}

void setMap()
{

}







