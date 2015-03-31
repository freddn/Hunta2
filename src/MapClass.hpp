#ifndef MAPCLASS_H
#define MAPCLASS_H

#include <map>

#include "Tile.hpp"
#include "LuaInterface.hpp"
#include "LoadMapData.hpp"
#include "MapCreator.hpp"

/*
 * Load a map, save a map, change a map.
 */
class MapClass
{
    public:
        MapClass();
        void init(SDL_Renderer *renderer);
        bool loadMap(const char* filename);
        void saveMap(std::map<int,Texture*> loadedMap,
                    const char*filename, int width, int height);
        void insertTile(Texture *texture);
        void setMap(std::map<int,Texture*> textureMap);
        std::map<int,Texture*> getMap();

        Texture* tileAtIndex();
        Texture *getGrassTile();
        Texture *getGroundTile();
        Texture *getWaterTile();

        void changeMap(const char *mapName);
        virtual ~MapClass();
    protected:
    private:
    std::map<const char*,std::map<int,Texture*>> maps;
    std::map<int,Texture*> currentMap;
    LoadMapData mapLoader;
    MapCreator mapCreator;
    Texture grass_T;
    Texture ground_T;
    Texture water_T;
};

#endif // MAPCLASS_H

