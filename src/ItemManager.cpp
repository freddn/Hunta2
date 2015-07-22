#include "ItemManager.hpp"

ItemManager::ItemManager() {
    //ctor
}

ItemManager::~ItemManager() {
    //dtor
}

void ItemManager::init() {
    lInterface.initLua();

    std::cerr << " ... Loading weapon data ..." << std::endl;
    lInterface.loadFile("data/items/weapons/weapons.lua");
    std::cerr << " ... Loading armor data ..." << std::endl;
    lInterface.loadFile("data/items/armor/armor.lua");
    std::cerr << " ... Loading misc item data ..." << std::endl;
    lInterface.loadFile("data/items/misc/misc.lua");
    std::cerr << " ... Loading usables data ..." << std::endl;
    lInterface.loadFile("data/items/usables/usables.lua");
}
