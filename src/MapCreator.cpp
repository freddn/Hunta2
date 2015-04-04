#include "MapCreator.hpp"

MapCreator::MapCreator()
{

}

MapCreator::~MapCreator()
{
    //dtor
}

void MapCreator::init()
{
    std::cout << " - MapCreator::init() ..."<<std::endl;
    l_interface.initLua();
    l_interface.load_File("src/CreateMap.lua");
}

void MapCreator::newMap(std::map<int,Texture*> currentMap,
            const char*filename, int width, int height)
{
    std::cout << " - MapCreator::newMap() ..."<<std::endl;
    l_interface.newMapFile(filename,width,height);
    for(auto iter = currentMap.begin(); iter != currentMap.end();iter++)
    {
        l_interface.appendTile(
                    filename,
                    ((int)iter->first),
                    (int)((int)(((Texture*)iter->second)->getRect().x) /
                    (int)(((Texture*)iter->second)->getWidth())),
                    (int)((int)(((Texture*)iter->second)->getRect().y) /
                    (int)(((Texture*)iter->second)->getHeight())),
                    0,
                    ((Texture*)iter->second)->getImgPath().c_str(),
                    ((Texture*)iter->second)->isSolid());
    }
}


