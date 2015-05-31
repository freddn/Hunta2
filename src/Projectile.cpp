#include "Projectile.hpp"
#include "Game.hpp"

Projectile::Projectile(int x,int y,int relX,int relY) {
    destX = relX;
    destY = relY;
    posX = x;
    posY = y;
    //ctor
}

Projectile::~Projectile()
{
    //dtor
    std::cerr << "projectile dead" << std::endl;
}



void Projectile::update() {
    //std::cerr << " - Projectile::update() ..."<<std::endl;
    int x = (int)(position->getX());
    int y = (int)(position->getY());
    if(x == posX || x > game::getWidth()*2 || x < 0) {
        entity->destroy();
    }
    if(y == posY || y > game::getHeight()*2 || y < 0) {
        entity->destroy();
    }
    //std::cerr << " - Projectile::update() ..."<<std::endl;
}

void Projectile::init() {
    std::cerr << " - Projectile::init() ...";
    position = &entity->getComponent<Position>();
    //texture = &entity->getComponent<Texture>();
    physics = &entity->getComponent<GPhysics>();

    physics->setDestX(destX);
    physics->setDestY(destY);

    std::cerr << " DONE"<<std::endl;
}

