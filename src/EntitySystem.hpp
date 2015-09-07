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
     * Used so that all components have a unique id.
     */
    namespace Internal {
        inline ComponentID getUniqueComponentID() noexcept {
            // Every call to this function returns an unique ID every time.
            static ComponentID lastID{0u};
            return lastID++;
        }
    }

    /**
     * Returns the id of the component.
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
     * Component is a base class for all different classes that an entity can
     * be built with. A component can for example be Position, Texture, Weapon
     * and so on.
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
        Entity(EntityManager &mManager,int z) : manager(mManager),yPos(z) {};
        void draw();
        void update();
        bool isAlive() const;
        void destroy();
        void updateY();
        void setY(int y);
        bool isMoved();
        void setMoved(bool mov);
        void setEntityId(int id);
        //int getY();
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
        bool moved = false;
        int entityId = -1;
        bool alive = true;
        std::vector<std::unique_ptr<Component>> components;
        ComponentArray componentArray;
        ComponentBitset componentBitset;

        GroupBitset groupBitset;
    };

    /**
     * EntityManager is the manager of all entities. This manager will
     * update, draw and refresh all entities.
     */
    class EntityManager {
    public:
        /**
         * Call update of all entities.
         */
        void update();

        /**
         * Call draw of all entities. Will go from top of the screen to bottom.
         */
        void draw();

        /**
         * Reserve an amount of entities that later can be added.
         */
        void reserveEntities(int amount);

        /**
         * Will move an entity from one position in the entity-map to another.
         * This is done so the game gets a "z-position" aswell for entities.
         */
        void moveEntity(int entityId, int srcPos, int destPos);

        /**
         * Check if maximum amount of entities is reached.
         */
        bool canAdd();

        /**
         * Add an entity to a specific group.
         */
        void addToGroup(Entity *mEntity,Group mGroup);

        /**
         * Return all entities that belongs to a given group.
         */
        std::vector<Entity*>& getEntitiesByGroup(Group mGroup);

        /**
         * Return the map containing all entities.
         */
        std::map<int, std::vector<std::shared_ptr<Entity>>>* getEntities();
        std::map<int, std::shared_ptr<Entity>>* getEntitiesByIndex();

        /**
         * Remove all entities that is destroyed.
         */
        void refresh();

        void setEntitiesByIndex(bool entitiesByInd);

        /**
         * Adds a new entity. Will put this entity in a vector that is placed
         * inside a map with y-position as key. Here y-position is the same
         * as z-position to get the 3D effect.
         */
        Entity* addEntity(int index, bool byIndex);

        Entity& addEntity(int index);
        Entity& addEntity();

        void destroyEntity(int index, int x, int y);
        void destroyEntity(int index);
        void setOffset(int x,int y);
    private:
        bool byIndex = false;
        int id = 0;
        int offsetX = 0;
        int offsetY = 0;
        unsigned int entitiesReserved = 32;
        std::vector<int> indexes;
        std::map<int,std::shared_ptr<Entity>> entitiesByIndex;
        std::map<int, std::vector<std::shared_ptr<Entity>>> entities;
        std::array<std::vector<Entity*>, maxGroups> groupedEntities;
    };
}


#endif
