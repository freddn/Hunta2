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

#include "../Global.hpp"
#include "../HelperFunctions.hpp"

InGame::InGame() {}

InGame::~InGame() {}

void InGame::init() {
    prompt.setText("> ", game::getTextColor(),game::getFont());
    textBox.init();
    textBox.setPos(100,400);
    textBox.setOnEnter([](std::string msg){
        HelperFunctions::log(HelperFunctions::MESSAGE,msg);
        game::getLuaInterface()->loadString(msg.c_str());
    });
}

void InGame::draw() {
    game::getTextureMapController()->draw(); // Draw the map
    if(updateFreq%10 == 0) {
        update_interface();
        updateFreq = 1;
    }

    if(textBox.takingInput()) {
        prompt.render(80,400);
        textBox.draw();
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

void InGame::updateEvents(SDL_Event *event) {
    textBox.update(*event);
}

void InGame::update_interface() {
    tempText.str("");
    tempText << "Name: "<<game::getPlayerController()->getName();
    nameText.setText(tempText.str(), game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "LV:      "<<game::getPlayerController()->getLevel();
    lvText.setText(tempText.str(), game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "HP:      "<<game::getPlayerController()->getCurrentHp()
            << "/"<<game::getPlayerController()->getHp();
    hpText.setText(tempText.str(), game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "EXP:    "<<game::getPlayerController()->getExperience()
                << "/"<<game::getPlayerController()->getMaxExperience(
                    game::getPlayerController()->getLevel());
    expText.setText(tempText.str(), game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "ATK:    "<<game::getPlayerController()->getAtk();
    atkText.setText(tempText.str(), game::getTextColor(),game::getFont());

    tempText.str("");
    tempText << "DEF:    "<<game::getPlayerController()->getDef();
    defText.setText(tempText.str(), game::getTextColor(),game::getFont());
}

bool InGame::takingInput() {
    return textBox.takingInput();
}
