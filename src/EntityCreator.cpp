/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "EntityCreator.hpp"

#include "Character.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Environment.hpp"

#include "Game.hpp"

EntityCreator::EntityCreator()
{
    //ctor
}

EntityCreator::~EntityCreator()
{
    //dtor
}

Entity& EntityCreator::createPlayer(EntitySystem::EntityManager *mManager,
                                    int x,int y)
{
    std::cout << " - EntityCreator::createPlayer() ..."<<std::endl;
    auto& entity(mManager->addEntity());
    //auto& entity = manager.addEntity();

    entity.addComponent<Position>(x,y);
    entity.addComponent<Texture>("data/gubbe_box1.png",true);
    entity.addComponent<GPhysics>();
    entity.addComponent<Character>(mManager);

    //if(!entity.hasGroup(game::PLAYER))
    entity.addGroup(game::PLAYER);

    return entity;
}

Entity& EntityCreator::createItem(EntitySystem::EntityManager *mManager,
                                    int itemNumber,int x,int y, bool onGround)
{
    auto& item(mManager->addEntity());

    /* Get right item from a list/file. */
    item.addComponent<Position>(x,y);
    item.addComponent<Texture>("data/stick.png",false);
    item.addComponent<Item>();
    /* add position */

    //if(!item.hasGroup(game::ITEM))
    item.addGroup(game::ITEM);
    return item;
}

Entity& EntityCreator::createEnemy(EntitySystem::EntityManager *mManager,
                                int enemyNumber,int x,int y)
{
    auto& enemy(mManager->addEntity());

    /* Get right item from a list/file. */
    enemy.addComponent<Position>(x,y);
    enemy.addComponent<Texture>("data/goblin.png",true);
    enemy.addComponent<Enemy>(mManager);
    /* add position */

    //if(!enemy.hasGroup(game::ENEMY))
        enemy.addGroup(game::ENEMY);
    return enemy;
}

Entity& EntityCreator::createEnvironment(EntitySystem::EntityManager *mManager,
                                            int envNumber,int x,int y)
{
    auto& environment(mManager->addEntity());

    environment.addComponent<Position>(x,y);
    environment.addComponent<Texture>("data/tree_box.png",false);
    environment.addComponent<GPhysics>();
    environment.addComponent<Environment>();

    environment.addGroup(game::ENVIRONMENT);
    return environment;
}
