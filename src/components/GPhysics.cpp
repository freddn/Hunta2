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

#include "GPhysics.hpp"

#include "Environment.hpp"
#include "../Global.hpp"
#include "../Enums.hpp"
#include <iostream>

/** TODO Add collision rect.
 * (Setters and getters and change in collision management)*/


GPhysics::GPhysics() {
    //ctor
}

GPhysics::~GPhysics() {
    body->destroy();
    //dtor
}

void GPhysics::update() {
   /* for(auto &e : &entity->manager->getEntitiesByGroup(game::ENVIRONMENT))
    {
        e->getComponent<Position>();
    }*/
    setYVelocity();
    setXVelocity();
    //body->velocity.x = xVel;
    //body->velocity.y = yVel;

    //body->force.x = -xVel;
    //body->force.y = -yVel;
    body->applyForce(Vec2(xVel,yVel));

    position->setX(body->position.x-(texture->getWidth()/2));
    position->setY(body->position.y-texture->getHeight()+5);
    /*if(xVel != 0)
        position->setX(position->getX()+xVel);
    if(yVel != 0)
        position->setY(position->getY()+yVel);
*/
    //clearCol();
}

void GPhysics::init() {
    //std::cout << " - GPhysics::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();

    currentDir = game::SOUTH;
    north = game::NORTH;
    south = game::SOUTH;
    west = game::WEST;
    east = game::EAST;

    Vec2 min(position->getX(), position->getY());
    Vec2 max(position->getX()+texture->getWidth(), position->getY()+texture->getHeight());
    aabb.min = min;
    aabb.max = max;

    circle.radius = 8;
    body = game::getPhysicsEngine()->add(&circle,position->getX(), position->getY()-32);
    if(entity->hasComponent<Environment>()) {
        body->setStatic();
    }

}

/*bool GPhysics::isColliding(int x, int y) {

    return false;
}*/

bool GPhysics::isColliding(EntitySystem::Entity *e) {
    int posX = position->getX();
    int posY = position->getY();

    /// TODO sourceCol = physics->getColRect();

    int entPosX = e->getComponent<Position>().getX();
    int entPosY = e->getComponent<Position>().getY();

    /// TODO targetCol = e->getComponent<GPhysics>().getColRect();
    //Texture *tempTexture = &e->getComponent<Texture>();

    int entW = e->getComponent<Texture>().getWidth();
    int entH = e->getComponent<Texture>().getHeight();

    bool colliding = false;

    if(dirRight) {
        if(posX+33 > entPosX &&
            posX+16 < entPosX &&
            (posY+22+(vel) > entPosY ||
            posY+14-(vel) < entPosY+entH) &&
            !(posY+14-(vel) < entPosY ||
            posY+22+(vel) > entPosY+entH)) {
            colRight = true;
            colliding = true;
        }
    }

    if(dirLeft) {
        if(posX-1 < entPosX+entW &&
            posX+16 > entPosX &&
            (posY+22+(vel) > entPosY ||
            posY+14-(vel) < entPosY+entH) &&
            !(posY+14-(vel) < entPosY ||
            posY+22+(vel) > entPosY+entH)) {

            colLeft = true;
            colliding = true;
        }
    }

    if(dirDown) {
        if(posY+14 > entPosY &&
            (posY < entPosY) &&
            (posX+(vel) > entPosX ||
            posX+32-(vel) < entPosX+entW) &&
            !(posX+32-(vel) < entPosX ||
            posX+(vel) > entPosX+entW)) {
            colDown = true;
            colliding = true;
        }
    }

    if(dirUp) {
        if(posY+22 < entPosY+entH &&
            (posY > entPosY+16) &&
            (posX+(vel) > entPosX ||
            posX+32-(vel) < entPosX+entW) &&
            !(posX+32-(vel) < entPosX ||
            posX+(vel) > entPosX+entW)) {
            colUp = true;
            colliding = true;
        }
    }
    return colliding;
}


inline void GPhysics::clearCol() {
    colDown = false;
    colUp = false;
    colLeft = false;
    colRight = false;
}

void GPhysics::setDir(int dir, bool isMoving) {
    if(dir == north) {
        if (isMoving)
            currentDir = dir;
        dirUp = isMoving;
    } else if(dir == south) {
        if (isMoving)
            currentDir = dir;
        dirDown = isMoving;
    } else if(dir == east) {
        if (isMoving)
            currentDir = dir;
        dirRight = isMoving;
    } else if(dir == west) {
        if (isMoving)
            currentDir = dir;
        dirLeft = isMoving;
    }
}

void GPhysics::setVelocity(float v) {
    vel = v;
}

inline void GPhysics::setXVelocity() {
    if(!movedByKey) {
        if(destX != 0) {
            if(destY != 0) {
                float dY = std::abs(destY);
                float dX = std::abs(destX);
                xVel = dX / (dY + dX) * vel;
            } else
                xVel = vel;
            if(destX<0)
                xVel*=-1;
        } else
            xVel = 0;
    } else {
        if(!dirUp && !dirDown) {
            if(dirLeft && !colLeft)
                xVel = -vel;
            else if(dirRight && !colRight)
                xVel = vel;
            else
                xVel = 0;
        } else if(dirUp || dirDown) {
            if(dirLeft && !colLeft)
                xVel = -sqrt(pow(vel,2.0) / 2);
            else if(dirRight && !colRight)
                xVel = sqrt(pow(vel,2.0) / 2);
            else
                xVel = 0;
        }
    }
}

inline void GPhysics::setYVelocity() {
    if(!movedByKey) {
        if(destY != 0) {
            if(destX != 0) {
                float dY = std::abs(destY);
                float dX = std::abs(destX);
                yVel = dY / (dY + dX) * vel;
               // yVel = sqrt(yVel);
            } else
                yVel = vel;
            if(destY<0)
                yVel*=-1;
        } else
            yVel = 0.0;
    } else {
        if(!dirLeft && !dirRight) {
            if(dirUp && !colUp)
                yVel = -vel;
            else if(dirDown && !colDown)
                yVel = vel;
            else
                yVel = 0;
        } else if(dirLeft || dirRight) {
            if(dirUp && !colUp)
                yVel = -sqrt(pow(vel,2.0) / 2);
            else if(dirDown && !colDown)
                yVel = sqrt(pow(vel,2.0) / 2);
            else
                yVel = 0;
        }
    }
}

float GPhysics::getXVel() {
    return xVel;
}

float GPhysics::getYVel() {
    return yVel;
}

void GPhysics::setDestX(int x) {
    destX = x;
}

void GPhysics::setDestY(int y) {
    destY = y;
}

int GPhysics::getDestX() {
    return destX;
}

int GPhysics::getDestY() {
    return destY;
}

void GPhysics::setKeyControlled(bool keyControlled) {
    movedByKey = keyControlled;
}

int GPhysics::getDir() {
    return currentDir;
}
