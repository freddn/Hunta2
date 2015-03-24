#include "LoadMapData.hpp"


using namespace lua_functions;

LoadMapData::LoadMapData()
{
    //std::map<int,Texture*> mamppp = lua_functions::getCurrentMap();

    //l_interface.newMapFile("data/map233",width/32,height/32);


    //l_interface.load_tiles("data/map1");

    //l_interface.getTile();

    // Testing lua functionallity..


}

LoadMapData::~LoadMapData()
{
    //dtor
}

void LoadMapData::init()
{
    l_interface.initLua();
    l_interface.load_File("src/LoadMap.lua");
}

void LoadMapData::insertTiles()
{

}

void insertTile()
{


}

std::map<int,Texture*> LoadMapData::getMap(const char* filename)
{
    std::cout << "getMap: "<<filename << std::endl;
    l_interface.load_tiles(filename);

    return lua_functions::getCurrentMap();
}

void setMap()
{

}







