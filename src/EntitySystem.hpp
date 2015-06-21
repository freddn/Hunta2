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

#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>


/**
 * EntitySystem is a system where we have a managers that contains all the
 * entities we have in the game. The entities is built of different components.
 *
 * We can have different managers for different areas.
 * (Editor, InGame, different levels)
 * An entity can be a character, an enemy, a house, an item and so on.
 * The components can be a position class, physics class, texture and so on.
 */
namespace EntitySystem {
    struct Component;
    class Entity;
    class EntityManager;

    using ComponentID = std::size_t;
    using Group = std::size_t;

    /**
     *
     */
    namespace Internal {
        inline ComponentID getUniqueComponentID() noexcept {
            // Every call to this function returns an unique ID every time.
            static ComponentID lastID{0u};
            return lastID++;
        }
    }

    /**
     *
     */
    template<typename T> inline ComponentID getComponentTypeID() noexcept {
        static_assert(std::is_base_of<Component,T>::value,
                        "T must inherit from Component");
        static ComponentID typeID{Internal::getUniqueComponentID()};
        return typeID;
    }

    /**
     *
     */
    constexpr std::size_t maxComponents{32};
    using ComponentBitset = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component*,maxComponents>;

    constexpr std::size_t maxGroups{32};
    using GroupBitset = std::bitset<maxGroups>;

    /**
     *
     */
    struct Component {
        Entity* entity;
        virtual void init() {};
        virtual void update() {};
        virtual void draw() {};

        virtual ~Component() {};
    };

    /**
     *
     */
    class Entity {
    public:
        Entity(EntityManager &mManager) : manager(mManager){};
        void draw();
        void update();
        bool isAlive() const;
        void destroy();
        void setY(int y);
        void setEntityId(int id);
        int getY();
        int getEntityId();

        template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
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

        template<typename T> bool hasComponent() const {
            return componentBitset[getComponentTypeID<T>()];
        }

        template<typename T> T& getComponent() const {
            assert(hasComponent<T>());
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *reinterpret_cast<T*>(ptr);
        }

        bool hasGroup(Group mGroup) const noexcept;
        void addGroup(Group mGroup) noexcept;
        void delGroup(Group mGroup) noexcept;
    private:
        EntityManager &manager;
        int yPos = 0;
        int entityId = -1;
        bool alive = true;
        std::vector<std::unique_ptr<Component>> components;
        ComponentArray componentArray;
        ComponentBitset componentBitset;

        GroupBitset groupBitset;
    };

    struct EntityManager {
    public:
        void update();
        void draw();
        void reserveEntities(int amount);
        void moveEntity(int entityId, int srcPos, int destPos);
        bool canAdd();
        void addToGroup(Entity *mEntity,Group mGroup);
        std::vector<Entity*>& getEntitiesByGroup(Group mGroup);
        std::map<int, std::vector<std::unique_ptr<Entity>>>* getEntities();
        void refresh();
        Entity& addEntity(int yPos);
    private:
        int id = 0;
        unsigned int entitiesReserved = 32;
        std::map<int, std::vector<std::unique_ptr<Entity>>> entities;
        std::array<std::vector<Entity*>, maxGroups> groupedEntities;
    };
}


#endif
