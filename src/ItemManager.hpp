#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "lua/LuaInterface.hpp"
#include <map>

/**
 * A general struct for item data.
 */
struct ItemData {
    int id;
    std::string name;
    std::string img;
    std::string desc;
};

/**
 * Armor data.
 */
struct ArmorItem : ItemData{
    int levelReq;
    int atk;
    int def;
    int hp;
    int price;
};

/**
 * Weapon data.
 */
struct WeaponItem : ItemData {
    int levelReq;
    int atk;
    int def;
    int hp;
    int price;
};

/**
 * Usables data.
 */
struct UsableItem : ItemData {
    int levelReq;
    int stackSize;
    int heal;
    int price;
    std::string script;
};

/**
 * Misc data.
 */
struct MiscItem : ItemData {
    int stackSize;
    int price;
};

/**
 * Will store information about items. When loaded we use get functions to get
 * references to the item objects that we can use to get information.
 */
class ItemManager {
public:
    ItemManager();

    /**
     * We need lua here to load the file with item information.
     */
    void init(LuaInterface *lInterface);

    /**
     * Load an armor item and save it to the manager.
     */
    void loadArmor(int id, const std::string &name, int levelReq, const std::string &img,
                   const std::string &desc, int price, int atk, int def,int hp);

    /**
     * Load a weapon and save it to the manager.
     */
    void loadWeapon(int id, const std::string &name, int levelReq, const std::string &img,
                    const std::string &desc, int price, int atk, int def, int hp);

    /**
     * Load an usable item and save it to the manager.
     */
    void loadUsable(int id, const std::string &name, int levelReq,
                    int stackSize, const std::string &img,
                    const std::string &desc, int price, int heal,
                    const std::string &script);

    /**
     * Load an misc item and save it to the manager.
     */
    void loadMisc(int id, const std::string &name, int stackSize, const std::string &img,
                  const std::string &desc, int price);

    /**
     * Getters for different types of items.
     */
    ArmorItem &getArmor(int id);
    WeaponItem &getWeapon(int id);
    UsableItem &getUsable(int id);
    MiscItem &getMisc(int id);
    ItemData &getItem(int id);

    virtual ~ItemManager();
private:
    LuaInterface *lInterface{nullptr};

    std::map<int, std::string> armorImages;
    std::map<int, std::string> weaporImages;
    std::map<int, std::string> usableImages;
    std::map<int, std::string> miscImages;

    std::map<int, ArmorItem> armor;
    std::map<int, WeaponItem> weapons;
    std::map<int, UsableItem> usables;
    std::map<int, MiscItem> misc;
};

#endif // ITEMMANAGER_H
