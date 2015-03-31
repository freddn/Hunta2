#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <map>

#include "Texture.hpp"
#include "LuaInterface.hpp"

/*
 * Will create a new map.
 */
class MapCreator
{
    public:
        MapCreator();
        void init();
        void newMap(std::map<int,Texture*> currentMap,
                    const char*filename, int width, int height);

        virtual ~MapCreator();
    protected:
    private:
    LuaInterface l_interface;

};

#endif // MAPCREATOR_H

