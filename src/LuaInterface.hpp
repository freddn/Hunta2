#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include <iostream>
#include <map>
#include <string>

#include "lua5.1/lua.hpp"

#include "Texture.hpp"

/* struct with some map-data. */
struct map_data
{
    int width;
    int height;
    std::map<int,Texture*> textures;
};

/* Functions used by lua and getters for data gathered with lua. */
namespace lua_functions
{
    int loadTile(lua_State *l_state);
    int setDimensions(lua_State *l_state);
    std::map<int,Texture*> getCurrentMap();
    void setWater(Texture *water);
    void setGround(Texture *ground);
    void setGrass(Texture *grass);
    int getHeight();
    int getWidth();
}

/* Functions that will execute lua-scripts. */
class LuaInterface
{
    public:
        LuaInterface();

        void initLua();
        void report_errors(lua_State *l_State, int status);
        lua_State *getLua_State();
        bool load_File(const char *file);
        void appendTile(const char *map_name, int index, int x, int y, int z, const char* image, int solid);
        void clearMapFile(const char *filename);
        void newMapFile(const char *filename,int width,int height);
        bool mapFileExist(const char *filename);

        void load_tiles(const char *filename);
        std::map<int,Texture> getMap();
        virtual ~LuaInterface();
    private:
    std::map<int,Texture> texture_map;
    lua_State *l_state;
};

#endif // LUAINTERFACE_H

