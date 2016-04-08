#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <string>

#include "components/Health.hpp"
#include "lua/LuaInterface.hpp"

/**
 * Handles the characters data.
 */
class PlayerController {
public:
    PlayerController();
    PlayerController(std::string n);

    void draw();
    void init();
    void save(LuaInterface *lInterface);
    void save(LuaInterface *lInterface, int slot);
    void load(std::string name, LuaInterface *lInterface);

    /** --------------- Getters --------------- */
    int getHp();
    int getCurrentHp();
    int getLevel();
    int getExperience();
    int getDef();
    int getAtk();
    int getPosX();
    int getPosY();
    std::string getName();
    int getMaxExperience(int lv);
    bool getHealthChanged();

    /** --------------- Setters --------------- */
    void increaseExperience(int e);
    void setExperience(int e);
    void setLevel(int l);
    void setHp(int h);
    void setCurrentHp(int h);
    void setDef(int d);
    void setAtk(int a);
    void setPosX(int x);
    void setPosY(int y);
    void setName(std::string name);
    void setHealthChanged(bool flag);
    void increaseHp(int h);

    virtual ~PlayerController();
protected:
private:
    int getMaxHp(int lv);
    std::string playerName;

    Texture hpBar;
    Texture expBar;

    /// Stats
    int hpBase = 15;
    int level = 1;
    int experience = 0;
    int atk = 1;
    int def = 1;
    int hp = 15;
    int currentHp = hp;
    int posX = 50;
    int posY = 50;

    bool healthChanged;
};

#endif // PLAYERCONTROLLER_H
