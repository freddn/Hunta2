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

    void Entity::updateY() {
        if(hasComponent<Position>() && hasComponent<Texture>()) {

            int y = getComponent<Position>().getY();
            y += getComponent<Texture>().getHeight();
            if(y != yPos) {
                manager.moveEntity(entityId, yPos, y);
                yPos = y;
            }
        }
    }

    int Entity::getEntityId() {
        return entityId;
    }

    void EntityManager::update() {
        if(byIndex) {
            for(auto &ent : entitiesByIndex) {
                ent.second->update();
            }
        } else {
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
                        else {

                            ent->update();
                            ent->updateY();
                        }
                    }
                }
            }
        }
    }

    void EntityManager::draw() {
        /* Draw after y position. */
        if(byIndex) {
            for(auto &ent : entitiesByIndex) {
                //x + y * width
                int index = ent.first;

                int x = 32* (index % 64);
                x += offsetX;
                int y = 32*(index)/64;
                y += offsetY;
                //std::cerr << y << std::endl;
                if(x > game::getOffset()->x &&
                    x < game::getOffset()->x + game::getOffset()->w &&
                    y > game::getOffset()->y &&
                    y < game::getOffset()->y + game::getOffset()->h)
                    ent.second->draw();
            }
        } else {
            for(int i = game::getOffset()->y; i < game::getHeight()+game::getOffset()->y;i++) {
            //for(auto vec = entities.begin(); vec != entities.end(); vec++) {
                for(auto& e : entities[i]) {
                    if(e->hasComponent<Position>()) {
                        int x = e->getComponent<Position>().getX();
                        if(x > game::getOffset()->x &&
                            x < game::getWidth()+game::getOffset()->x)
                            e->draw();
                    }
                }
            }
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

    std::map<int, std::shared_ptr<Entity>>* EntityManager::getEntitiesByIndex() {
        return &entitiesByIndex;
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
        if(byIndex) {
            for(auto it = entitiesByIndex.begin(),itend = entitiesByIndex.end();it != itend;) {
                 if(!it->second->isAlive())
                    it = entitiesByIndex.erase(it);
                 else
                    ++it;
            }
        } else {
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

    }

    bool EntityManager::canAdd() {
        //return (entities.size() < entitiesReserved);
        return true;
    }

    void EntityManager::reserveEntities(int amount) {
        //entities.reserve(amount);
        entitiesReserved = amount;
    }

    void EntityManager::moveEntity(int entityId, int srcPos, int destPos) {

        /// Loop through all entitys in the vector at srcPos = z-pos. Stop when
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

    void EntityManager::setEntitiesByIndex(bool entByIndex) {
        byIndex = entByIndex;
    }

    Entity& EntityManager::addEntity(int index) {
        byIndex = true;
        if(entitiesByIndex.find(index) != entitiesByIndex.end()) {
            entitiesByIndex.erase(index);
        }
        Entity* e(new Entity(*this));
        //std::cerr << entities.size() << std::endl;

        /// All entities get a unique id.
        e->setEntityId(index);
        std::shared_ptr<Entity> sPtr{e};
        entitiesByIndex.insert(std::pair<int,std::shared_ptr<Entity>>(index,sPtr));

        return *e;
    }

    Entity* EntityManager::addEntity(int index,bool i) {
        if(i) {
            byIndex = true;
            if(entitiesByIndex.find(index) != entitiesByIndex.end()) {
                entitiesByIndex.erase(index);
            }
            Entity* e(new Entity(*this));
            //std::cerr << entities.size() << std::endl;

            /// All entities get a unique id.
            e->setEntityId(index);
            std::shared_ptr<Entity> sPtr{e};
            entitiesByIndex.insert(std::pair<int,std::shared_ptr<Entity>>(index,sPtr));
            return e;
        } else {
            byIndex = false;
            for(int e : indexes) {
                if(index == e) {
                    destroyEntity(index);
                }
            }
            Entity* e(new Entity(*this));
            //std::cerr << entities.size() << std::endl;
            /// All entities get a unique id.
            e->setEntityId(id++);
            std::shared_ptr<Entity> sPtr{e};

            /// Place the entity in a vector at the right "z-position".
            entities[0].emplace_back(sPtr);
            indexes.push_back(index);
            return e;
        }

    }

    Entity& EntityManager::addEntity() {

        Entity* e(new Entity(*this));
        //std::cerr << entities.size() << std::endl;
        /// All entities get a unique id.
        e->setEntityId(id++);
        std::shared_ptr<Entity> sPtr{e};

        /// Place the entity in a vector at the right "z-position".
        entities[0].emplace_back(sPtr);
        //indexes.push_back(index);

        return *e;
    }

    void EntityManager::destroyEntity(int index) {
        int x = 32* (index % 64);
        int y = (index - (index % 64))/2;
        destroyEntity(index,x,y);
    }

    void EntityManager::destroyEntity(int index, int x, int y) {
        for(auto vec = entities.begin(); vec != entities.end(); ++vec) {
            for(auto ent : vec->second) {
                if(ent->getComponent<Position>().getX() == x &&
                    ent->getComponent<Position>().getY() == y) {
                    ent->destroy();
                }
            }
        }
        for(auto it = indexes.begin();it != indexes.end();++it) {
            if(*it == index) {
                indexes.erase(it);
                return;
            }
        }
    }

    void EntityManager::setOffset(int x, int y) {
        offsetX = x;
        offsetY = y;
    }

    void Entity::addGroup(Group mGroup) noexcept {
        groupBitset[mGroup] = true;
        manager.addToGroup(this,mGroup);
    }
}



