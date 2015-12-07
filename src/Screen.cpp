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

#include "Screen.hpp"
#include "Game.hpp"


Screen::~Screen() {}

void Screen::init() {}

void Screen::update() {}

void Screen::draw() {}

void Screen::renderStart() {
    SDL_RenderClear(game::getRenderer());
}

void Screen::renderEnd() {
    tempText.str("");
    tempText << "FPS: " << game::getAvgFPS();
    fpsText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "Time: " << (game::getTimer()->getTicks() / 1000.f);
    timerText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    fpsText.render(200,30,nullptr);
    timerText.render(350,30,nullptr);


    SDL_RenderPresent(game::getRenderer());
}



