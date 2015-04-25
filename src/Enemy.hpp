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

#include "Game.hpp"
#include "Texture.hpp"
#include "GPhysics.hpp"
#include "Position.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;
/* The enemy class. */
struct Enemy : Component
{
    public:
        Enemy(EntityManager *m);

        void init();
        void draw();
        void update();

        virtual ~Enemy();
    protected:
    private:

        GPhysics *physics{nullptr};
        Texture *texture{nullptr};
        Position *position{nullptr};

        EntityManager *manager{nullptr};

        int xPos; // x-position of the enemy.
        int yPos; // y-position of the enemy.
        int xSpawnPos;
        int ySpawnPos;

        int enemyID = -1;

        bool aggro;
};

#endif // ENEMY_H
