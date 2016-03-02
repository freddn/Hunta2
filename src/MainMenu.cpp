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

#include "MainMenu.hpp"
#include "Global.hpp"
#include "Enums.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init() {
    HelperFunctions::log("MainMenu::init() ...");
    frame.loadFromFile("data/frame.png");

    newGame.setImg("data/button.png", true, 256, 64);
    newGame.setRect(32*6, 120, 256, 64);
    newGame.setButtonText("New Game", game::getTextColor(), game::getFont());
    newGame.onClick([]() {
        game::setCurrentState(game::CHARCREATION);
        game::getCharacterCreationScreen()->init();
    });

    loadGame.setImg("data/button.png", true, 256, 64);
    loadGame.setRect(32*6, 200, 256, 64);
    loadGame.setButtonText("Load Game", game::getTextColor(), game::getFont());
    loadGame.onClick([]() {
        game::getTextureMapController()->getMap(1)->loadPlayer(100, 100);
        game::setCurrentState(game::INGAME);
    });

    settings.setImg("data/button.png", true, 256, 64);
    settings.setRect(32*6, 280, 256, 64);
    settings.setButtonText("Settings", game::getTextColor(), game::getFont());
    settings.onClick([](/* TODO goto Settings */) { });

    quit.setImg("data/button.png", true, 256, 64);
    quit.setRect(32*6, 360, 256, 64);
    quit.setButtonText("Quit Game", game::getTextColor(), game::getFont());
    quit.onClick([]() { game::setRunning(false); });

    background.loadFromFile("data/wolf.png");
    backgroundRect = {0,0,game::getWidth(),game::getHeight()};
    background.setDestRect(backgroundRect);
}

void MainMenu::draw() {
    Screen::renderStart();

    background.render(0,0,nullptr);

    /* Render the menu items */
    newGame.draw();
    loadGame.draw();
    settings.draw();
    quit.draw();

    Screen::renderEnd();
}

void MainMenu::update() {

    SDL_Event *e = game::getEvent();
    int mX = game::getMouseX();
    int mY = game::getMouseY();

    /* Update the buttons. */
    newGame.update(e,mX,mY);
    loadGame.update(e,mX,mY);
    settings.update(e,mX,mY);
    quit.update(e,mX,mY);

    Screen::update();
}

