#include "Environment.hpp"
#include <iostream>

Environment::Environment()
{
    //ctor
}

Environment::~Environment()
{
    //dtor
}

void Environment::init()
{
    std::cout << " - Environment::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    physics = &entity->getComponent<GPhysics>();
}
