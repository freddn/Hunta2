#include "Position.hpp"

Position::Position()
{
    //ctor
}
Position::Position(int posX, int posY)
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

}

int Position::getX()
{
    return x;
}
int Position::getY()
{
    return y;
}
void Position::setX(int posX)
{
    x = posX;
}
void Position::setY(int posY)
{
    y = posY;
}

