/* Copyright (C) 2015 Fredrik Mörtberg <fredrikmo@hotmail.com>
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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Hunta2. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Character.hpp"
#include "Game.hpp"

Character::Character() //: Texture()
{
}

Character::Character(EntityManager *m)
{
    manager = m;
}

Character::~Character()
{
}

void Character::init()
{
    std::cout << " - Character::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
    physics = &entity->getComponent<GPhysics>();
    //position->setX(game::getWidth());
    //position->setY(game::getHeight());
    if(position->getX()-(game::getWidth()/2) < 0)
        game::getOffset()->x = 0;
    else if(position->getX()+(game::getWidth()/2) > game::getWidth()*2)
        game::getOffset()->x = game::getWidth();
    else
        game::getOffset()->x = position->getX() - (game::getWidth()/2);
    if(position->getY()-(game::getHeight()/2) < 0)
        game::getOffset()->y = 0;
    else if(position->getY()+(game::getHeight()/2) > game::getHeight()*2)
        game::getOffset()->y = game::getHeight();
    else
        game::getOffset()->y = position->getY() - (game::getHeight()/2);
    texture->setXRect(game::getWidth()-game::getOffset()->x);
    texture->setYRect(game::getHeight()-game::getOffset()->y);
    //game::getOffset().x
}

void Character::draw()
{
    //render(game::getRenderer(),(SDL_Rect*)NULL,
    // (double)0.0,NULL,SDL_FLIP_NONE);
}

void Character::update()
{
    const Uint8 *key = SDL_GetKeyboardState(NULL);
    moveChar(key);
    for(auto& e: manager->getEntitiesByGroup(game::ENVIRONMENT))
    {
        Position temp = e->getComponent<Position>();
        int width = e->getComponent<Texture>().getWidth();
        int height = e->getComponent<Texture>().getHeight();
        if((position->getX()-10 < temp.getX()+width &&
            position->getX()+42 > temp.getX()) &&
            (position->getY()-10 < temp.getY()+height &&
            position->getY()+42 > temp.getY()))
        {
            physics->isColliding(e);
        }
    }
}
void Character::moveChar(const Uint8 *key)
{
    if(key[SDL_SCANCODE_DOWN])
    {
        physics->setDir(game::SOUTH,true);
        texture->setClipX(0);
        texture->setClipY(0);
        //position->setY(position->getY()+vel);
        if(position->getY() > (game::getHeight()*2-(game::getHeight()/2))) // Mapheight - screenheight
            texture->setYRect(position->getY()-game::getHeight());
        if(position->getY() < game::getHeight()/2)
            texture->setYRect(position->getY());
    }
    else
    {
        physics->setDir(game::SOUTH,false);
        //std::cerr <<"Physics::setDir()"<<std::endl;
    }
    if(key[SDL_SCANCODE_UP])
    {
        physics->setDir(game::NORTH,true);
        texture->setClipX(1);
        texture->setClipY(0);
        //position->setY(position->getY()-vel);
        if(position->getY() < (game::getHeight()/2))
            texture->setYRect(position->getY());
        if(position->getY() > (game::getHeight()*2-(game::getHeight()/2)))
            texture->setYRect(position->getY()-game::getHeight());
    }
    else
    {
        //std::cerr <<"Physics::setDir() before"<<std::endl;
        physics->setDir(game::NORTH,false);
        //std::cerr <<"Physics::setDir() after"<<std::endl;
    }
    if(key[SDL_SCANCODE_RIGHT])
    {
        physics->setDir(game::EAST,true);
        texture->setClipX(1);
        texture->setClipY(1);
        //position->setX(position->getX()+vel);
        if(position->getX() > game::getWidth()*2-(game::getWidth()/2)) // Mapheight - screenheight
            texture->setXRect(position->getX()-game::getWidth());
        if(position->getX() < game::getWidth()/2)
            texture->setXRect(position->getX());
    }
    else
        physics->setDir(game::EAST,false);
    if(key[SDL_SCANCODE_LEFT])
    {
        physics->setDir(game::WEST,true);
        texture->setClipX(0);
        texture->setClipY(1);
        //position->setX(position->getX()-vel);
        if(position->getX() < game::getWidth()/2)
            texture->setXRect(position->getX());
        if(position->getX() > game::getWidth()*2-(game::getWidth()/2))
            texture->setXRect(position->getX() - game::getWidth());
    }
    else
        physics->setDir(game::WEST,false);
}

bool Character::checkCollision(int DIR)
{
    /* need to get the surrounding tiles somehow */
    bool isColliding = false;
    return isColliding;
}
