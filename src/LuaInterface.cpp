#include "LuaInterface.hpp"


namespace lua_functions
{
    map_data current_map_data;

    Texture *grass_T;
    Texture *water_T;
    Texture *ground_T;

    int loadTile(lua_State *l_state)
    {
        int argc = lua_gettop(l_state);
        //std::cout << "loadTile(), loading tile.. \n";
        if(argc == 7)
        {
            Texture *temp;
            //const char* name = lua_tostring(l_state,1); // filename
            int index = lua_tonumber(l_state,2); // index
            int x = lua_tonumber(l_state,3); // x
            int y = lua_tonumber(l_state,4); // y
            //int z = lua_tonumber(l_state,5); // z
            std::string img = lua_tostring(l_state,6); // image
            bool solid = lua_tonumber(l_state,7); // solid


            if(img.compare(grass_T->getImgPath()) == 0)
            {
                temp = grass_T->clone();
            }
            else if(img.compare(ground_T->getImgPath()) == 0)
            {
                temp = ground_T->clone();
            }
            else if(img.compare(water_T->getImgPath()) == 0)
            {
                temp = water_T->clone();
            }
            else
            {
                temp = grass_T->clone();
            }
            temp->setXPos(x*temp->getWidth());
            temp->setYPos(y*temp->getHeight());
            temp->setXRect(x*temp->getWidth());
            temp->setYRect(y*temp->getHeight());
            if(solid == 1)
                temp->setSolid(true);

            //std::cout << temp->getImgPath() << std::endl;
            current_map_data.textures.insert(std::pair<int,Texture*>(index,temp));
            //std::cout << "Loading tile: ";
        }
        //std::cout << std::endl;
        return 1;
    }
    int setDimensions(lua_State *l_state)
    {
        std::cout << "loading tile.. \n";
        int argc = lua_gettop(l_state);
        if(argc == 2)
        {
            current_map_data.width = lua_tonumber(l_state,1);
            current_map_data.height = lua_tonumber(l_state,2);
        }
        return 1;
    }

    std::map<int,Texture*> getCurrentMap()
    {
        return current_map_data.textures;
    }

    int getWidth()
    {
        return current_map_data.width;
    }

    int getHeight()
    {
        return current_map_data.height;
    }
    void setGrass(Texture *grass)
    {
        grass_T = grass;
    }

    void setGround(Texture *ground)
    {
        ground_T = ground;
    }

    void setWater(Texture *water)
    {
        water_T = water;
    }

}


LuaInterface::LuaInterface()
{

}

void LuaInterface::initLua()
{
    std::cout << "initLua" << std::endl;
    l_state = luaL_newstate();
    luaL_openlibs(l_state);
    lua_register(l_state, "loadTile", lua_functions::loadTile);
    lua_register(l_state, "setDimensions", lua_functions::setDimensions);
}

void LuaInterface::report_errors(lua_State *l_state, int status)
{
    if(status != 0)
    {
        std::cerr << "-- " << lua_tostring(l_state,-1) << std::endl;
        lua_pop(l_state,1);
    }
}

lua_State *LuaInterface::getLua_State()
{
    return l_state;
}

bool LuaInterface::load_File(const char *file)
{
    bool success = true;
    std::cout << "loadFile:" << file << std::endl;
    int s = luaL_loadfile(l_state,file);
    std::cout << "loadedFile:" << file << ", " <<s<< std::endl;
    if(s == 0)
    {
        if((s = lua_pcall(l_state,0,LUA_MULTRET,0)) != 0)
        {
            success = false;
            std::cout << "Could not execute lua-program.";
        }
    }
    else
    {
        success = false;
    }
    report_errors(l_state,s);
    //std::cerr << std::endl;
    return success;
}

void LuaInterface::appendTile(const char* map_name, int index, int x,
                            int y, int z, const char* image, int solid)
{
    lua_pushstring(l_state,"AppendTile");

    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state,map_name);
    lua_pushnumber(l_state, index);
    lua_pushnumber(l_state, x);
    lua_pushnumber(l_state, y);
    lua_pushnumber(l_state, z);
    lua_pushstring(l_state,image);
    lua_pushnumber(l_state, solid);
    int p = lua_pcall(l_state,7,0,0);
    report_errors(l_state,p);
    //std::cout << std::endl;
}

void LuaInterface::clearMapFile(const char *filename)
{
    lua_pushstring(l_state,"ClearMapFile");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
    //std::cout << std::endl;
}

void LuaInterface::newMapFile(const char *filename,int width,int height)
{
    lua_pushstring(l_state,"NewMapFile");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1 working
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state,filename);
    lua_pushnumber(l_state,width);
    lua_pushnumber(l_state,height);
    int p = lua_pcall(l_state,3,0,0);
    report_errors(l_state,p);
}

bool LuaInterface::mapFileExist(const char *filename)
{
    bool exists = false;
    lua_pushstring(l_state,"MapFileExist");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_pushglobaltable(l_state); // lua5.2 not working
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
    if(lua_tonumber(l_state,-1) == 1)
    {
        exists = true;
    }
    return exists;
}

void LuaInterface::load_tiles(const char *filename)
{

    std::cout << "loadTiles:" << filename << std::endl;
    lua_pushstring(l_state,"getTiles");
    lua_gettable(l_state,LUA_GLOBALSINDEX); // lua5.1
    //lua_getglobal(l_state,"_G"); // lua5.2 not working
    //lua_rawgeti(l_state, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS); // lua5.2 not working
    //lua_pushglobaltable(l_state);  // lua5.2 not working
    lua_pushstring(l_state,filename);
    int p = lua_pcall(l_state,1,0,0);
    report_errors(l_state,p);
}

LuaInterface::~LuaInterface()
{
    lua_close(l_state);
}
