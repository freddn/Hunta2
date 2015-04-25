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

#ifndef GPHYSICS_H
#define GPHYSICS_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "Texture.hpp"

/*
 * The physics of an object. This class is a component and will
 * give an entity collision detection, velocity and movement.
 */
struct GPhysics : EntitySystem::Component
{
    public:
        GPhysics();
        void update();
        void init();
        void clearCol();
        bool isColliding(int x, int y);
        bool isColliding(EntitySystem::Entity *e);
        void setDir(int dir, bool isMoving);
        void setVelocity(float v);
        void setXVelocity();
        void setYVelocity();
        float getXVel();
        float getYVel();

        virtual ~GPhysics();
    protected:
    private:

        bool dirUp = false;
        bool dirDown = false;
        bool dirLeft = false;
        bool dirRight = false;
        bool colUp = false;
        bool colDown = false;
        bool colLeft = false;
        bool colRight = false;
        Position *position{nullptr};
        Texture *texture{nullptr};
        float xVel{0.0f};
        float yVel{0.0f};
        float vel{4};
};

#endif // GPHYSICS_H
