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

#ifndef EDITOR_H
#define EDITOR_H

#include "Screen.hpp"
#include "Game.hpp"

/* This class represents the map-editor.
 * Currently we can only draw the background-tiles.
 * TODO Put objects on the map. Trees/houses/enemys.
 */
struct Editor : public Screen
{
    public:
        Editor();
        void init();
        void update();
        void draw();
        ~Editor();
    private:
        SDL_Rect rground;
        SDL_Rect rwater;
        SDL_Rect rgrass;
        SDL_Rect sel;
        const Uint8 *key = NULL;
        bool selBool = false;
        int selected = 0;
        SDL_Surface *r_select;
        SDL_Texture *rect_select;
};

#endif // EDITOR_H
