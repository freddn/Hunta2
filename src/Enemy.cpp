#include "Enemy.hpp"

Enemy::Enemy(EntityManager *m)
{
    //ctor
    manager = m;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::init()
{
    std::cout << " - Enemy::init() ..."<<std::endl;
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();

    xSpawnPos = position->getX();
    ySpawnPos = position->getY();

    //physics = &entity->getComponent<GPhysics>();
    aggro = false;
}

void Enemy::draw()
{

}

void Enemy::update()
{
    Position playerPos;
    auto& player(manager->getEntitiesByGroup(game::PLAYER));
    playerPos = player[0]->getComponent<Position>();

    /* Check if player is near */
    if(playerPos.getX()+132 > position->getX() &&
        playerPos.getX()-100 < position->getX() &&
        playerPos.getY()+132 > position->getY() &&
        playerPos.getY()-100 < position->getY())
    {
        if(aggro == false)
        {
            aggro = true;
            /* FIXME: Replace the position with an ID. */
            std::cerr << "!aggro from enemy at pos " << position->getX() <<
                "," << position->getY() << std::endl;
        }
    }
    else
    {
        if(aggro == true)
        {
            aggro = false;
            /* FIXME: Replace the position with an ID. */
            std::cerr << "!no aggro from enemy at pos " << position->getX() <<
                "," << position->getY() << std::endl;
        }
    }

    if(aggro) /* Follow player */
    {
        if(position->getX()+32 < playerPos.getX())
        {
            position->setX(position->getX() + 1);
        }
        else if(position->getX()-32 > playerPos.getX())
        {
            position->setX(position->getX() - 1);
        }

        if(position->getY()+32 < playerPos.getY())
        {
            position->setY(position->getY() + 1);
        }
        else if(position->getY()-32 > playerPos.getY())
        {
            position->setY(position->getY() - 1);
        }
    }
    else /* Return home */
    {
        if(position->getX() < xSpawnPos)
            position->setX(position->getX() + 1);
        else if(position->getX() > xSpawnPos)
            position->setX(position->getX() - 1);
        if(position->getY() < ySpawnPos)
            position->setY(position->getY() + 1);
        else if(position->getY() > ySpawnPos)
            position->setY(position->getY() - 1);

    }

}



