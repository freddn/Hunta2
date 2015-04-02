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
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
    position->setX(game::getWidth());
    position->setY(game::getHeight());
    texture->setXRect(game::getWidth()-game::getOffset()->x);
    texture->setYRect(game::getHeight()-game::getOffset()->y);
    //game::getOffset().x
    std::cerr << "player init()";
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
        texture->setClipX(32);
        texture->setClipY(0);
        if(!checkCollision(NORTH))
        {
            position->setY(position->getY()-vel);
            //texture->setYPos(texture->getY()texture-vel);
            if(position->getY() < (game::getHeight()/2))
                texture->setYRect(position->getY()); // screenheight
            if(position->getY() > (game::getHeight()*2-(game::getHeight()/2)))
                texture->setYRect(position->getY()-game::getHeight());
        }
    }
    else if(key[SDL_SCANCODE_DOWN])
    {
        texture->setClipX(0);
        texture->setClipY(0);
        if(!checkCollision(SOUTH))
        {
            position->setY(position->getY()+vel);
            if(position->getY() > (game::getHeight()*2-(game::getHeight()/2))) // Mapheight - screenheight
                texture->setYRect(position->getY()-game::getHeight());
            if(position->getY() < game::getHeight()/2)
                texture->setYRect(position->getY());
        }

    }
    else if(key[SDL_SCANCODE_LEFT])
    {
        texture->setClipX(0);
        texture->setClipY(32);
        if(!checkCollision(WEST))
        {
            position->setX(position->getX()-vel);
            if(position->getX() < game::getWidth()/2)
                texture->setXRect(position->getX());
            if(position->getX() > game::getWidth()*2-(game::getWidth()/2))
                texture->setXRect(position->getX() - game::getWidth());
        }
    }
    else if(key[SDL_SCANCODE_RIGHT])
    {
        texture->setClipX(32);
        texture->setClipY(32);
        if(!checkCollision(EAST))
        {
            position->setX(position->getX()+vel);
            if(position->getX() > game::getWidth()*2-(game::getWidth()/2)) // Mapheight - screenheight
                texture->setXRect(position->getX()-game::getWidth());
            if(position->getX() < game::getWidth()/2)
                texture->setXRect(position->getX());
        }
    }
}

bool Character::checkCollision(int DIR)
{
    /* need to get the surrounding tiles somehow */
    bool isColliding = false;


    return isColliding;
}

void Character::setVelocity(int v)
{
    vel = v;
}


