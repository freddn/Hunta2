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
#include "HelperFunctions.hpp"

#include "LuaLoadFunctions.hpp"
#include "LuaGeneralFunctions.hpp"
#include "LuaInGameFunctions.hpp"

LuaInterface::LuaInterface() { }

void LuaInterface::initLua() {
    HelperFunctions::log("LuaInterface::initLua() ...");

    l_state = luaL_newstate();
    luaL_openlibs(l_state);

    loadFile("src/scripting/LoadMap.lua");
    loadFile("src/scripting/CreateMap.lua");
    loadFile("src/scripting/SaveChar.lua");

    thread = lua_newthread(l_state);
    int s = luaL_dofile(thread, "data/maps/1/map.lua");
    report_errors(thread, s);

    /* functions for loading saved data (maps, inventory, saved games, etc) */
    lua_register(l_state, "playerSavegame", lua_functions::playerSavegame);
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
    lua_register(l_state, "playerAddHp", lua_functions::playerAddHp);

    lua_register(l_state, "loadCharacter", lua_functions::loadCharacter);

    lua_register(thread, "getPlayerY", lua_functions::getPlayerY);
    lua_register(thread, "getPlayerX", lua_functions::getPlayerX);
    lua_register(thread, "yield", lua_functions::yield);
}

void LuaInterface::report_errors(lua_State *l_state, int status) {
    if(status != 0) {
        HelperFunctions::log(HelperFunctions::ERROR,lua_tostring(l_state,-1));
        lua_pop(l_state,1);
    }
}

lua_State *LuaInterface::getLua_State() {
    return l_state;
}

void LuaInterface::loadString(const char *code) {
    int s = luaL_loadstring(l_state, code);
    if(s == 0) {
        if((s = lua_pcall(l_state,0,LUA_MULTRET,0)) != 0) {
            std::stringstream err;
            err << "Could not execute lua-script: " << code;
            HelperFunctions::log(HelperFunctions::ERROR,err.str());
        }
    }
    report_errors(l_state,s);
}

bool LuaInterface::loadFile(const char *filename) {
    bool success = true;
    int s = luaL_loadfile(l_state,filename);
    if(s == 0) {
        if((s = lua_pcall(l_state,0,LUA_MULTRET,0)) != 0) {
            success = false;
            std::stringstream err;
            err << "Could not execute lua-script: " << filename;
            HelperFunctions::log(HelperFunctions::ERROR,err.str());
        }
    } else {
        success = false;
    }
    report_errors(l_state,s);
    return success;
}

void LuaInterface::saveCharacter(int saveslot, const char* charName, int level, int exp, int hp,
                                int currentHp, int atk, int def, int x, int y) {
    lua_pushstring(l_state,"SaveCharacter");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushnumber(l_state, saveslot);
    lua_pushstring(l_state, charName);
    lua_pushnumber(l_state, level);
    lua_pushnumber(l_state, exp);
    lua_pushnumber(l_state, hp);
    lua_pushnumber(l_state, currentHp);
    lua_pushnumber(l_state, atk);
    lua_pushnumber(l_state, def);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    int p = lua_pcall(l_state,10,0,0);
    report_errors(l_state,p);

}

void LuaInterface::clearSaveslots() {
    lua_pushstring(l_state,"ClearSaveSlots");

    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    int p = lua_pcall(l_state,0,0,0);
    report_errors(l_state,p);
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
}

void LuaInterface::newMapFile(int mapId, const char* filename) {
    HelperFunctions::log(HelperFunctions::ERROR, " - LuaInterface::newMapFile() ...");
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
    std::stringstream msg;
    msg << "LuaInterface::Map() ... map: " << mapID;
    HelperFunctions::log(HelperFunctions::MESSAGE, msg.str());

    std::string filename = "data/maps/" + std::to_string(mapID);
    std::string tiles = filename + "/tiles.lua";
    std::string enemies = filename + "/enemies.lua";
    std::string environment = filename + "/environment.lua";
    loadFile(tiles.c_str());
    loadFile(enemies.c_str());
    loadFile(environment.c_str());
}

void LuaInterface::loadInventory(const char *filename) {
    lua_pushstring(l_state,"loadInventory");
    lua_gettable(l_state,LUA_GLOBALSINDEX);
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

LuaInterface::~LuaInterface() {
    if(thread != nullptr)
        thread = nullptr;

    if(l_state != nullptr) {
        lua_close(l_state);
        l_state = nullptr;
    }

}

void LuaInterface::runLuaMain() {
    /*if(startedMain) {
        lua_resume(thread, 0);
    } else {*/
        //startedMain = true;
        lua_getglobal(thread, "Main");
        lua_call(thread,0,0);
    //}
}
