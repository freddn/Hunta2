#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>

namespace EntitySystem
{
    struct Component;
    class Entity;
    class EntityManager;

    using ComponentID = std::size_t;
    using Group = std::size_t;

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

    constexpr std::size_t maxComponents{300};
    using ComponentBitset = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component*,maxComponents>;

    constexpr std::size_t maxGroups{32};
    using GroupBitset = std::bitset<maxGroups>;

    struct Component
    {
        Entity* entity;
        virtual void init() {};
        virtual void update() {};
        virtual void draw() {};

        virtual ~Component() {};
    };

    class Entity
    {
        public:
            Entity(EntityManager &mManager) : manager(mManager){};
            void draw();
            void update();
            bool isAlive() const;
            void destroy();
            template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
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
            template<typename T> bool hasComponent() const
            {
                return componentBitset[getComponentTypeID<T>()];
            }
            template<typename T> T& getComponent() const
            {
                assert(hasComponent<T>());
                auto ptr(componentArray[getComponentTypeID<T>()]);
                return *reinterpret_cast<T*>(ptr);
            }
            bool hasGroup(Group mGroup) const noexcept;
            void addGroup(Group mGroup) noexcept;
            void delGroup(Group mGroup) noexcept;
        private:
            EntityManager &manager;

            bool alive{true};
            std::vector<std::unique_ptr<Component>> components;
            ComponentArray componentArray;
            ComponentBitset componentBitset;

            GroupBitset groupBitset;
    };
    struct EntityManager
    {
        public:
            void update();
            void draw();
            void addToGroup(Entity *mEntity,Group mGroup);
            std::vector<Entity*>& getEntitiesByGroup(Group mGroup);
            void refresh();
            Entity& addEntity();
        private:
            std::vector<std::unique_ptr<Entity>> entities;

            std::array<std::vector<Entity*>, maxGroups> groupedEntities;
    };
}


#endif
