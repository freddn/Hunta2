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
