#include "EntitySystem.hpp"


namespace EntitySystem
{
    namespace Internal
    {
        inline ComponentID getUniqueComponentID() noexcept
        {
            // Every call to this function returns an unique ID every time.
            static ComponentID lastID{0u};
            return lastID++;
        }
    }

    template<typename T> inline ComponentID getComponentTypeID() noexcept
    {
        static_assert(std::is_base_of<Component,T>::value,
                        "T must inherit from Component");
        static ComponentID typeID{Internal::getUniqueComponentID()};
        return typeID;
    }

    void Entity::draw()    { for(auto& c : components) c->draw(); }
    void Entity::update(float m)    { for(auto& c : components) c->update(m); }
    bool Entity::isAlive() const { return alive; }
    void Entity::destroy() { alive = false; }
    template<typename T, typename... TArgs>
    T& Entity::addComponent(TArgs&&... mArgs)
    {
        assert(!hasComponent<T>());

        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));


        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();

        return *c;
    }

    template<typename T> T& Entity::getComponent() const
    {
        assert(hasComponent<T>());
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *reinterpret_cast<T*>(ptr);
    }

    template<typename T> bool Entity::hasComponent() const
    {
        return componentBitset[getComponentTypeID<T>()];
    }

    bool Entity::hasGroup(Group mGroup) const noexcept
    {
        return groupBitset[mGroup];
    }
    void Entity::delGroup(Group mGroup) noexcept
    {
        groupBitset[mGroup] = false;
    }

    void EntityManager::update(float m)
    {
        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isAlive();
            }),
            std::end(entities));

        for(auto& e : entities) e->update(m);
    }

    void EntityManager::draw()    { for(auto& e : entities) e->draw(); }

    void EntityManager::addToGroup(Entity *mEntity,Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    //getEntitiesByGroup
    //refresh
    // https://github.com/SuperV1234/Tutorials/blob/master/DiveIntoC%2B%2B11/5_Entities/p8.cpp

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
            [](const std::unique_ptr<Entity>& mEnitity)
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
