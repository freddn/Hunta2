
#include "PlayerController.hpp"
#include <cmath>
#include <iostream>

PlayerController::PlayerController() {
    //ctor
}

PlayerController::PlayerController(std::string n) : playerName(n) {
}

PlayerController::~PlayerController() {
    //dtor
}

void PlayerController::draw() {
    /// Draw exp and hpbar
    /// Draw name also..

}

void PlayerController::init() {
    /// Load inventory and char data..

}

void PlayerController::save(LuaInterface *lInterface) {
    lInterface->saveCharacter(playerName.c_str(),level,experience,hp,currentHp,atk,def,posX,posY);
}

void PlayerController::load(std::string name, LuaInterface *lInterface) {
    playerName = name;
    std::string filepath = "data/savedata/" + name + ".lua";
    lInterface->loadFile(filepath.c_str());
}


/** --------------- Getters --------------- */

int PlayerController::getHp() {
    return hp;
}

int PlayerController::getCurrentHp() {
    return currentHp;
}

int PlayerController::getLevel() {
    return level;
}

int PlayerController::getExperience() {
    return experience;
}

int PlayerController::getDef() {
    return def;
}

int PlayerController::getAtk() {
    return atk;
}

int PlayerController::getPosX() {
    return posX;
}

int PlayerController::getPosY() {
    return posY;
}

std::string PlayerController::getName() {
    return playerName;
}

int getMaxExperience(int lv) {
    // return 16+std::pow(lv, 3) / 2; // Bigger exp curve
    return (int)(16+std::pow(lv, 2.5) / 2); // More linear than above
}

/** --------------- Setters --------------- */

void PlayerController::increaseExperience(int e) {
    std::cout << "-- Got " << e << " xp! --" << std::endl;
    setExperience(experience+e);
}

void PlayerController::setExperience(int e) {
    if(e >= getMaxExperience(level)) {
        level+=1;
        int inc = e - getMaxExperience(level-1);
        experience = 0;
        if(inc > 0) {
            setExperience(inc);
        }
        std::cout << "-----------------------------\n"<<
                     "|         LEVELUP!!!\n"<<
                     "|          "<<level<<"\n" <<
                     "-----------------------------" <<std::endl;
    } else {
        experience = e;
        std::cout << "!! LV: "<< level<<" XP: " << experience << "/" << getMaxExperience(level)<<" !!"<< std::endl;
    }
}

void PlayerController::setLevel(int l) {
    level = l;
}

void PlayerController::setHp(int h) {
    hp = h;
}

void PlayerController::setCurrentHp(int h) {
    currentHp = h;
}

void PlayerController::setDef(int d) {
    def = d;
}

void PlayerController::setAtk(int a) {
    atk = a;
}

void PlayerController::setPosX(int x) {
    posX = x;
}

void PlayerController::setPosY(int y) {
    posY = y;
}

void PlayerController::setName(std::string name) {
    playerName = name;
}


