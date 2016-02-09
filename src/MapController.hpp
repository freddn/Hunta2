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
 * Load maps, save maps, change map.
 */
class MapController {
public:
    MapController();

    /**
     * Loads tiles and set up lua-scripts.
     */
    void init(LuaInterface *lInterface);

    /**
     * Used to draw the map currently on screen.
     */
    void draw();

    /**
     * Updates the map and everything on it.
     */
    void update();
    /**
     * Make a call to the script that loads the tiles. Then we get the map from
     * the lua namespace.
     */
    bool loadMap(int id);

    /**
     * Will erase and delete all tiles of the map. TODO Remove?
     */
    void clearCurrentMap();

    /**
     * Will create a new map and replace existing ones with same name.
     */
    void saveMap(std::map<int,std::shared_ptr<Texture>> *loadedMap,
                int mapID, int width, int height); // TODO Implement this? (got saveMaps)

    /**
     * Saves all maps and their data to files.
     */
    void saveMaps();

    /**
     * Sets the current map. TODO Remove or use?
     */
    void setMap(std::shared_ptr<Map> tempMap);
    void clearMap(int mapID); // TODO Remove or fix?

    /**
     * Check if map exists.
     */
    bool mapExists(int mapID);

    /**
     * Returns a pointer to the map with given id.
     */
    std::shared_ptr<Map> getMap(int mapID);

    /**
     * Loads a tile with given id on given map at position (x,y)
     */
    void loadTile(int mapID, int id, int index, int x,int y);

    /**
     * Load environmental stuff on given map at position (x,y)
     */
    void loadEnvironment(int mapID, int id, int index, int x,int y);

    /**
     * Loads an enemy on given map at position (x,y)
     */
    void loadEnemy(int mapID, int id, int index, int x,int y);

    void loadTileTexture(std::string img); // TODO Use this?

    /**
     * Load tile data.
     */
    void loadTileData(int id, std::string img, bool solid);

    void loadEnvironmentTexture(std::string img); // TODO Use this?

    /**
     * Load environment data.
     */
    void loadEnvironmentData(int id, std::string img, bool solid);

    void loadEnemyTexture(std::string img); // TODO Use this?

    /**
     * Load enemy data.
     */
    void loadEnemyData(int id, std::string img); // TODO Maby move away from map mechanics

    /**
     * Loads a map and register neighbour maps.
     */
    void loadMapData(int id, int x,int y, int n,int e, int s, int w);

    void saveMap(int id, int x,int y, int n, int e, int s, int w); // TODO Use this?

    /**
     * Returns the map id of the current map.
     */
    int getCurrentMap();

    /**
     * Used when changing map.
     */
    void setCurrentMap(int id);

    /**
     * Returns a map id which correspond to the given position.
     */
    int getMapID(int x, int y);

    Texture *tileAtIndex(); // TODO Remove?

    void changeMap(const char *mapName); // TODO Implement

    ~MapController();
private:
    std::map<int,std::shared_ptr<Map>> mapContainer;
    LuaInterface *lInterface{nullptr};
    std::shared_ptr<Map> currentMap;
    int currentMapID = 1;
    std::map<std::string, std::shared_ptr<Texture>> loadedTextures;
    std::map<int, std::string> tiles; // Here we store image names to all tiles.
    std::map<int, std::string> environment; // Image names for environment.
    std::map<int, std::string> enemies; // Image names for enemies.
};

#endif // MAPCLASS_H


