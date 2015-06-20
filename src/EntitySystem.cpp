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

namespace EntitySystem
{
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
        yPos = y;
    }

    int Entity::getY() const {
        return yPos;
    }

    void EntityManager::update() {
        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isAlive();
            }),
            std::end(entities));
        //std::cerr << entities.size()<< std::endl;
        for(auto& e : entities) {
            //if(e->isAlive())
            e->update();
        }
    }

    void EntityManager::draw() {
        /* Sort after y position. */

        std::sort(entities.begin(),entities.end());

        for(auto& e : entities)
            e->draw();
    }

    void EntityManager::addToGroup(Entity *mEntity,Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup) {
        return groupedEntities[mGroup];
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

        entities.erase(
            std::remove_if(std::begin(entities),std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isAlive();
            }),
            std::end(entities));
    }

    bool EntityManager::canAdd() {
        return (entities.size() < entitiesReserved);
    }

    void EntityManager::reserveEntities(int amount) {
        entities.reserve(amount);
        entitiesReserved = amount;
    }

    Entity& EntityManager::addEntity() {
        Entity* e(new Entity(*this));
        //std::cerr << entities.size() << std::endl;

        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));

        return *e;
    }

    void Entity::addGroup(Group mGroup) noexcept {
        groupBitset[mGroup] = true;
        manager.addToGroup(this,mGroup);
    }
}



