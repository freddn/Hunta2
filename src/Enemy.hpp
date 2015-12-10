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

#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.hpp"
#include "GPhysics.hpp"
#include "Position.hpp"
#include "EntitySystem.hpp"
#include "LTimer.hpp"

using namespace EntitySystem;
/* The enemy class. */
struct Enemy : Component {
public:
    Enemy(EntityManager &m, int id);
    Enemy(EntityManager &m, int id, int exp, std::string name, int atk);

    void init();
    void draw();
    void update();
    void knockBack(int dir);
    void setExpGain(int xp);
    void setAggressive(bool aggressive);
    int getID();
    void onDeath();
    virtual ~Enemy();
protected:
private:

    GPhysics *physics{nullptr};
    Texture *texture{nullptr};
    Position *position{nullptr};

    EntityManager *manager{nullptr};
    std::string enemyName = "-";
    int xPos = 0; // x-position of the enemy.
    int yPos = 0; // y-position of the enemy.
    int xSpawnPos = 0;
    int ySpawnPos = 0;

    int enemyWidth = 0;
    int enemyHeight = 0;

    int experienceGain = 1;
    int enemyAttack = 0;
    int enemyID = -1;
    bool isAggressive = false;
    bool aggro = false;
    bool aggroX = true;
    bool aggroY = true;
    bool isKnockedBack = false;
    bool alive = true;
    int knockBackDir = 0;
    bool isAttacking = false;
    LTimer attackTimer;
    LTimer knockBackTimer;
    LTimer deathTimer;
};

#endif // ENEMY_H
