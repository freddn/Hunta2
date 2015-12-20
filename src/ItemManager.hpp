#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "LuaInterface.hpp"
#include <map>

struct ItemData {
    int id;
    std::string name;
    std::string img;
    std::string desc;
};

struct ArmorItem : ItemData{
    int levelReq;
    int atk;
    int def;
    int hp;
    int price;
};


struct WeaponItem : ItemData {
    int levelReq;
    int atk;
    int def;
    int hp;
    int price;
};


struct UsableItem : ItemData {
    int levelReq;
    int stackSize;
    int heal;
    int price;
    std::string script;
};

struct MiscItem : ItemData {
    int stackSize;
    int price;
};

class ItemManager {
public:
    ItemManager();

    void init(LuaInterface *lInterface);

    void loadArmor(int id, const std::string &name, int levelReq, const std::string &img,
                   const std::string &desc, int price, int atk, int def,int hp);
    void loadWeapon(int id, const std::string &name, int levelReq, const std::string &img,
                    const std::string &desc, int price, int atk, int def, int hp);
    void loadUsable(int id, const std::string &name, int levelReq,
                    int stackSize, const std::string &img,
                    const std::string &desc, int price, int heal,
                    const std::string &script);
    void loadMisc(int id, const std::string &name, int stackSize, const std::string &img,
                  const std::string &desc, int price);

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
