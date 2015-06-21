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

#include "EntitySystem.hpp"

#include <iostream>

#include "Game.hpp"

namespace EntitySystem {

    void Entity::draw() {
        for(auto& c : components) {
            c->draw();
        }
    }

    void Entity::update() {
        //std::cerr << components.size() << std::endl;

        for(auto& c : components) {
            //if(c != nullptr && c->entity->isAlive())
            c->update();
        }

    }

    bool Entity::isAlive() const {
        return alive;
    }

    void Entity::destroy() {
        alive = false;
    }

    bool Entity::hasGroup(Group mGroup) const noexcept {
        return groupBitset[mGroup];
    }
    void Entity::delGroup(Group mGroup) noexcept {
        groupBitset[mGroup] = false;
    }

    void Entity::setY(int y) {
        y = y + getComponent<Texture>().getHeight();
        manager.moveEntity(entityId, yPos, y);

        yPos = y;
    }

    bool Entity::isMoved() {
        return moved;
    }

    void Entity::setMoved(bool mov) {
        moved = mov;
    }

    void Entity::setEntityId(int id) {
        entityId = id;
    }

    int Entity::getY() {
        return yPos;
    }

    int Entity::getEntityId() {
        return entityId;
    }

    void EntityManager::update() {
        for(auto vec = entities.begin(); vec != entities.end(); vec++) {
            vec->second.erase(
                std::remove_if(std::begin(vec->second), std::end(vec->second),
                [](const std::shared_ptr<Entity>& mEntity)
                {
                    return !mEntity->isAlive();
                }),
                std::end(vec->second));
        //std::cerr << entities.size()<< std::endl;

            for(auto& ent : vec->second) {
                if(ent != nullptr) {
                    if(ent->isMoved())
                        ent->setMoved(false);
                    else
                        ent->update();
                }
            }
        }
    }

    void EntityManager::draw() {
        /* Draw after y position. */
        for(int i = game::getOffset()->y; i < game::getHeight()+game::getOffset()->y;i++) {
        //for(auto vec = entities.begin(); vec != entities.end(); vec++) {
            for(auto& e : entities[i])
                e->draw();
        }

    }

    void EntityManager::addToGroup(Entity *mEntity,Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    std::map<int, std::vector<std::shared_ptr<Entity>>>* EntityManager::getEntities() {
        return &entities;
    }

    void EntityManager::refresh() {
        for(auto i(0u); i < maxGroups; ++i) {
            auto& v(groupedEntities[i]);

            v.erase(
                std::remove_if(std::begin(v),std::end(v),
                [i](Entity* mEntity)
                {
                    return !mEntity->isAlive() || !mEntity->hasGroup(i);
                }),
                std::end(v));
        }
        for( auto vec = entities.begin(); vec != entities.end(); vec++) {
            vec->second.erase(
                std::remove_if(std::begin(vec->second),std::end(vec->second),
                [](const std::shared_ptr<Entity>& mEntity)
                {
                    return !mEntity->isAlive();
                }),
                std::end(vec->second));
        }
    }

    bool EntityManager::canAdd() {
        //return (entities.size() < entitiesReserved);
        return true;
    }

    void EntityManager::reserveEntities(int amount) {
        //entities.reserve(amount);
        //entitiesReserved = amount;
    }

    void EntityManager::moveEntity(int entityId, int srcPos, int destPos) {

        /// Loop through all entitys in the vector at z-pos: srcPos. Stop when
        /// the entity we are looking for is found or all entitis have been
        /// iterated.
        for(auto e = entities.at(srcPos).begin(); e != entities.at(srcPos).end(); e++) {

            /// Check if we have found the right entity.
            if((*e)->getEntityId() == entityId) {

                /// Make a new reference to the entity we are moving.
                std::shared_ptr<Entity> newPtr = (*e);

                /// Remove the reference from the old shared_ptr.
                e->reset();

                /// We don't need to set moved if moving uppwards because updating
                /// is made from top to bottom. We used moved bool to avoid recursion.
                if(srcPos < destPos)
                    newPtr->setMoved(true);

                /// Place the new entity in the right "z" position.
                entities[destPos].emplace_back(newPtr);
                //entities->at(y).emplace_back(**e);

                /// Remove the old (now empty) shared_ptr from the vector.
                entities.at(srcPos).erase(e);
                break;
            }
        }

    }

    Entity& EntityManager::addEntity() {
        Entity* e(new Entity(*this));
        //std::cerr << entities.size() << std::endl;

        /// All entities get a unique id.
        e->setEntityId(id++);
        std::shared_ptr<Entity> sPtr{e};

        /// Place the entity in a vector at the right z-position.
        entities[0].emplace_back(sPtr);

        return *e;
    }

    void Entity::addGroup(Group mGroup) noexcept {
        groupBitset[mGroup] = true;
        manager.addToGroup(this,mGroup);
    }
}



