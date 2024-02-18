#include "Weapon.hpp"

#include "../Global.hpp"
#include "../Enums.hpp"
#include "Health.hpp"
#include "Enemy.hpp"

Weapon::Weapon() {}

Weapon::Weapon(std::string img, EntitySystem::EntityManager &mgr) :
    manager(&mgr),
    imgPath(img) {
}

Weapon::~Weapon() {}

void Weapon::init() {
    playerPosition = &entity->getComponent<Position>();
    physics = &entity->getComponent<GPhysics>();
    seedTimer.start();
    weaponImage.setClipped(true);
    weaponImage.setClipH(32);
    weaponImage.setClipW(32);
    weaponImage.setClipX(0);
    weaponImage.setClipY(physics->getDir());
    weaponImage.loadFromFile(imgPath);
}

void Weapon::update() {
    const Uint8 *key = SDL_GetKeyboardState(NULL);

    weaponImage.setClipY(physics->getDir());

    if(key[SDL_SCANCODE_SPACE]) {
        if(!isAttacking)
            isAttacking = true;
    }

    if(isAttacking) {
        if(!attackTimer.isStarted())
            attackTimer.start();
        switch(attackState) {
        case 0:
            if(attackTimer.getTicks() > INTERVALL) {
                attackTimer.stop();
                attackState++;
            }
            break;
        case 1:
            if(attackTimer.getTicks() > INTERVALL) {
                attackTimer.stop();
                attackState++;
            }
            break;
        case 2:
            if(attackTimer.getTicks() > INTERVALL) {
                attackTimer.stop();
                attackState++;
            }
            break;
        case 3:
            /* Damage to enemies */
            if(attackTimer.getTicks() > INTERVALL) {
                attackTimer.stop();
                attack();
                attackState++;
            }
            break;
        case 4:
            if(attackTimer.getTicks() > INTERVALL*3) {
                attackTimer.stop();
                attackState = 0;
                isAttacking = false;
            }
            break;
        default:
            attackState = 0;
            isAttacking = false;
            break;
        }
        weaponImage.setClipX(attackState);
    }
}

bool Weapon::attack() {
    bool hit = false;
    // If this is a player:
    int seed = 12345;
    seed += seedTimer.getTicks();
    for(auto& e: manager->getEntitiesByGroup(game::ENEMY)) {
        int ex = e->getComponent<Position>().getX();
        int ey = e->getComponent<Position>().getY();
        int ew = e->getComponent<Texture>().getWidth();
        int eh = e->getComponent<Texture>().getHeight();

        if((ex < weaponImage.getX()+weaponImage.getWidth()+game::getOffset()->x &&
            ex+ew > weaponImage.getX()+game::getOffset()->x) &&
           (ey < weaponImage.getY()+weaponImage.getHeight()+game::getOffset()->y &&
            ey+eh > weaponImage.getY()+game::getOffset()->y)) {

            e->getComponent<Health>().damage(
                    atk+game::getPlayerController()->getAtk(),ex+ey+seed);
            e->getComponent<Enemy>().knockBack(physics->getDir());
            hit = true;
            seed -= 1237;
        }
    }
    return hit;
}

void Weapon::draw() {
    int posX = 0;
    int posY = 0;
    switch(physics->getDir()) {
    case game::NORTH:
        posY = playerPosition->getY() - 16 - game::getOffset()->y;
        weaponImage.render(playerPosition->getX() - game::getOffset()->x,
                            posY, nullptr);
        break;
    case game::SOUTH:
        posY = playerPosition->getY() + 16 - game::getOffset()->y;
        weaponImage.render(playerPosition->getX() - game::getOffset()->x,
                            posY, nullptr);
        break;
    case game::WEST:

        posX = playerPosition->getX() - 16 - game::getOffset()->x;
        weaponImage.render(posX, playerPosition->getY() - game::getOffset()->y,
                            nullptr);
        break;
    case game::EAST:
        posX = playerPosition->getX() + 16 - game::getOffset()->x;
        weaponImage.render(posX, playerPosition->getY() - game::getOffset()->y,
                            nullptr);
        break;
    }
}
