
#ifndef HUNTA2_ENEMYCONTROLLER_H
#define HUNTA2_ENEMYCONTROLLER_H

#include <string>

#include "components/Health.hpp"
#include "components/Character.hpp"
#include "lua/LuaInterface.hpp"

struct EnemyData {
    int id;
    std::string name;
    std::string img;
    int level;
    int exp;
    int atk;
    int hp;
    int width;
    int height;
};

/**
 * Handles the enemy information.
 */
class EnemyManager {
public:
    EnemyManager();
    EnemyManager(std::string n);

    void draw();
    void init();
    void loadEnemy(int id, std::string name, std::string img,
                   int hp, int level, int atk,int exp, int width,int height);

    /** --------------- Getters --------------- */
    int getHp(int id);
    int getLevel(int id);
    int getExperience(int id);
    int getDef(int id);
    int getAtk(int id);
    int getWidth(int id);
    int getHeight(int id);
    std::string getName(int id);
    std::string getImg(int id);
    EnemyData getEnemyData(int id);
    std::map<int, EnemyData>* getAllENemyData();

    /** --------------- Setters --------------- */
    void setExperience(int e);
    void setLevel(int l);
    void setHp(int h);
    void setCurrentHp(int h);
    void setDef(int d);
    void setAtk(int a);
    void setPosX(int x);
    void setPosY(int y);
    void setName(std::string name);

    virtual ~EnemyManager();
protected:
private:
    std::map<int, EnemyData> enemies;
};


#endif //HUNTA2_ENEMYCONTROLLER_H
