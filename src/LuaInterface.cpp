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

#include "LuaInterface.hpp"

#include "Game.hpp"

namespace lua_functions {

    inventoryItem items[20]; /* */
    int itemNo = 0;

    int loadTile(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadTile(mapID,id,index,x,y);
            return 0;
        }
        return 0;
    }

    int loadEnemy(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadEnemy(mapID,id,index,x,y);
            return 0;
        }
        return 0;
    }

    int loadEnvironment(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadEnvironment(mapID,id,index,x,y);
            return 0;
        }
        return 0;
    }

    int loadItem(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            inventoryItem temp;
            temp.id =  lua_tonumber(l_state,2);
            temp.amount = lua_tonumber(l_state,3);
            temp.x = lua_tonumber(l_state,4);
            temp.y = lua_tonumber(l_state,5);

            if(itemNo > 19) {
                std::cerr << "Too many items in inventory" << std::endl;
                return 1;
            }
            items[itemNo] = temp;
            itemNo++;
        }
        return 0;
    }

    /// ASSET LOADING
    int loadTileData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 3) {
            int id = lua_tonumber(l_state,1); // id
            std::string img = lua_tostring(l_state,2); // image
            int solid = lua_tonumber(l_state,3); // solid
            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadTileData(id,img,solid == 1);
            game::getEditor()->loadIcon(img,id,game::TILE);
        }
        return 0;
    }

    int loadEnvironmentData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 3) {
            int id = lua_tonumber(l_state,1); // id
            std::string img = lua_tostring(l_state,2); // image
            int solid = lua_tonumber(l_state,3); // solid
            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadEnvironmentData(id,img,solid == 1);
            game::getEditor()->loadIcon(img,id,game::ENVIRONMENT);
        }
        return 0;
    }

    int loadArmorData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            //int id = lua_tonumber(l_state,1); // id
            //std::string name = lua_tostring(l_state,2); // name
            //int level = lua_tonumber(l_state,3); // id
            //std::string img = lua_tostring(l_state,4); // image
            //std::string desc = lua_tostring(l_state,5); // desc
            //int price = lua_tonumber(l_state,6); // price
            //int atk = lua_tonumber(l_state,7); // atk
            //int def = lua_tonumber(l_state,8); // def
            //int hp = lua_tonumber(l_state,9); // hp
        }
        return 0;
    }

    int loadUsablesData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 8) {
            //int id = lua_tonumber(l_state,1); // id
            //std::string name = lua_tostring(l_state,2); // name
            //int level = lua_tonumber(l_state,3);
            //int maxStack = lua_tonumber(l_state,4);
            //std::string img = lua_tostring(l_state,5); // image
            //std::string desc = lua_tostring(l_state,6); // desc
            //int price = lua_tonumber(l_state,7); // price
            //int heal = lua_tonumber(l_state,8); // atk
        }
        return 0;
    }

    int loadWeaponsData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            //int id = lua_tonumber(l_state,1); // id
            //std::string name = lua_tostring(l_state,2); // name
            //int level = lua_tonumber(l_state,3); // id
            //std::string img = lua_tostring(l_state,4); // image
            //std::string desc = lua_tostring(l_state,5); // desc
            //int price = lua_tonumber(l_state,6); // price
            //int atk = lua_tonumber(l_state,7); // atk
            //int def = lua_tonumber(l_state,8); // def
            //int hp = lua_tonumber(l_state,9); // hp
        }
        return 0;
    }

    int loadMapData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 7) {
            int id = lua_tonumber(l_state,1); // id
            int x = lua_tonumber(l_state,2); // x pos
            int y = lua_tonumber(l_state,3); // y pos
            int north = lua_tonumber(l_state,4); // north
            int east = lua_tonumber(l_state,5); // east
            int south = lua_tonumber(l_state,6); // south
            int west = lua_tonumber(l_state,7); // west
            game::getTextureMapController()->loadMapData(id,x,y,north,east,south,west);
        }
        return 0;
    }

    int loadEnemiesData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int id = lua_tonumber(l_state,1); // id
            std::string img = lua_tostring(l_state,2); // image
            //int hp = lua_tonumber(l_state,3); // hp
            //int level = lua_tonumber(l_state,4); // level
            //int atk = lua_tonumber(l_state,5); // atk
            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadEnemyData(id,img);
            game::getEditor()->loadIcon(img,id,game::ENEMY);
        }
        return 0;
    }

    int loadMiscItemData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 6) {
            //int id = lua_tonumber(l_state,1); // id
            //std::string name = lua_tostring(l_state,2); // name
            //int maxStack = lua_tonumber(l_state,3); // stack
            //std::string img = lua_tostring(l_state,4); // image
            //std::string desc = lua_tostring(l_state,5); // desc
            //int sellprice = lua_tonumber(l_state,6); // price
        }
        return 0;
    }

    int getItemCount() {
        return itemNo;
    }

    inventoryItem* getItems() {
        return items;
    }
}

LuaInterface::LuaInterface() { }

