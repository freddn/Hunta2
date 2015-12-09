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

/**
 * The physics of an entity. This class is a component and will
 * give an entity collision detection, velocity and movement.
 */
struct GPhysics : EntitySystem::Component {
public:
    GPhysics();

    /** Sets the velocity of the player and change the position accordingly. */
    void update();

    /** Gets the needed components. */
    void init();

    /** Clears all collision booleans. */
    void clearCol();

    /** Check for collision */
    bool isColliding(float x, float y); /// Current entity is inside this position?
    bool isColliding(EntitySystem::Entity *e); /// Current entity is colliding with given one?
    bool isColliding(SDL_Rect src, SDL_Rect dest); /// TODO Implement

    /** Getters. */
    SDL_Rect getColRect(); /// TODO Implement
    int getDir();
    float getXVel();
    float getYVel();
    int getDestX();
    int getDestY();

    /** Setters. */
    void setDir(int dir, bool isMoving);
    void setVelocity(float v);
    void setXVelocity();
    void setYVelocity();
    void setKeyControlled(bool keyControlled);
    void setDestX(int x);
    void setDestY(int y);

    virtual ~GPhysics();
private:
    bool dirUp = false;
    bool dirDown = false;
    bool dirLeft = false;
    bool dirRight = false;
    bool colUp = false;
    bool colDown = false;
    bool colLeft = false;
    bool colRight = false;
    bool movedByKey = false;
    int currentDir = 0;
    float destX = 0;
    float destY = 0;
    Position *position{nullptr};
    Texture *texture{nullptr};
    float xVel{0.0f};
    float yVel{0.0f};
    float vel{4};
    int north = 0;
    int south = 1;
    int west = 2;
    int east = 3;
};

#endif // GPHYSICS_H
