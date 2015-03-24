#ifndef LOADMAPDATA_H
#define LOADMAPDATA_H

#include "LuaInterface.hpp"


/**
    Import map-data. (lua/plaintext?)
*/
class LoadMapData
{
    public:
        LoadMapData();
        void init();
        void insertTiles();
        std::map<int,Texture*> getMap(const char* filename);
        virtual ~LoadMapData();
    protected:
    private:
    LuaInterface l_interface;
};

#endif // LOADMAPDATA_H





