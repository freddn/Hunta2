
#include "Character.hpp"


Character::Character() : Texture()
{

}

Character::~Character()
{

}

void Character::moveChar(int vel, const Uint8 *key)
{
    if(key[SDL_SCANCODE_UP])
    {
        setClipX(32);
        setClipY(0);
        if(!checkCollision(NORTH))
        {
            setYPos(getY()-vel);
            if(getY() < (height/2))
                setYRect(getY()); // screenheight
            if(getY() > (height*2-(height/2)))
                setYRect(getY()-height);
        }
    }
    else if(key[SDL_SCANCODE_DOWN])
    {
        setClipX(0);
        setClipY(0);
        if(!checkCollision(SOUTH))
        {
            setYPos(getY()+vel);
            if(getY() > (height*2-(height/2))) // Mapheight - screenheight
                setYRect(getY()-height);
            if(getY() < height/2)
                setYRect(getY());
        }

    }
    else if(key[SDL_SCANCODE_LEFT])
    {
        setClipX(0);
        setClipY(32);
        if(!checkCollision(WEST))
        {
            setXPos(getX()-vel);
            if(getX() < width/2)
                setXRect(getX());
            if(getX() > width*2-(width/2))
                setXRect(getX() - width);
        }
    }
    else if(key[SDL_SCANCODE_RIGHT])
    {
        setClipX(32);
        setClipY(32);
        if(!checkCollision(EAST))
        {
            setXPos(getX()+vel);
            if(getX() > width*2-(width/2)) // Mapheight - screenheight
                setXRect(getX()-width);
            if(getX() < width/2)
                setXRect(getX());
        }
    }
}

bool Character::checkCollision(int DIR)
{
    /* need to get the surrounding tiles somehow */
    bool isColliding = false;





    return isColliding;
}


