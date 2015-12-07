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
    manager = &m;
    enemyID = id;
}

Enemy::~Enemy() {}

void Enemy::init() {
    experienceGain = enemyID*5;
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

    if(alive) {
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
            int px = 0;
            int py = 0;
            int pw = 0;
            int ph = 0;
            if(!player.empty()) {
                px = player[0]->getComponent<Position>().getX();
                py = player[0]->getComponent<Position>().getY();
                pw = player[0]->getComponent<Texture>().getWidth();
                ph = player[0]->getComponent<Texture>().getHeight();
            }
            /* Check if player is near */
            if(position->getX() < px+100+pw &&
                position->getX()+enemyWidth > px-100 &&
                position->getY() < py+100+ph &&
                position->getY()+enemyHeight > py-100) {
                if(aggro == false)
                    aggro = true;
            } else {
                if(aggro == true)
                    aggro = false;
            }

            if(aggro) {     /* Follow player */
                if((position->getY()+5 > py &&
                    position->getY()+5 < py+ph) ||
                    (position->getY()+(enemyHeight-5) < py+ph &&
                    position->getY()+(enemyHeight-5) > py )) {
                    aggroY = false;
                    physics->setDestY(0);
                } else
                    aggroY = true;
                if((position->getX()+5 > px &&
                    position->getX()+5 < px+pw) ||
                    (position->getX()+(enemyWidth-5) < px+pw &&
                    position->getX()+(enemyWidth-5) > px )) {
                    aggroX = false;
                    physics->setDestX(0);
                }
                else
                    aggroX = true;

                if(position->getY()+enemyHeight-10 < py) {
                    if(aggroY)
                        physics->setDestY(py - (position->getY()+enemyHeight));
                    texture->setClipX(0);
                    texture->setClipY(0);
                } else if(position->getY()+10 > py+ph) {
                    if(aggroY)
                        physics->setDestY( (py+ph-5) - position->getY());
                    texture->setClipX(1);
                    texture->setClipY(0);
                }

                if(position->getX()+enemyWidth-10 < px) {
                    if(aggroX)
                        physics->setDestX(px - (position->getX()+enemyWidth-5));
                    texture->setClipX(1);
                    texture->setClipY(1);
                } else if(position->getX()+10 > px+pw) {
                    if(aggroX)
                        physics->setDestX((px-pw+5) - position->getX());
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
    } else {
        if(deathTimer.getTicks() > 1000)
            entity->destroy();
    }
}

void Enemy::setAggressive(bool aggressive) {
    isAggressive = aggressive;
}

void Enemy::knockBack(int dir) {
    knockBackDir = dir;
    isKnockedBack = true;
    isAggressive = true;
}

int Enemy::getID() {
    return enemyID;
}

void Enemy::onDeath() {
    /// Drop?
    /// Death animation?
    /// Corpse??
    alive = false;
    game::getPlayerController()->increaseExperience(experienceGain);
    deathTimer.start();
}
