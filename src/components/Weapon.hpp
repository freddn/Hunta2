#ifndef WEAPON_H
#define WEAPON_H

#define INTERVALL 40

#include "../EntitySystem.hpp"
#include "Texture.hpp"
#include "GPhysics.hpp"
#include "../LTimer.hpp"

using namespace EntitySystem;


/**
 * This class represents a weapon that enemys and players will have.
 */
struct Weapon : Component {
public:
    Weapon();
    Weapon(std::string img, EntityManager &mgr);

    /** Will draw the weapon texture. */
    void draw();

    /** Update the weapon and check if attacking. */
    void update();

    /** Load the texture and set it's position accordingly to the character. */
    void init();

    bool attack();

    /** Will change weapon to a given new one. */
    void changeWeapon(int wId);

    virtual ~Weapon();
private:
    Position *playerPosition{nullptr};
    GPhysics *physics{nullptr};

    EntityManager *manager{nullptr};

    int weaponX = 0;
    int weaponY = 0;
    LTimer seedTimer;
    LTimer attackTimer;
    Texture weaponImage;
    std::string imgPath = "";
    bool isAttacking = false;
    int attackState = 0;
    int atk = 5; /// Weapon attack
    int minAtk = 0;
};

#endif // WEAPON_H
