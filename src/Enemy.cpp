/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 *
 * This file is a part of the Hunta2 project.
 *
 * Hunta2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hunta2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include "Enemy.hpp"

Enemy::Enemy(EntityManager *m) {
    //ctor
    manager = m;
}

Enemy::~Enemy() {
    //dtor
}

void Enemy::init() {
    std::cout << " - Enemy::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();

    xSpawnPos = position->getX();
    ySpawnPos = position->getY();

    physics = &entity->getComponent<GPhysics>();
    physics->setVelocity(2);

    aggro = false;
}

void Enemy::draw() {
}

void Enemy::update() {
    Position playerPos;
    auto& player(manager->getEntitiesByGroup(game::PLAYER));
    playerPos = player[0]->getComponent<Position>();

    /* Check if player is near */
    if(playerPos.getX()+132 > position->getX() &&
        playerPos.getX()-100 < position->getX() &&
        playerPos.getY()+132 > position->getY() &&
        playerPos.getY()-100 < position->getY()) {
        if(aggro == false) {
            aggro = true;
            /* FIXME: Replace the position with an ID. */
            std::cerr << "!aggro from enemy at pos " << position->getX() <<
                "," << position->getY() << std::endl;
        }
    }
    else {
        if(aggro == true) {
            aggro = false;
            /* FIXME: Replace the position with an ID. */
            std::cerr << "!no aggro from enemy at pos " << position->getX() <<
                "," << position->getY() << std::endl;
        }
    }

    if(aggro) {     /* Follow player */
        //std::cerr << "x: "<< playerPos.getX() - position->getX() << std::endl;
        //std::cerr << "y: "<< playerPos.getY() - position->getY() << std::endl;
        physics->setDestX(playerPos.getX() - position->getX());
        physics->setDestY(playerPos.getY() - position->getY());

        if(position->getY()+32 < playerPos.getY()) {
            //position->setY(position->getY() + 1);
            texture->setClipX(0);
            texture->setClipY(0);
        } else if(position->getY()-32 > playerPos.getY()) {
            //position->setY(position->getY() - 1);
            texture->setClipX(1);
            texture->setClipY(0);
        }
        if(position->getX()+32 < playerPos.getX()) {
            //position->setX(position->getX() + 1);
            texture->setClipX(1);
            texture->setClipY(1);
        } else if(position->getX()-32 > playerPos.getX()) {
            //position->setX(position->getX() - 1);
            texture->setClipX(0);
            texture->setClipY(1);
        }
    } else {        /* Return home */
        physics->setDestX(0.f);
        physics->setDestY(0.f);

        if(position->getX() < xSpawnPos-1) {
            position->setX(position->getX() + 1);
            texture->setClipX(1);
        } else if(position->getX() > xSpawnPos+1) {
            position->setX(position->getX() - 1);
            texture->setClipX(0);
        }
        if(position->getY() < ySpawnPos-1) {
            position->setY(position->getY() + 1);
        } else if(position->getY() > ySpawnPos+1) {
            position->setY(position->getY() - 1);
        }
    }
}



