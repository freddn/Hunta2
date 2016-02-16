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

#include "lua.hpp"

/* Functions that will execute lua-scripts. */
class LuaInterface {
public:
    LuaInterface();

    void initLua();
    void report_errors(lua_State *l_State, int status);
    lua_State *getLua_State();
    bool loadFile(const char *filename);
    void saveCharacter(int saveslot, const char* charName, int level, int exp, int hp,
                                int currentHp, int atk, int def, int x, int y);
    void clearSaveslots();
    void appendMapData(const char* loadFunc, int mapId, const char* filename,
                        int id, int index, int x, int y);
    void appendMapDataInfo(const char* filename,int mapID,int x,int y,int n,int e,int s,int w);
    void clearMapFile(int mapID, const char* filename);
    void newMapFile(int mapID, const char* filename);
    void newMapDataFile(const char* filename);
    bool mapFileExist(int mapID, const char* filename);

    void addItem(const char *filename,int id, int amount, int x, int y);
    void deleteItem(const char *filename,int id, int amount, int x, int y);
    void clearInventory(const char *filename);
    void newInventory(const char *filename);

    void loadMap(int mapId);
    void loadInventory(const char *filename);

    void runLuaMain();

    lua_State *thread{nullptr};
    lua_State *l_state{nullptr};
    virtual ~LuaInterface();
private:
    //std::vector<std::pair<int,Texture*>> texture_map;

};

#endif // LUAINTERFACE_H

