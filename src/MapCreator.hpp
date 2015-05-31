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

#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <map>

#include "Texture.hpp"
#include "LuaInterface.hpp"

/*
 * Will create a new map.
 */
class MapCreator {
public:
    MapCreator();
    void init();
    void newMap(std::map<int,Texture*> &currentMap,
                const char*filename, int width, int height);

    virtual ~MapCreator();
private:
    LuaInterface l_interface;

};

#endif // MAPCREATOR_H

