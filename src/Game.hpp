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

#ifndef GAME_H
#define GAME_H

#define SCREEN_FPS 60
#define TICKS_PER_FRAME (1000 / SCREEN_FPS)

#include <string>

/**
 * Game class. Contains game-loop. State of the game. Init of map/data.
 * This class holds alot of important game related objects.
 */
namespace game {
    /**
     * Will init the needed states and then start the game-loop.
     */
    void start();

    /** Check for SDL events */
    void pollEvents();

    void newGame(std::string nick);

    /** Initiates SDL, creates a window, buffer and so on. */
    bool initVideo(bool fullscreen);
    bool initTextureHandling();

    /** Quit SDL and deallocate stuff. */
    void close();
}


#endif // GAME_H
