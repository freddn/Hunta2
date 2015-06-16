#ifndef MELEE_H
#define MELEE_H

#include "Weapon.hpp"

/** DONT KNOW IF NEEDED, WILL LEAVE IT HERE JUST IN CASE */

class Melee : Weapon {
public:
    Melee(std::string img);
    void init();

    virtual ~Melee();
protected:
private:
};

#endif // MELEE_H
