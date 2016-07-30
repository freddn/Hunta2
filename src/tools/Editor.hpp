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

#define MAP_WIDTH 2048
#define MAP_HEIGHT 2048

#include "../ui/Screen.hpp"

#include "../EntitySystem.hpp"
#include "../ui/Icon.hpp"

/**
 * This class represents the map-editor.
 */
struct Editor : public Screen {
public:
    Editor();

    /**
     *SDL_MOUSEWHEEL
     */
    void init();

    void loadIcon(std::string img, int id,std::size_t type);

    /**
     *
     */
    void update();

    /**
     *
     */
    void draw();

    /**
     * Change which icon/tile/entity is selected.
     */
    void setSelected(unsigned long n);

    /**
     * Returns selected number.
     */
    unsigned long getSelected();

    /**
     * Place an entitiy on the map.
     */
    void place();

    /**
     * Save all changes made.
     */
    void save();

    ~Editor();
private:
    std::map<int, std::shared_ptr<Icon>> icons;
    unsigned long selected = 0;

    unsigned int firstIcon = 0;
    unsigned int lastIcon = 8;
    int selectedCount = 0;
    bool mapUpdated = false;

    int mapX = 0;
    int mapY = 0;
};

#endif // EDITOR_H
