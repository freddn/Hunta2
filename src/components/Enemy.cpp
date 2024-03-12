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

#include "../Global.hpp"
#include "../Enums.hpp"
#include "../common/HelperFunctions.hpp"

Enemy::Enemy(EntitySystem::EntityManager &m, int id) : manager(&m){
    enemyID = id;
}

Enemy::Enemy(EntitySystem::EntityManager &m, int id, int exp, std::string name, int atk) :
                        manager(&m), enemyName(name){
    enemyID = id;
    experienceGain = exp;
    enemyAttack = atk;
}

Enemy::~Enemy() {}

void Enemy::init() {
    enemyAttack = game::getEnemyDataController()->getAtk(enemyID);
    experienceGain = game::getEnemyDataController()->getExperience(enemyID);

    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
    enemyHeight = texture->getHeight();
    enemyWidth = texture->getWidth();
    xSpawnPos = position->getX();
    ySpawnPos = position->getY();

    physics = &entity->getComponent<GPhysics>();
    physics->setVelocity(1);

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
                physics->setDestY(-4);
                break;
            case game::SOUTH:
                physics->setDestY(4);
                break;
            case game::WEST:
                physics->setDestX(-4);
                break;
            case game::EAST:
                physics->setDestX(4);
                break;
            default:
                break;
            }
        } else if(isAggressive) {
            auto& player(manager->getEntitiesByGroup(game::PLAYER));
            float px = 0;
            float py = 0;
            float pw = 0;
            float ph = 0;
            if(!player.empty()) {
                px = player[0]->getComponent<Position>().getX();
                py = player[0]->getComponent<Position>().getY();
                pw = player[0]->getComponent<Texture>().getWidth();
                ph = player[0]->getComponent<Texture>().getHeight();
            }
            /* Check if player is near */
            if(!aggro)
                aggro = position->getX() < px + 100 + pw &&
                        position->getX()+enemyWidth > px-100 &&
                        position->getY() < py+100+ph &&
                        position->getY()+enemyHeight > py-100;

            if(aggro) {     /* Follow player */
                if((position->getY()-5 > py &&
                    position->getY()+5 < py+ph) ||
                    (position->getY()+(enemyHeight+10) < py+ph &&
                    position->getY()+(enemyHeight-5) > py )) {
                    aggroY = false;
                    physics->setDestY(0);
                    isAttacking = true;
                } else
                    aggroY = true;
                if((position->getX()+5 > px &&
                    position->getX()+5 < px+pw) ||
                    (position->getX()+(enemyWidth-5) < px+pw &&
                    position->getX()+(enemyWidth-5) > px )) {
                    aggroX = false;
                    physics->setDestX(0);
                    isAttacking = true;
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
                if(isAttacking) {
                    if(!attackTimer.isStarted()) {
                        attackTimer.start();
                        player[0]->getComponent<Health>().damage(
                                enemyAttack, game::getTimer()->getTicks());
                        game::getPlayerController()->setCurrentHp(
                                player[0]->getComponent<Health>().getHp());
                    } else if(attackTimer.getTicks() > 800) {
                        attackTimer.stop();
                        isAttacking = false;
                    }
                }
            } else {        /* Return home */
                aggroX = true;
                aggroY = true;
                physics->setDestX(0);
                physics->setDestY(0);

                if(position->getX() < xSpawnPos-10) {
                    physics->setDestX(2);
                    texture->setClipX(1);
                } else if(position->getX() > xSpawnPos+10) {
                    physics->setDestX(-2);
                    texture->setClipX(0);
                }
                if(position->getY() < ySpawnPos-10) {
                    physics->setDestY(2);
                } else if(position->getY() > ySpawnPos+10) {
                    physics->setDestY(-2);
                }
            }
        }
    } else {
        if(deathTimer.getTicks() > 1000)
            entity->destroy();
    }
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
    /**
     * TODO Implement a lootManager and enemy loot tables with drop rates.
     */
    int rgn = HelperFunctions::random(1,9,game::getTimer()->getTicks());
    if(rgn < 3)
        game::getTextureMapController()->getMap(1)->loadItem(rgn,position->getX(),position->getY(),1);
    else if(rgn == 5)
        game::getTextureMapController()->getMap(1)->loadItem(100,position->getX(),position->getY(),1);
    else if(rgn == 7)
        game::getTextureMapController()->getMap(1)->loadItem(200,position->getX(),position->getY(),1);
    else if(rgn == 9)
        game::getTextureMapController()->getMap(1)->loadItem(300,position->getX(),position->getY(),1);

    alive = false;
    game::getPlayerController()->increaseExperience(experienceGain);
    knockBackTimer.stop();
    isKnockedBack = false;
    deathTimer.start();
}
