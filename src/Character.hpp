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
#include "EntitySystem.hpp"
#include "EntityCreator.hpp"

using namespace EntitySystem;

/*
 * Character class. Draw the player on the screen.
 * Character is a component. Need a position and physics
 * component aswell to function.
 */
struct Character: Component
{
public:
    Character();
    Character(EntityManager *m, EntityCreator *c);

    /* Load player. Loads a texture with the
     * character image and set position. */
    void init() override;

    /* Draw the player. */
    void draw() override;

    void update() override;

    /* Takes in a key and move the char accordingly. */
    void moveChar(const Uint8 *key);

    /* Check if player is colliding with something. */
    bool checkCollision(int DIR);

    /* Load saved data. */
    void loadSaveFile(std::string char_name);

    virtual ~Character();

private:
    GPhysics *physics{nullptr};
    Texture *texture{nullptr};
    Position *position{nullptr};
    EntityManager *manager{nullptr};
    EntityCreator *creator;
    bool attacking = false;
    int xPos; /* x-position of the player. */
    int yPos; /* y-position of the player. */
};

#endif /* CHARACTER_HPP */
