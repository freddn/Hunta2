#include "Projectile.hpp"
#include "Game.hpp"

#include <cmath>

Projectile::Projectile(int x,int y,int relX,int relY) {
    destX = relX;
    destY = relY;
    posX = x;
    posY = y;
    timer.start();
    //ctor
}

Projectile::~Projectile()
{
    //dtor
    //std::cerr << "projectile dead" << std::endl;
}



void Projectile::update() {
    //std::cerr << " - Projectile::update() ..."<<std::endl;
    int x = std::abs( startX - (int)(position->getX()) );
    int y = std::abs( startY - (int)(position->getY()) );
    int d = std::sqrt(std::pow(x,2) + std::pow(y,2));

    /* Range of projectiles. */
    if(d > range)
        entity->destroy();
    if(timer.getTicks() > 50 && d < 5)
        entity->destroy();
    /*if(x > startX + 100 || x > game::getWidth()*2 || x < 0) {
        entity->destroy();
    }
    if(y == posY || y > game::getHeight()*2 || y < 0) {
        entity->destroy();
    }*/
    //std::cerr << " - Projectile::update() ..."<<std::endl;
}

void Projectile::init() {
    //std::cerr << " - Projectile::init() ...";
    position = &entity->getComponent<Position>();
    //texture = &entity->getComponent<Texture>();
    physics = &entity->getComponent<GPhysics>();
    startX = position->getX();
    startY = position->getY();
    physics->setDestX(destX);
    physics->setDestY(destY);

    //std::cerr << " DONE"<<std::endl;
}

void Projectile::setRange(int r) {
    range = r;
}
