#include "Weapon.hpp"

#include "Game.hpp"


Weapon::Weapon() {
    //ctor
}

Weapon::Weapon(std::string img,EntityManager *mgr) {
    imgPath = img;
    //ctor
}

Weapon::~Weapon() {
    //dtor
}

void Weapon::init() {
    playerPosition = &entity->getComponent<Position>();
    weaponImage.setClipped(true);
    weaponImage.setClipH(32);
    weaponImage.setClipW(32);
    weaponImage.setClipX(0);
    weaponImage.setClipY(0);
    weaponImage.loadFromFile(game::getRenderer(),imgPath);
}

void Weapon::update() {
    //SDL_Event *event = game::getEvent();

    const Uint8 *key = SDL_GetKeyboardState(NULL);

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
    for(auto& e: manager->getEntitiesByGroup(game::ENEMY)) {
        Position temp = e->getComponent<Position>();
        int width = e->getComponent<Texture>().getWidth();
        int height = e->getComponent<Texture>().getHeight();

        if((position->getX()-10 < temp.getX()+width &&
                position->getX()+42 > temp.getX()) &&
                (position->getY()-10 < temp.getY()+height &&
                 position->getY()+42 > temp.getY())) {
            e->getComponent<HealthBar>().setHp(e->getComponent<HealthBar>().getHp()-4);
        }
    }
}

void Weapon::draw() {
    int posX = playerPosition->getX() + 16 - game::getOffset()->x;
    weaponImage.render(game::getRenderer(), posX,
                       playerPosition->getY() - game::getOffset()->y, nullptr);
}
