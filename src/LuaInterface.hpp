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

#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include <iostream>
#include <map>
#include <string>

#include "lua.hpp"

#include "Texture.hpp"

/* struct with some map-data. */
struct map_data {
    int width;
    int height;
    std::map<int,Texture*> textures;
};

struct inventoryItem {
    int id;
    int amount;
    int x;
    int y;
};


/* Functions used by lua and getters for data gathered with lua. */
namespace lua_functions {
    int loadTile(lua_State *l_state);
    int setDimensions(lua_State *l_state);
    int loadItem(lua_State *l_state);

    std::map<int,Texture*> *getCurrentMap();
    int getItemCount();
    inventoryItem* getItems();
    void setWater(Texture *water);
    void setGround(Texture *ground);
    void setGrass(Texture *grass);
    int getHeight();
    int getWidth();
}

/* Functions that will execute lua-scripts. */
class LuaInterface {
public:
    LuaInterface();

    void initLua();
    void report_errors(lua_State *l_State, int status);
    lua_State *getLua_State();
    bool load_File(const char *filename);
    void appendTile(const char *filename, int index, int x, int y,
                        int z, const char* image, int solid);
    void clearMapFile(const char *filename);
    void newMapFile(const char *filename,int width,int height);
    bool mapFileExist(const char *filename);

    void addItem(const char *filename,int id, int amount, int x, int y);
    void deleteItem(const char *filename,int id, int amount, int x, int y);
    void clearInventory(const char *filename);
    void newInventory(const char *filename);

    void load_tiles(const char *filename);
    void loadInventory(const char *filename);
    std::vector<std::pair<int,Texture*>> *getMap();
    virtual ~LuaInterface();
private:
    std::vector<std::pair<int,Texture*>> texture_map;
    lua_State *l_state;
};

#endif // LUAINTERFACE_H

