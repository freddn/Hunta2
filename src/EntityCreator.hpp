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

#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "EntitySystem.hpp"

using namespace EntitySystem;

/*
 * In this class you can create entitys that will be added to the
 * given manager.
 */
class EntityCreator {
public:
    EntityCreator();

    Entity* createEntity(EntitySystem::EntityManager &mManager, int index, bool byIndex);

    void addPosition(Entity *entity,int x, int y);
    void addShape(Entity *entity,int w,int h,int r,int g, int b);
    void addTexture(Entity *entity,std::string img, bool isClipped,int clipW,int clipH);
    void addTexture(Entity *entity,std::string img, bool isClipped);
    void addTexture(Entity *entity,std::string text,SDL_Color textcolor,TTF_Font* font);
    void addTexture(Entity *entity);
    void addPhysics(Entity *entity);
    void addHealthBar(Entity *entity,int hp);
    void addWeapon(Entity *entity, std::string img, EntityManager &mManager);
    void addKeyboardController(Entity *entity);
    void addKeyboardController(Entity *entity, bool x, bool y);
    void addMouseController(Entity *entity);
    void addMouseController(Entity *entity, bool x, bool y);
    void addCamera(Entity *entity);
    void addToGroup(Entity *entity,std::size_t group);


    Entity& createPlayer(EntitySystem::EntityManager &mManager,
                            int x,int y);
    Entity& createItem(EntitySystem::EntityManager &mManager,int itemNumber,
                            int x,int y, bool onGround);
    Entity& createEnemy(EntitySystem::EntityManager &mManager,int enemyNumber,
                            int x,int y);
    Entity& createEnvironment(EntitySystem::EntityManager &mManager,
                                int envNumber,int x,int y);
    void createProjectile(EntitySystem::EntityManager &mManager,
                                    int x,int y,int destX,int destY);
    Entity& createTile(EntitySystem::EntityManager &mManager,
                                int tileId,int x,int y);
    virtual ~EntityCreator();
protected:
private:
};

#endif // ENTITYCREATOR_H
