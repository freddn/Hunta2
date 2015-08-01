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
#include "Projectile.hpp"
#include "Weapon.hpp"
#include "Health.hpp"
#include "Game.hpp"
#include "Shape.hpp"
#include "Camera.hpp"
#include "MouseController.hpp"
#include "KeyboardController.hpp"

/** TODO remove? */

EntityCreator::EntityCreator() {
    //ctor
}

EntityCreator::~EntityCreator() {
    //dtor
}

Entity* EntityCreator::createEntity(EntitySystem::EntityManager &mManager, int index,bool byIndex) {
    //auto& entity(mManager.addEntity());
    return mManager.addEntity(index, byIndex);
}

void EntityCreator::addPosition(Entity *entity,int x, int y) {
    entity->addComponent<Position>(x,y);
}

void EntityCreator::addShape(Entity *entity,int w,int h,int r,int g, int b) {
    entity->addComponent<Shape>(w,h,r,g,b);
}

void EntityCreator::addTexture(Entity *entity,std::string img,
                                bool isClipped,int clipW,int clipH) {
    entity->addComponent<Texture>(img,isClipped,clipW,clipH);
}

void EntityCreator::addTexture(Entity *entity,std::string img,
                                bool isClipped) {
    entity->addComponent<Texture>(img,isClipped);
}

void EntityCreator::addTexture(Entity *entity,std::string text,SDL_Color textcolor,TTF_Font* font) {
    entity->addComponent<Texture>(text,textcolor,font);
}
void EntityCreator::addTexture(Entity *entity) {
    entity->addComponent<Texture>();
}

void EntityCreator::addPhysics(Entity *entity) {
    entity->addComponent<GPhysics>();
}

void EntityCreator::addHealthBar(Entity *entity,int hp) {
    entity->addComponent<Health>(hp);
}

void EntityCreator::addWeapon(Entity *entity, std::string img,
                            EntityManager &mManager) {
    entity->addComponent<Weapon>(img,mManager);
}

void EntityCreator::addKeyboardController(Entity *entity) {
    entity->addComponent<KeyboardController>();
}

void EntityCreator::addMouseController(Entity *entity) {
    entity->addComponent<MouseController>();
}

void EntityCreator::addMouseController(Entity *entity,bool x,bool y) {
    entity->addComponent<MouseController>(x, y);
}

void EntityCreator::addCamera(Entity *entity) {
    entity->addComponent<Camera>();
}

void EntityCreator::addToGroup(Entity *entity, std::size_t group) {
    entity->addGroup(group);
}

Entity& EntityCreator::createPlayer(EntitySystem::EntityManager &mManager,
                                        int x,int y) {
    std::cout << " - EntityCreator::createPlayer() ..."<<std::endl;
    auto& player(mManager.addEntity());
    //auto& entity = manager.addEntity();

    player.addComponent<Position>(x,y);
    player.addComponent<Texture>("data/gubbe_box1.png",true); // 32x32 clip
    player.addComponent<GPhysics>();
    player.addComponent<Health>(100);
    player.addComponent<Weapon>("data/sword.png", mManager);
    player.addComponent<Character>(mManager);

    //player.setY(y);//+player.getComponent<Texture>().getHeight());
    //if(!entity.hasGroup(game::PLAYER))
    player.addGroup(game::PLAYER);
    return player;
}

Entity& EntityCreator::createItem(EntitySystem::EntityManager &mManager,
                                    int itemID,int x,int y, bool onGround) {
    auto& item(mManager.addEntity());

    /* Get right item from a list/file. */
    item.addComponent<Position>(x,y);
    item.addComponent<Texture>("data/stick.png",false); // no clip
    item.addComponent<Item>(itemID,onGround);

    //item.setY(y);//+item.getComponent<Texture>().getHeight());

    /* add position */


    item.addGroup(game::ITEM);
    return item;
}

Entity& EntityCreator::createEnemy(EntitySystem::EntityManager &mManager,
                                int enemyID,int x,int y) {
    auto& enemy(mManager.addEntity());

    /* Get right enemy from a list/file. */
    enemy.addComponent<Position>(x,y);
    if(enemyID == 1)
        enemy.addComponent<Texture>("data/enemies/goblin.png",true); // 32x32 clip
    else
        enemy.addComponent<Texture>("data/enemies/wolf.png",true,48,48); // 48x48 clip
    enemy.addComponent<GPhysics>();
    enemy.addComponent<Health>(100);
    enemy.addComponent<Enemy>(mManager, enemyID);

    //enemy.setY(y);//+enemy.getComponent<Texture>().getHeight());
    /* add position */

    enemy.addGroup(game::ENEMY);
    return enemy;
}

Entity& EntityCreator::createEnvironment(EntitySystem::EntityManager &mManager,
                                            int envId,int x,int y) {
    auto& environment(mManager.addEntity());

    environment.addComponent<Position>(x,y);
    environment.addComponent<Texture>("data/environment/tree2.png",false); // no clip
    environment.addComponent<GPhysics>();
    environment.addComponent<Environment>(envId);

    //environment.setY(y);

    environment.addGroup(game::ENVIRONMENT);
    return environment;
}

void EntityCreator::createProjectile(EntitySystem::EntityManager &mManager,
                                        int x,int y,int destX,int destY) {

    if(mManager.canAdd()) {
        auto& projectile(mManager.addEntity());

        projectile.addComponent<Position>(x,y);
        projectile.addComponent<Texture>("data/fireball.png",false); // no clip
        projectile.addComponent<GPhysics>();
        projectile.addComponent<Projectile>(destX,destY,destX-x,destY-y);

        //projectile.setY(y);//+projectile.getComponent<Texture>().getHeight());

        projectile.addGroup(game::PROJECTILE);
    }
}

Entity& EntityCreator::createTile(EntitySystem::EntityManager &mManager,
                                    int tileId,int x,int y) {
    auto& tile(mManager.addEntity());

    /* Get right item from a list/file. */
    tile.addComponent<Position>(x,y);
    tile.addComponent<Texture>("data/stick.png",false); // no clip
    tile.addComponent<Tile>(tileId);
    //tile.setY(y);//+item.getComponent<Texture>().getHeight());

    /* add position */


    tile.addGroup(game::TILE);
    return tile;
}

