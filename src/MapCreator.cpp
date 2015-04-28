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

#include "MapCreator.hpp"

MapCreator::MapCreator()
{

}

MapCreator::~MapCreator()
{
    //dtor
}

void MapCreator::init()
{
    std::cout << " - MapCreator::init() ..."<<std::endl;
    l_interface.initLua();
    l_interface.load_File("src/CreateMap.lua");
}

void MapCreator::newMap(std::map<int,Texture*> currentMap,
            const char *filename, int width, int height)
{
    std::cout << " - MapCreator::newMap() ..."<<std::endl;
    l_interface.newMapFile(filename,width,height);
    for(auto iter = currentMap.begin(); iter != currentMap.end();iter++)
    {
        l_interface.appendTile(
                    filename,
                    ((int)iter->first),
                    (int)((int)(((Texture*)iter->second)->getRect().x) /
                    (int)(((Texture*)iter->second)->getWidth())),
                    (int)((int)(((Texture*)iter->second)->getRect().y) /
                    (int)(((Texture*)iter->second)->getHeight())),
                    0,
                    ((Texture*)iter->second)->getImgPath().c_str(),
                    ((Texture*)iter->second)->isSolid());
    }
}


