#include "EntityCreator.hpp"



#include "Game.hpp"

EntityCreator::EntityCreator()
{
    //ctor
}

EntityCreator::~EntityCreator()
{
    //dtor
}

Entity& EntityCreator::createPlayer(EntitySystem::EntityManager *mManager)
{
    auto& entity(mManager->addEntity());
    //auto& entity = manager.addEntity();

    entity.addComponent<Position>();
    entity.addComponent<Texture>("data/gubbe.png");
    entity.addComponent<Character>();

    if(!entity.hasGroup(game::PLAYER))
        entity.addGroup(game::PLAYER);
    return entity;
}

Entity& EntityCreator::createItem(EntitySystem::EntityManager *mManager,int itemNumber,
                                int x,int y, bool onGround)
{
    auto& item(mManager->addEntity());

    /* Get right item from a list/file. */
    item.addComponent<Position>(x,y);
    item.addComponent<Texture>("data/stick.png");
    item.addComponent<Item>();
    /* add position */

    if(!item.hasGroup(game::ITEM))
        item.addGroup(game::ITEM);
    return item;
}

Entity& EntityCreator::createEnemy(EntitySystem::EntityManager *mManager,
                                int enemyNumber,int x,int y)
{
    auto& enemy(mManager->addEntity());

    /* Get right item from a list/file. */
    enemy.addComponent<Position>(x,y);
    enemy.addComponent<Texture>();
    enemy.addComponent<Enemy>();
    /* add position */

    if(!enemy.hasGroup(game::ENEMY))
        enemy.addGroup(game::ENEMY);
    return enemy;
}


