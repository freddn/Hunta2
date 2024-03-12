#include "ItemManager.hpp"
#include "../common/HelperFunctions.hpp"

ItemManager::ItemManager() {}

ItemManager::~ItemManager() {}

void ItemManager::init(LuaInterface *lInterface) {
    this->lInterface = lInterface;
    HelperFunctions::log("Loading item data ...");
    lInterface->loadFile("data/items/items.lua");
}


void ItemManager::loadArmor(int id, const std::string &name, int levelReq, const std::string &img,
                            const std::string &desc, int price, int atk, int def,int hp) {
    ArmorItem armorItem;
    armorItem.atk = atk;
    armorItem.id = id;
    armorItem.name = name;
    armorItem.levelReq = levelReq;
    armorItem.img = img;
    armorItem.desc = desc;
    armorItem.price = price;
    armorItem.def = def;
    armorItem.hp = hp;

    armor.emplace(std::pair<int, ArmorItem>(id, armorItem));
}
void ItemManager::loadWeapon(int id, const std::string &name, int levelReq, const std::string &img,
                             const std::string &desc, int price, int atk, int def, int hp) {
    WeaponItem weaponItem;
    weaponItem.atk = atk;
    weaponItem.id = id;
    weaponItem.name = name;
    weaponItem.levelReq = levelReq;
    weaponItem.img = img;
    weaponItem.desc = desc;
    weaponItem.price = price;
    weaponItem.def = def;
    weaponItem.hp = hp;

    weapons.emplace(std::pair<int, WeaponItem>(id, weaponItem));
}
void ItemManager::loadUsable(int id, const std::string &name, int levelReq,
                             int stackSize, const std::string &img,
                             const std::string &desc, int price, int heal,
                             const std::string &script) {
    UsableItem usableItem;
    usableItem.id = id;
    usableItem.name = name;
    usableItem.levelReq = levelReq;
    usableItem.stackSize = stackSize;
    usableItem.img = img;
    usableItem.desc = desc;
    usableItem.price = price;
    usableItem.heal = heal;
    usableItem.script = script;

    usables.emplace(std::pair<int, UsableItem>(id, usableItem));
}
void ItemManager::loadMisc(int id, const std::string &name, int stackSize, const std::string &img,
                           const std::string &desc, int price) {
    MiscItem miscItem;
    miscItem.id = id;
    miscItem.name = name;
    miscItem.stackSize = stackSize;
    miscItem.img = img;
    miscItem.desc = desc;
    miscItem.price = price;

    misc.emplace(std::pair<int, MiscItem>(id, miscItem));
}

ArmorItem &ItemManager::getArmor(int id) { return armor.at(id); }

WeaponItem &ItemManager::getWeapon(int id) { return weapons.at(id); }

UsableItem &ItemManager::getUsable(int id) { return usables.at(id); }

MiscItem &ItemManager::getMisc(int id) { return misc.at(id); }

ItemData &ItemManager::getItem(int id) {
    if (id>=300)
        return misc.at(id);
    else if(id>=200)
        return usables.at(id);
    else if(id>=100)
        return armor.at(id);
    else
        return weapons.at(id);

}
