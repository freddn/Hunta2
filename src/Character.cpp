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
    loadFromFile(game::getRenderer(),"data/gubbe.png");
    setXPos(game::getWidth());
    setYPos(game::getHeight());
    setXRect(game::getWidth()/2);
    setYRect(game::getHeight()/2);
    std::cerr << "player init()";
}

void Character::draw()
{
    render(game::getRenderer(),(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);
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
        setClipX(32);
        setClipY(0);
        if(!checkCollision(NORTH))
        {
            setYPos(getY()-vel);
            if(getY() < (game::getHeight()/2))
                setYRect(getY()); // screenheight
            if(getY() > (game::getHeight()*2-(game::getHeight()/2)))
                setYRect(getY()-game::getHeight());
        }
    }
    else if(key[SDL_SCANCODE_DOWN])
    {
        setClipX(0);
        setClipY(0);
        if(!checkCollision(SOUTH))
        {
            setYPos(getY()+vel);
            if(getY() > (game::getHeight()*2-(game::getHeight()/2))) // Mapheight - screenheight
                setYRect(getY()-game::getHeight());
            if(getY() < game::getHeight()/2)
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
            if(getX() < game::getWidth()/2)
                setXRect(getX());
            if(getX() > game::getWidth()*2-(game::getWidth()/2))
                setXRect(getX() - game::getWidth());
        }
    }
    else if(key[SDL_SCANCODE_RIGHT])
    {
        setClipX(32);
        setClipY(32);
        if(!checkCollision(EAST))
        {
            setXPos(getX()+vel);
            if(getX() > game::getWidth()*2-(game::getWidth()/2)) // Mapheight - screenheight
                setXRect(getX()-game::getWidth());
            if(getX() < game::getWidth()/2)
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

void Character::setVelocity(int v)
{
    vel = v;
}


