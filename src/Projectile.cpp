#include "Projectile.hpp"
#include "Game.hpp"

#include <cmath>

Projectile::Projectile(int x,int y,int relX,int relY) {
    destX = relX;
    destY = relY;
    posX = x;
    posY = y;
    timer.start();
}

Projectile::~Projectile() {}

void Projectile::update() {
    int x = std::abs( startX - (int)(position->getX()) );
    int y = std::abs( startY - (int)(position->getY()) );
    int d = std::sqrt(std::pow(x,2) + std::pow(y,2));

    /* Range of projectiles. */
    if(d > range)
        entity->destroy();
    if(timer.getTicks() > 50 && d < 5)
        entity->destroy();
}

void Projectile::init() {
    position = &entity->getComponent<Position>();
    physics = &entity->getComponent<GPhysics>();
    startX = position->getX();
    startY = position->getY();
    physics->setDestX(destX);
    physics->setDestY(destY);
}

void Projectile::setRange(int r) {
    range = r;
}
