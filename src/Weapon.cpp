#include "Weapon.hpp"

#include "Game.hpp"
#include "HealthBar.hpp"


Weapon::Weapon() {
    //ctor
}

Weapon::Weapon(std::string img,EntityManager &mgr) {
    imgPath = img;
    manager = &mgr;
    //ctor
}

Weapon::~Weapon() {
    //dtor
}

void Weapon::init() {
    playerPosition = &entity->getComponent<Position>();
    physics = &entity->getComponent<GPhysics>();
    weaponImage.setClipped(true);
    weaponImage.setClipH(32);
    weaponImage.setClipW(32);
    weaponImage.setClipX(0);
    weaponImage.setClipY(physics->getDir());
    weaponImage.loadFromFile(game::getRenderer(),imgPath);
}

void Weapon::update() {
    //SDL_Event *event = game::getEvent();

    const Uint8 *key = SDL_GetKeyboardState(NULL);

    weaponImage.setClipY(physics->getDir());


    if(key[SDL_SCANCODE_SPACE]) {
        if(!isAttacking)
            isAttacking = true;
    }

    if(isAttacking) {
        switch(attackState) {
        case 0:
            if(!attackTimer.isStarted())
                attackTimer.start();
            if(attackTimer.getTicks() > INTERVALL) {
                attackState++;
                attackTimer.stop();
            }
            weaponImage.setClipX(attackState);
            break;
        case 1:
            if(!attackTimer.isStarted())
                attackTimer.start();
            if(attackTimer.getTicks() > INTERVALL) {
                attackState++;
                attackTimer.stop();
            }
            weaponImage.setClipX(attackState);
            break;
        case 2:
            if(!attackTimer.isStarted())
                attackTimer.start();
            if(attackTimer.getTicks() > INTERVALL) {
                attackState++;
                attackTimer.stop();
            }
            weaponImage.setClipX(attackState);
            break;
        case 3:
            /* Damage to enemies */
            if(!attackTimer.isStarted())
                attackTimer.start();
            if(attackTimer.getTicks() > INTERVALL) {
                //std::cout << "Attack!" << std::endl;
                attack();
                attackState++;
                attackTimer.stop();
            }
            weaponImage.setClipX(attackState);
            break;
        case 4:
            if(!attackTimer.isStarted())
                attackTimer.start();
            if(attackTimer.getTicks() > INTERVALL) {
                attackState = 0;
                attackTimer.stop();
                isAttacking = false;
            }
            weaponImage.setClipX(attackState);

            break;
        default:
            attackState = 0;
            weaponImage.setClipX(attackState);
            isAttacking = false;
            break;
        }
    }
}

bool Weapon::attack() {
    bool hit = false;
    // If this is a player:
    for(auto& e: manager->getEntitiesByGroup(game::ENEMY)) {
        Position enemyPos = e->getComponent<Position>();
        int width = e->getComponent<Texture>().getWidth();
        int height = e->getComponent<Texture>().getHeight();
        /* Right attack */


        if((enemyPos.getX() < weaponImage.getX()+weaponImage.getWidth()+game::getOffset()->x &&
            enemyPos.getX()+width > weaponImage.getX()+game::getOffset()->x) &&
           (enemyPos.getY() < weaponImage.getY()+weaponImage.getHeight()+game::getOffset()->y &&
            enemyPos.getY()+height > weaponImage.getY()+game::getOffset()->y)) {
            e->getComponent<HealthBar>().setHp(e->getComponent<HealthBar>().getHp()-4);
            hit = true;
        }
    }
    return hit;
}

void Weapon::draw() {
    int posX = 0;
    int posY = 0;
    switch(physics->getDir()) {
    case game::NORTH:
        posY = playerPosition->getY() - 24 - game::getOffset()->y;
        weaponImage.render(game::getRenderer(),
                            playerPosition->getX() - game::getOffset()->x,
                            posY, nullptr);
        break;
    case game::SOUTH:
        posY = playerPosition->getY() + 24 - game::getOffset()->y;
        weaponImage.render(game::getRenderer(),
                            playerPosition->getX() - game::getOffset()->x,
                            posY, nullptr);
        break;
    case game::WEST:

        posX = playerPosition->getX() - 24 - game::getOffset()->x;
        weaponImage.render(game::getRenderer(), posX,
                       playerPosition->getY() - game::getOffset()->y, nullptr);
        break;
    case game::EAST:
        posX = playerPosition->getX() + 24 - game::getOffset()->x;
        weaponImage.render(game::getRenderer(), posX,
                       playerPosition->getY() - game::getOffset()->y, nullptr);
        break;

    }


}
