#include "Character.hpp"

#include "Game.hpp"

Character::Character() //: Texture()
{

}

Character::~Character()
{

}

void Character::init()
{
    std::cout << " - Character::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    physics = &entity->getComponent<GPhysics>();
    texture = &entity->getComponent<Texture>();
    position->setX(game::getWidth());
    position->setY(game::getHeight());
    texture->setXRect(game::getWidth()-game::getOffset()->x);
    texture->setYRect(game::getHeight()-game::getOffset()->y);
    //game::getOffset().x

}

void Character::draw()
{
    //render(game::getRenderer(),(SDL_Rect*)NULL,
    //                (double)0.0,NULL,SDL_FLIP_NONE);
}

void Character::update()
{
    const Uint8 *key = SDL_GetKeyboardState(NULL);
    moveChar(key);
}

void Character::moveChar(const Uint8 *key)
{
    if(key[SDL_SCANCODE_UP])
    {
        physics->setDir(game::NORTH,true);
        texture->setClipX(32);
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
    if(key[SDL_SCANCODE_LEFT])
    {
        physics->setDir(game::WEST,true);
        texture->setClipX(0);
        texture->setClipY(32);
            //position->setX(position->getX()-vel);
        if(position->getX() < game::getWidth()/2)
            texture->setXRect(position->getX());
        if(position->getX() > game::getWidth()*2-(game::getWidth()/2))
            texture->setXRect(position->getX() - game::getWidth());
    }
    else
        physics->setDir(game::WEST,false);
    if(key[SDL_SCANCODE_RIGHT])
    {
        physics->setDir(game::EAST,true);
        texture->setClipX(32);
        texture->setClipY(32);
            //position->setX(position->getX()+vel);
        if(position->getX() > game::getWidth()*2-(game::getWidth()/2)) // Mapheight - screenheight
            texture->setXRect(position->getX()-game::getWidth());
        if(position->getX() < game::getWidth()/2)
            texture->setXRect(position->getX());
    }
    else
        physics->setDir(game::EAST,false);
}

bool Character::checkCollision(int DIR)
{
    /* need to get the surrounding tiles somehow */
    bool isColliding = false;


    return isColliding;
}

