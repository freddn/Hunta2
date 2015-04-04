#include "Position.hpp"

Position::Position()
{
    //ctor
}
Position::Position(float posX, float posY)
{
    x = posX;
    y = posY;
    //ctor
}
Position::~Position()
{
    //dtor
}

void Position::update()
{
    //std::cerr <<"Position::update()"<<std::endl;
}

float Position::getX()
{
    return x;
}
float Position::getY()
{
    return y;
}
void Position::setX(float posX)
{
    x = posX;
}
void Position::setY(float posY)
{
    y = posY;
}

