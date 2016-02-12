
#include "EnemyManager.hpp"

EnemyManager::EnemyManager() { }

EnemyManager::~EnemyManager() { }

void EnemyManager::loadEnemy(int id, std::string name, std::string img,
                             int hp, int level, int atk, int exp, int width, int height) {
    EnemyData data;
    data.id = id;
    data.name = name;
    data.img = img;
    data.hp = hp;
    data.exp = exp;
    data.level = level;
    data.atk = atk;
    data.width = width;
    data.height = height;

    enemies.emplace(std::pair<int, EnemyData>(id, data));
}

/** --------------- Getters --------------- */
int EnemyManager::getHp(int id){ return enemies.find(id) != enemies.end() ? enemies.at(id).hp : -1; }
int EnemyManager::getLevel(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).level : -1;}
int EnemyManager::getExperience(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).exp : -1;}
int EnemyManager::getAtk(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).atk : -1;}
int EnemyManager::getWidth(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).width : -1;}
int EnemyManager::getHeight(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).height : -1;}
std::string EnemyManager::getName(int id){return enemies.find(id) != enemies.end() ? enemies.at(id).name : "-";}
std::string EnemyManager::getImg(int id) {return enemies.find(id) != enemies.end() ? enemies.at(id).img : "-";}
EnemyData EnemyManager::getEnemyData(int id) { return enemies.at(id); }

std::map<int, EnemyData>*EnemyManager::getAllENemyData() { return &enemies;}