void LuaInterface::initLua() {
    std::cout << " - LuaInterface::initLua() ..." << std::endl;
    l_state = luaL_newstate();
    luaL_openlibs(l_state);

    /// functions for loading saved data (maps, inventory)
    lua_register(l_state, "loadTile", lua_functions::loadTile);
    lua_register(l_state, "loadEnemy", lua_functions::loadEnemy);
    lua_register(l_state, "loadEnvironment", lua_functions::loadEnvironment);
    lua_register(l_state, "loadItem", lua_functions::loadItem);
    //lua_register(l_state, "loadInventory", lua_functions::loadInventory);

    /// functions for loading assets.. (images, stats, etc.)
    lua_register(l_state, "loadMapData", lua_functions::loadMapData);

    lua_register(l_state, "loadTileData", lua_functions::loadTileData);
    lua_register(l_state, "loadEnvironmentData", lua_functions::loadEnvironmentData);
    lua_register(l_state, "loadArmorData", lua_functions::loadArmorData);
    lua_register(l_state, "loadUsablesData", lua_functions::loadUsablesData);
    lua_register(l_state, "loadWeaponData", lua_functions::loadWeaponsData);
    lua_register(l_state, "loadEnemyData", lua_functions::loadEnemiesData);
    lua_register(l_state, "loadMiscItemData", lua_functions::loadMiscItemData);
}

void LuaInterface::report_errors(lua_State *l_state, int status) {
    if(status != 0) {
        std::cerr << " - " << lua_tostring(l_state,-1) << std::endl;
        lua_pop(l_state,1);
    }
}

lua_State *LuaInterface::getLua_State() {
    return l_state;
}

bool LuaInterface::loadFile(const char *filename) {
    bool success = true;
    int s = luaL_loadfile(l_state,filename);
    if(s == 0) {
        if((s = lua_pcall(l_state,0,LUA_MULTRET,0)) != 0) {
            success = false;
            std::cerr << "Could not execute lua-script: " << filename << std::endl;
        }
    } else {
        success = false;
    }
    report_errors(l_state,s);
    //std::cerr << std::endl;
    return success;
}

void LuaInterface::appendMapData(const char* loadFunc, int mapId, const char* filename,int id,
                                int index, int x, int y) {
    lua_pushstring(l_state,"AppendMapData");

    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state, loadFunc);
    lua_pushnumber(l_state, mapId);
    lua_pushstring(l_state, filename);
    lua_pushnumber(l_state, id);
    lua_pushnumber(l_state, index);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    int p = lua_pcall(l_state,7,0,0);
    report_errors(l_state,p);
    //std::cout << std::endl;
}
void LuaInterface::appendMapDataInfo(const char* filename, int mapId, int x,int y,
                                int n, int e, int s, int w) {
    lua_pushstring(l_state,"AppendMapDataInfo");

    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state, filename);
    lua_pushnumber(l_state, mapId);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    lua_pushnumber(l_state, n);
    lua_pushnumber(l_state, e);
    lua_pushnumber(l_state, s);
    lua_pushnumber(l_state, w);
    int p = lua_pcall(l_state,8,0,0);
    report_errors(l_state,p);
    //std::cout << std::endl;
}

void LuaInterface::clearMapFile(int mapID, const char* filename) {
    lua_pushstring(l_state,"ClearMapFile");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushnumber(l_state,mapID);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,2,0,0);
    report_errors(l_state,p);
    //std::cout << std::endl;
}

void LuaInterface::newMapFile(int mapId, const char* filename) {
    std::cout << " - LuaInterface::newMapFile() ..."<<std::endl;
    lua_pushstring(l_state,"NewMapFile");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1 working
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushnumber(l_state,mapId);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,2,0,0);
    report_errors(l_state,p);
}

void LuaInterface::newMapDataFile(const char* filename) {
    lua_pushstring(l_state,"NewMapDataFile");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1 working
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

bool LuaInterface::mapFileExist(int mapID, const char* filename) {
    bool exists = false;
    lua_pushstring(l_state,"MapFileExist");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushnumber(l_state,mapID);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,2,0,0);
    report_errors(l_state,p);
    if(lua_tonumber(l_state,-1) == 1) {
        exists = true;
    }
    return exists;
}

void LuaInterface::addItem(const char *filename,int id,
                            int amount, int x, int y) {
    lua_pushstring(l_state,"AddItem");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    lua_pushnumber(l_state, id);
    lua_pushnumber(l_state, amount);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    int p = lua_pcall(l_state,5,0,0);
    report_errors(l_state,p);
}

void LuaInterface::deleteItem(const char *filename,int id,
                                int amount, int x, int y) {
    lua_pushstring(l_state,"DeleteItem");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    lua_pushnumber(l_state, id);
    lua_pushnumber(l_state, amount);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    int p = lua_pcall(l_state,5,0,0);
    report_errors(l_state,p);
}

void LuaInterface::clearInventory(const char *filename) {
    lua_pushstring(l_state,"ClearInventory");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

void LuaInterface::newInventory(const char *filename) {
    lua_pushstring(l_state,"NewInventory");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

void LuaInterface::loadMap(int mapID) {

    std::cout << " - LuaInterface::Map() ... map: "<< mapID << std::endl;

    std::string filename = "data/maps/" + std::to_string(mapID);
    std::string tiles = filename + "/tiles.lua";
    std::string enemies = filename + "/enemies.lua";
    std::string environment = filename + "/environment.lua";
    loadFile(tiles.c_str());
    loadFile(enemies.c_str());
    loadFile(environment.c_str());
}

void LuaInterface::loadInventory(const char *filename) {
    for(int i = 0;i<20;i++) {
        lua_functions::items[i].id = -1;
        lua_functions::items[i].amount = -1;
        lua_functions::items[i].x = -1;
        lua_functions::items[i].y = -1;
    }

    lua_functions::itemNo = 0;

    lua_pushstring(l_state,"loadInventory");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

LuaInterface::~LuaInterface() {
    lua_close(l_state);
}
