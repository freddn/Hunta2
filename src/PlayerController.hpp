#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <string>

#include "Health.hpp"
#include "Character.hpp"
#include "LuaInterface.hpp"

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

    virtual ~PlayerController();
protected:
private:
    std::string playerName;

    Texture hpBar;
    Texture expBar;

    /// Stats
    int level = 1;
    int experience = 0;
    int atk = 1;
    int def = 1;
    int hp = 15;
    int currentHp = hp;
    int posX = 50;
    int posY = 50;

    int temp = 0;
};

#endif // PLAYERCONTROLLER_H
