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
        inline ComponentID getUniqueComponentID() noexcept;
    }
    template<typename T> inline ComponentID getComponentTypeID() noexcept;

    constexpr std::size_t maxComponents{300};
    using ComponentBitset = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component*,maxComponents>;

    constexpr std::size_t maxGroups{32};
    using GroupBitset = std::bitset<maxGroups>;

    struct Component
    {
        Entity* entity;
        virtual void init();
        virtual void update(float m);
        virtual void draw();

        virtual ~Component();
    };

    class Entity
    {
        public:
            Entity(EntityManager &mManager) : manager(mManager){};
            void draw();
            void update(float m);
            bool isAlive() const;
            void destroy();
            template<typename T, typename... TArgs>
            T& addComponent(TArgs&&... mArgs);
            template<typename T> bool hasComponent() const;
            template<typename T> T& getComponent() const;
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
            void update(float m);
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
