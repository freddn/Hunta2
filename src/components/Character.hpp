/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 * Copyright (C) 2015  Lucas Sköldqvist <frusen@gungre.ch>
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

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Texture.hpp"
#include "GPhysics.hpp"
#include "Health.hpp"
#include "EntitySystem.hpp"

/**
 * Character class.
 * Character is a component. Need a position and physics
 * component aswell to function.
 */
struct Character: EntitySystem::Component {
public:
    Character();
    Character(EntitySystem::EntityManager &m);

    /**
     * Init the player component. Gets the entity's other components.
     */
    void init();

    /**
     * Updates everything that has to do with the character.
     */
    void update();

    /**
     * Takes in a key and move the char accordingly.
     */
    void moveChar(const Uint8 *key);

    ~Character();

private:
    // Needed components.
    GPhysics *physics{nullptr};
    Texture *texture{nullptr};
    Position *position{nullptr};
    Health *health{nullptr};

    EntitySystem::EntityManager *manager{nullptr}; // For (creating and) finding entitys.
    int level = 0;
    bool attacking = false;
};

#endif /* CHARACTER_HPP */
