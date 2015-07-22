#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "LuaInterface.hpp"


class ItemManager {
public:
    ItemManager();

    void init();

    void loadArmor(int id, std::string name, int levelReq, std::string img,
                    std::string desc, int price, int atk, int def,int hp);
    void loadWeapon(int id, std::string name, int levelReq, std::string img,
                    std::string desc, int price, int atk, int def, int hp);
    void loadUsable(int id, std::string name, int levelReq, int stackSize,
                    std::string img, std::string desc, int price, int heal);
    void loadMisc(int id, std::string name, int stackSize, std::string img,
                    std::string desc, int price);
    virtual ~ItemManager();
protected:
private:
    LuaInterface lInterface;
};

#endif // ITEMMANAGER_H
