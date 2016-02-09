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

#include "InGame.hpp"

#include "Game.hpp"

InGame::InGame() {}

InGame::~InGame() {}

void InGame::init() {
    inGameManager.reserveEntities(300); // TODO Remove? Check if needed (spam loads of objects in the game)
}

void InGame::draw() {
    game::getTextureMapController()->draw(); // Draw the map
    if(updateFreq%10 == 0) {
        update_interface();
        updateFreq = 1;
    }
    nameText.render(450,30,nullptr);
    lvText.render(450,50,nullptr);
    hpText.render(450,70,nullptr);
    expText.render(450,90,nullptr);
    atkText.render(450,110,nullptr);
    defText.render(450,130,nullptr);
    updateFreq++;
}

void InGame::update() {
    game::getTextureMapController()->update();

    Screen::update();
}

void InGame::update_interface() {
    tempText.str("");
    tempText << "Name: "<<game::getPlayerController()->getName();
    nameText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "LV:      "<<game::getPlayerController()->getLevel();
    lvText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "HP:      "<<game::getPlayerController()->getCurrentHp()
            << "/"<<game::getPlayerController()->getHp();
    hpText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "EXP:    "<<game::getPlayerController()->getExperience()
                << "/"<<game::getPlayerController()->getMaxExperience(
                    game::getPlayerController()->getLevel());
    expText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "ATK:    "<<game::getPlayerController()->getAtk();
    atkText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "DEF:    "<<game::getPlayerController()->getDef();
    defText.loadFromText(tempText.str(), *game::getTextColor(),game::getFont());
}

