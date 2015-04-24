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
}



