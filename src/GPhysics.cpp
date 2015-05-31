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

#include <cmath>

#include "Game.hpp"


GPhysics::GPhysics() {
    //ctor
}

GPhysics::~GPhysics() {
    //dtor
}

void GPhysics::update() {
   /* for(auto &e : &entity->manager->getEntitiesByGroup(game::ENVIRONMENT))
    {
        e->getComponent<Position>();
    }*/
    setYVelocity();
    setXVelocity();

    position->setX(position->getX()+xVel);

    position->setY(position->getY()+yVel);
    //    std::cerr << "pos updated"<<std::endl;

    clearCol();
}

void GPhysics::init() {
    std::cout << " - GPhysics::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
}

bool GPhysics::isColliding(int x, int y) {

    return false;
}

bool GPhysics::isColliding(EntitySystem::Entity *e) {
    Position *tempPos = &e->getComponent<Position>();
    Texture *tempTexture = &e->getComponent<Texture>();
    bool colliding = false;

    if(dirRight) {
        if(position->getX()+33 > tempPos->getX() &&
            position->getX()+16 < tempPos->getX() &&
            (position->getY()+(vel) > tempPos->getY() ||
            position->getY()+32-(vel) < tempPos->getY()+tempTexture->getHeight()) &&
            !(position->getY()+32-(vel) < tempPos->getY() ||
            position->getY()+(vel) > tempPos->getY()+tempTexture->getHeight())) {
            colRight = true;
            //std::cerr << "--collision-right--"<<std::endl;
            //position->setX(position->getX()-8);
            //xVel--;
            colliding = true;
        }
    }
    if(dirLeft) {
        if(position->getX()-1 < tempPos->getX()+tempTexture->getWidth() &&
            position->getX()+16 > tempPos->getX() &&
            (position->getY()+(vel) > tempPos->getY() ||
            position->getY()+32-(vel) < tempPos->getY()+tempTexture->getHeight()) &&
            !(position->getY()+32-(vel) < tempPos->getY() ||
            position->getY()+(vel) > tempPos->getY()+tempTexture->getHeight())) {

            colLeft = true;
            //std::cerr << "--collision-left--"<<std::endl;
            //position->setX(position->getX()+8);
            //xVel++;
            colliding = true;
        }
    }

    if(dirDown) {
        if(position->getY()+33 > tempPos->getY() &&
            (position->getY() < tempPos->getY()+16) &&
            (position->getX()+(vel) > tempPos->getX() ||
            position->getX()+32-(vel) < tempPos->getX()+tempTexture->getWidth()) &&
            !(position->getX()+32-(vel) < tempPos->getX() ||
            position->getX()+(vel) > tempPos->getX()+tempTexture->getWidth())) {
            //std::cerr << "--collision-down--"<<std::endl;
            colDown = true;
            //position->setY(position->getY()-8);
            //yVel--;
            colliding = true;
        }
    }

    if(dirUp) {
        if(position->getY()-1 < tempPos->getY()+tempTexture->getHeight() &&
            (position->getY()-16 > tempPos->getY()) &&
            (position->getX()+(vel) > tempPos->getX() ||
            position->getX()+32-(vel) < tempPos->getX()+tempTexture->getWidth()) &&
            !(position->getX()+32-(vel) < tempPos->getX() ||
            position->getX()+(vel) > tempPos->getX()+tempTexture->getWidth())) {
            colUp = true;
            //std::cerr << "--collision-up--"<<std::endl;
            //position->setY(position->getY()+8);
            //yVel++;
            colliding = true;
        }
    }
    return colliding;
}

void GPhysics::clearCol() {
    colDown = false;
    colUp = false;
    colLeft = false;
    colRight = false;
}

void GPhysics::setDir(int dir, bool isMoving) {
    //std::cerr << "dir: "<<dir<<" isMoving: "<<isMoving<<" game::N "<<game::NORTH<<std::endl;
    switch(dir) {
    case (game::NORTH):
        //std::cerr << "position: "<<&position<<std::endl;
        //std::cerr << "north"<<" up: "<<this->dirUp<<" = "<< isMoving<<std::endl;

        dirUp = isMoving;
        //std::cerr << "north set"<<std::endl;
        break;
    case (game::SOUTH):
        //std::cerr << "south"<<std::endl;
        dirDown = isMoving;
        break;
    case (game::EAST):
        //std::cerr << "east"<<std::endl;
        dirRight = isMoving;
        break;
    case (game::WEST):
        //std::cerr << "west"<<std::endl;
        dirLeft = isMoving;
        break;
    default:
        break;
    }
}

void GPhysics::setVelocity(float v) {
    vel = v;
}

void GPhysics::setXVelocity() {
    if(!movedByKey) {
        if(destX != 0 && destY != 0) {
            float dY = std::abs(destY);
            float dX = std::abs(destX);
            xVel = ((dX/dY) / (dY/dX + dX/dY)) * vel;
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

void GPhysics::setYVelocity() {
    if(!movedByKey) {
        if(destX != 0 && destY != 0) {
            float dY = std::abs(destY);
            float dX = std::abs(destX);
            yVel =  ((dY/dX) / ((dY/dX) + dX/dY)) * vel;
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
