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


namespace EntitySystem
{
    void Entity::draw()    { for(auto& c : components) c->draw(); }
    void Entity::update()    { for(auto& c : components) c->update(); }
    bool Entity::isAlive() const { return alive; }
    void Entity::destroy() { alive = false; }

    bool Entity::hasGroup(Group mGroup) const noexcept
    {
        return groupBitset[mGroup];
    }
    void Entity::delGroup(Group mGroup) noexcept
    {
        groupBitset[mGroup] = false;
    }

    void EntityManager::update()
    {
        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isAlive();
            }),
            std::end(entities));

        for(auto& e : entities) e->update();
    }

    void EntityManager::draw()    { for(auto& e : entities) e->draw(); }

    void EntityManager::addToGroup(Entity *mEntity,Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    void EntityManager::refresh()
    {
        for(auto i(0u); i < maxGroups; ++i)
        {
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

    Entity& EntityManager::addEntity()
    {
        Entity* e(new Entity(*this));
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

    void Entity::addGroup(Group mGroup) noexcept
    {
        groupBitset[mGroup] = true;
        manager.addToGroup(this,mGroup);
    }

}
