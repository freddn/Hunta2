#include "ItemManager.hpp"
#include <iostream>

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

/*
void ItemManager::loadArmor(int id, std::string name, int levelReq, std::string img,
                            std::string desc, int price, int atk, int def,int hp) {



}
void ItemManager::loadWeapon(int id, std::string name, int levelReq, std::string img,
                            std::string desc, int price, int atk, int def, int hp) {

}
void ItemManager::loadUsable(int id, std::string name, int levelReq, int stackSize,
                            std::string img, std::string desc, int price, int heal) {


}
void ItemManager::loadMisc(int id, std::string name, int stackSize, std::string img,
                            std::string desc, int price) {


}
*/

