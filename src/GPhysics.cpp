#include "GPhysics.hpp"

#include <cmath>

#include "Game.hpp"


GPhysics::GPhysics()//: up(false),down(false),left(false),right(false)
{
    //ctor
}

GPhysics::~GPhysics()
{
    //dtor
}

void GPhysics::update()
{
    setYVelocity();
    setXVelocity();
    //std::cerr << "vel set"<<std::endl;

    position->setX(position->getX()+xVel);
    position->setY(position->getY()+yVel);
    //    std::cerr << "pos updated"<<std::endl;

    //std::cerr << "pos not updated"<<std::endl;
}

void GPhysics::init()
{
    std::cout << " - GPhysics::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
}

bool GPhysics::isColliding(int dir, int x, int y)
{
    return false;
}

bool GPhysics::isColliding(int dir, Position destPos)
{
    return false;
}

void GPhysics::setDir(int dir, bool isMoving)
{
    //std::cerr << "dir: "<<dir<<" isMoving: "<<isMoving<<" game::N "<<game::NORTH<<std::endl;
    switch(dir)
    {
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

void GPhysics::setVelocity(float v)
{
    vel = v;
}

void GPhysics::setXVelocity()
{
    if(!dirUp && !dirDown)
    {
        if(dirLeft)
            xVel = -vel;
        else if(dirRight)
            xVel = vel;
        else
            xVel = 0;
    }
    else if(dirUp || dirDown)
    {
        if(dirLeft)
            xVel = -sqrt(pow(vel,2.0) / 2);
        else if(dirRight)
            xVel = sqrt(pow(vel,2.0) / 2);
        else
            xVel = 0;
    }
}

void GPhysics::setYVelocity()
{
    if(!dirLeft && !dirRight)
    {
        if(dirUp)
            yVel = -vel;
        else if(dirDown)
            yVel = vel;
        else
            yVel = 0;
    }
    else if(dirLeft || dirRight)
    {
        if(dirUp)
            yVel = -sqrt(pow(vel,2.0) / 2);
        else if(dirDown)
            yVel = sqrt(pow(vel,2.0) / 2);
        else
            yVel = 0;
    }
}

float GPhysics::getXVel()
{
    return xVel;
}

float GPhysics::getYVel()
{
    return yVel;
}
