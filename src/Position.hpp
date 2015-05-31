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

#ifndef POSITION_H
#define POSITION_H

#include "EntitySystem.hpp"

/*
 * This class is a component and will give entitys a position.
 * This position is used in collision-system, drawing and movement.
 */
struct Position : EntitySystem::Component
{
    public:
        Position();
        Position(float xPos,float yPos);

        //void update();

        float getX();
        float getY();
        void setX(float posX);
        void setY(float posY);
        /* TODO
         * - Add SDL_Rect.
         * - Setters and getters for the rect.
         */
        virtual ~Position();
    protected:
    private:
        float x{0};
        float y{0};
};

#endif // POSITION_H
