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

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define MAP_WIDTH 2048
#define MAP_HEIGHT 2048
#define MAP_TILE_WIDTH 64
#define MAP_TILE_HEIGHT 64

#include <map>

#include "Tile.hpp"
#include "LuaInterface.hpp"
#include "Map.hpp"

/**
 * Load a map, save a map, change a map.
 */
class MapClass {
public:
    MapClass();

    /**
     * Loads tiles and set up lua-scripts.
     */
    void init();
    void draw();
    void update();
    /**
     * Make a call to the script that loads the tiles. Then we get the map from
     * the lua namespace.
     */
    bool loadMap(int id);

    /**
     * Will erase and delete all tiles of the map.
     */
    void clearCurrentMap();

    /**
     * Will create a new map and replace existing ones with same name.
     */
    void saveMap(std::map<int,std::shared_ptr<Texture>> *loadedMap,
                int mapID, int width, int height);

    /**
     * Saves all maps to files.
     */
    void saveMaps();

    /**
     * Sets the current map.
     */
    void setMap(std::shared_ptr<Map> tempMap);
    bool mapExists(int mapID);
    std::shared_ptr<Map> getMap(int mapID);

    void loadTile(int mapID, int id, int index, int x,int y);
    void loadEnvironment(int mapID, int id, int index, int x,int y);
    void loadEnemy(int mapID, int id, int index, int x,int y);

    void loadTileTexture(std::string img);
    void loadTileData(int id, std::string img, bool solid);

    void loadEnvironmentTexture(std::string img);
    void loadEnvironmentData(int id, std::string img, bool solid);

    void loadEnemyTexture(std::string img);
    void loadEnemyData(int id, std::string img, int hp,int level, int atk);

    void loadMapData(int id, int x,int y, int n,int e, int s, int w);
    void saveMap(int id, int x,int y, int n, int e, int s, int w);
    int getCurrentMap();
    void setCurrentMap(int id);
    int getMapID(int x, int y);

    Texture *tileAtIndex();
    void changeMap(const char *mapName);
    ~MapClass();
private:
    std::map<int,std::shared_ptr<Map>> mapContainer;
    LuaInterface l_interface;
    //std::map<int,std::shared_ptr<Texture>> *currentMap;
    std::shared_ptr<Map> currentMap;
    int currentMapID = 1;
    std::map<std::string, std::shared_ptr<Texture>> loadedTextures;
    std::map<int, std::string> tiles;
    std::map<int, std::string> environment;
    std::map<int, std::string> enemies;
};

#endif // MAPCLASS_H


