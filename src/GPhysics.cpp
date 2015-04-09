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

    //std::cerr << "vel set"<<std::endl;

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
    //std::cerr << "pos not updated"<<std::endl;
}

void GPhysics::init()
{
    std::cout << " - GPhysics::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
}

bool GPhysics::isColliding(int x, int y)
{

    return false;
}

bool GPhysics::isColliding(EntitySystem::Entity *e)
{
    Position *tempPos = &e->getComponent<Position>();
    Texture *tempTexture = &e->getComponent<Texture>();
    bool colliding = false;

    if(dirRight)
    {
        if(position->getX()+32+vel > tempPos->getX() &&
            position->getX()+16 < tempPos->getX() &&
            (position->getY()+(vel/2) > tempPos->getY() ||
            position->getY()+32-(vel/2) < tempPos->getY()+tempTexture->getHeight()) &&
            !(position->getY()+32-(vel/2) < tempPos->getY() ||
            position->getY()+(vel/2) > tempPos->getY()+tempTexture->getHeight()))
        {
            colRight = true;
            std::cerr << "--collision-right--"<<std::endl;
            //position->setX(position->getX()-8);
            //xVel--;
            colliding = true;
        }
    }
    if(dirLeft)
    {
        if(position->getX()-vel < tempPos->getX()+tempTexture->getWidth() &&
            position->getX()+16 > tempPos->getX() &&
            (position->getY()+(vel/2) > tempPos->getY() ||
            position->getY()+32-(vel/2) < tempPos->getY()+tempTexture->getHeight()) &&
            !(position->getY()+32-(vel/2) < tempPos->getY() ||
            position->getY()+(vel/2) > tempPos->getY()+tempTexture->getHeight()))
        {
            colLeft = true;
            std::cerr << "--collision-left--"<<std::endl;
            //position->setX(position->getX()+8);
            //xVel++;
            colliding = true;
        }
    }

    if(dirDown)
    {
        if(position->getY()+32+vel > tempPos->getY() &&
            (position->getY() < tempPos->getY()+16) &&
            (position->getX()+(vel/2) > tempPos->getX() ||
            position->getX()+32-(vel/2) < tempPos->getX()+tempTexture->getWidth()) &&
            !(position->getX()+32-(vel/2) < tempPos->getX() ||
            position->getX()+(vel/2) > tempPos->getX()+tempTexture->getWidth()))
        {
            std::cerr << "--collision-down--"<<std::endl;
            colDown = true;
            //position->setY(position->getY()-8);
            //yVel--;
            colliding = true;
        }
    }

    if(dirUp)
    {
        if(position->getY()-vel < tempPos->getY()+tempTexture->getHeight() &&
            (position->getY()-16 > tempPos->getY()) &&
            (position->getX()+(vel/2) > tempPos->getX() ||
            position->getX()+32-(vel/2) < tempPos->getX()+tempTexture->getWidth()) &&
            !(position->getX()+32-(vel/2) < tempPos->getX() ||
            position->getX()+(vel/2) > tempPos->getX()+tempTexture->getWidth()))
        {
            colUp = true;
            std::cerr << "--collision-up--"<<std::endl;
            //position->setY(position->getY()+8);
            //yVel++;
            colliding = true;
        }
    }

    return colliding;
}
void GPhysics::clearCol()
{
    colDown = false;
    colUp = false;
    colLeft = false;
    colRight = false;
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
        if(dirLeft && !colLeft)
            xVel = -vel;
        else if(dirRight && !colRight)
            xVel = vel;
        else
            xVel = 0;
    }
    else if(dirUp || dirDown)
    {
        if(dirLeft && !colLeft)
            xVel = -sqrt(pow(vel,2.0) / 2);
        else if(dirRight && !colRight)
            xVel = sqrt(pow(vel,2.0) / 2);
        else
            xVel = 0;
    }
}

void GPhysics::setYVelocity()
{
    if(!dirLeft && !dirRight)
    {
        if(dirUp && !colUp)
            yVel = -vel;
        else if(dirDown && !colDown)
            yVel = vel;
        else
            yVel = 0;
    }
    else if(dirLeft || dirRight)
    {
        if(dirUp && !colUp)
            yVel = -sqrt(pow(vel,2.0) / 2);
        else if(dirDown && !colDown)
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
