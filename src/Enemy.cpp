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

#include "Game.hpp"

Enemy::Enemy(EntityManager &m, int id) {
    //ctor
    manager = &m;
    enemyID = id;
}

Enemy::~Enemy() {
    //dtor
}

void Enemy::init() {
    //std::cout << " - Enemy::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
    enemyHeight = texture->getHeight();
    enemyWidth = texture->getWidth();
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

    int playerH = 0;
    int playerW = 0;
    if(isKnockedBack) {
        if(!knockBackTimer.isStarted())
            knockBackTimer.start();
        if(knockBackTimer.getTicks() > 25) {
            isKnockedBack = false;
            knockBackTimer.stop();
        }
        switch(knockBackDir) {
        case game::NORTH:
            position->setY(position->getY()-4);
            break;
        case game::SOUTH:
            position->setY(position->getY()+4);
            break;
        case game::WEST:
            position->setX(position->getX()-4);
            break;
        case game::EAST:
            position->setX(position->getX()+4);
            break;
        }
    } else if(isAggressive) {
        auto& player(manager->getEntitiesByGroup(game::PLAYER));
        if(!player.empty()) {
            playerPos = player[0]->getComponent<Position>();
            playerW = player[0]->getComponent<Texture>().getWidth();
            playerH = player[0]->getComponent<Texture>().getHeight();
        }
        /* Check if player is near */
        if(position->getX() < playerPos.getX()+100+playerW &&
            position->getX()+enemyWidth > playerPos.getX()-100 &&
            position->getY() < playerPos.getY()+100+playerH &&
            position->getY()+enemyHeight > playerPos.getY()-100) {
            if(aggro == false) {
                aggro = true;
                /* FIXME: Replace the position with an ID. */
            }
        } else {
            if(aggro == true) {
                aggro = false;
                /* FIXME: Replace the position with an ID. */
            }
        }

        if(aggro) {     /* Follow player */
            if((position->getY()+5 > playerPos.getY() &&
                position->getY()+5 < playerPos.getY()+playerH) ||
                (position->getY()+(enemyHeight-5) < playerPos.getY()+playerH &&
                position->getY()+(enemyHeight-5) > playerPos.getY() )) {
                aggroY = false;
                physics->setDestY(0);
            } else
                aggroY = true;
            if((position->getX()+5 > playerPos.getX() &&
                position->getX()+5 < playerPos.getX()+playerW) ||
                (position->getX()+(enemyWidth-5) < playerPos.getX()+playerW &&
                position->getX()+(enemyWidth-5) > playerPos.getX() )) {
                aggroX = false;
                physics->setDestX(0);
            }
            else
                aggroX = true;

            if(position->getY()+enemyHeight-10 < playerPos.getY()) {
                if(aggroY)
                    physics->setDestY(playerPos.getY() - (position->getY()+enemyHeight));
                texture->setClipX(0);
                texture->setClipY(0);
            } else if(position->getY()+10 > playerPos.getY()+playerH) {
                if(aggroY)
                    physics->setDestY( (playerPos.getY()+playerH-5) - position->getY());
                texture->setClipX(1);
                texture->setClipY(0);
            }

            if(position->getX()+enemyWidth-10 < playerPos.getX()) {
                if(aggroX)
                    physics->setDestX(playerPos.getX() - (position->getX()+enemyWidth-5));
                texture->setClipX(1);
                texture->setClipY(1);
            } else if(position->getX()+10 > playerPos.getX()+playerW) {
                if(aggroX)
                    physics->setDestX((playerPos.getX()-playerW+5) - position->getX());
                texture->setClipX(0);
                texture->setClipY(1);
            }
        } else {        /* Return home */
            aggroX = true;
            aggroY = true;
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
}

void Enemy::setAggressive(bool aggressive) {
    isAggressive = aggressive;
}

void Enemy::knockBack(int dir) {
    knockBackDir = dir;
    isKnockedBack = true;
}

int Enemy::getID() {
    return enemyID;
}

void Enemy::onDeath() {
    /// Drop?
    /// Death animation?
    /// Corpse??
    entity->destroy();
}
