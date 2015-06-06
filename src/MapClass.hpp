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

#ifndef MAPCLASS_H
#define MAPCLASS_H

#include <map>

#include "Tile.hpp"
#include "LuaInterface.hpp"
#include "LoadMapData.hpp"
#include "MapCreator.hpp"

/*
 * Load a map, save a map, change a map.
 */
class MapClass {
public:
    MapClass();
    void init();
    bool loadMap(std::string filename);
    void saveMap(std::map<int,Texture*> &loadedMap,
                const char*filename, int width, int height);
    void insertTile(Texture &texture);
    void setMap(std::map<int,Texture*> &textureMap);
    std::map<int,Texture*> *getMap();
    void clearCurrentMap();
    Texture *tileAtIndex();
    Texture *getGrassTile();
    Texture *getGroundTile();
    Texture *getWaterTile();

    void changeMap(const char *mapName);
    ~MapClass();
private:
    //std::map<const char*,std::map<int,Texture*>> maps;
    std::map<int,Texture*> currentMap;
    LoadMapData mapLoader;
    MapCreator mapCreator;
    Texture grass_T;
    Texture ground_T;
    Texture water_T;
};

#endif // MAPCLASS_H

