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
#include "Game.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init() {
    HelperFunctions::log("MainMenu::init() ...");
    frame.loadFromFile("data/frame.png");

    button.x = 0;
    button.y = 0;
    button.h = 64;
    button.w = 256;

    newGame =  {32*6, 120,button.w,button.h};
    loadGame = {32*6, 200,button.w,button.h};
    settings = {32*6, 280,button.w,button.h};
    quitGame = {32*6, 360,button.w,button.h};

    buttonBg.setClipped(true);
    buttonBg.setClipW(256);
    buttonBg.setClipH(64);
    buttonBg.loadFromFile("data/button.png");

    background.loadFromFile("data/wolf.png");
    backgroundRect = {0,0,game::getWidth(),game::getHeight()};
    background.setDestRect(&backgroundRect);
}

void MainMenu::draw() {
    Screen::renderStart();

    background.render(0,0,nullptr);

    /* Render the menu */

    if(newGamePressed)
        buttonBg.setClipY(2);
    else if(newGameHoover)
        buttonBg.setClipY(1);
    else
        buttonBg.setClipY(0);
    buttonBg.render(newGame.x, newGame.y,nullptr);

    // TODO Separate so we dont need to load text every time we render.. OR
    // TODO Implement a loadFromText function that takes a bool at the end ..
    // TODO which decides that we will save a text that is used often.. (maby both)

    text.loadFromText("New Game" ,
                        *game::getTextColor(),game::getFont());
    text.render(newGame.x+20,newGame.y+18,(SDL_Rect*)nullptr);

    if(loadGamePressed)
        buttonBg.setClipY(2);
    else if(loadGameHoover)
        buttonBg.setClipY(1);
    else
        buttonBg.setClipY(0);
    buttonBg.render(loadGame.x,loadGame.y, nullptr);
    text.loadFromText("Load Game" ,
                        *game::getTextColor(),game::getFont());
    text.render(loadGame.x+20,loadGame.y+18,(SDL_Rect*)nullptr);

    if(settingsPressed)
        buttonBg.setClipY(2);
    else if(settingsHoover)
        buttonBg.setClipY(1);
    else
        buttonBg.setClipY(0);
    buttonBg.render(settings.x,settings.y,nullptr);
    text.loadFromText("Settings" ,
                        *game::getTextColor(),game::getFont());
    text.render(settings.x+20,settings.y+18,(SDL_Rect*)nullptr);

    if(quitGamePressed)
        buttonBg.setClipY(2);
    else if(quitGameHoover)
        buttonBg.setClipY(1);
    else
        buttonBg.setClipY(0);
    buttonBg.render(quitGame.x,quitGame.y,nullptr);
    text.loadFromText("Quit game" ,
                        *game::getTextColor(),game::getFont());
    text.render(quitGame.x+20,quitGame.y+18,(SDL_Rect*)nullptr);

    Screen::renderEnd();
}

void MainMenu::update() {
    /* Check if button is pressed. */
    if(mouseOverRect(newGame))
        newGameHoover = true;
    else {
        newGameHoover = false;
        newGamePressed = false;
    }
    if(mouseOverRect(loadGame))
        loadGameHoover = true;
    else {
        loadGameHoover = false;
        loadGamePressed = false;
    }
    if(mouseOverRect(settings))
        settingsHoover = true;
    else {
        settingsHoover = false;
        settingsPressed = false;
    }
    if(mouseOverRect(quitGame))
        quitGameHoover = true;
    else {
        quitGameHoover = false;
        quitGamePressed = false;
    }

    if(game::getEvent()->type == SDL_MOUSEBUTTONDOWN) {
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if(mouseOverRect(newGame))
                newGamePressed = true;
            else
                newGamePressed = false;
            if(mouseOverRect(loadGame))
                loadGamePressed = true;
            else
                loadGamePressed = false;
            if(mouseOverRect(settings))
                settingsPressed = true;
            else
                settingsPressed = false;
            if(mouseOverRect(quitGame))
                quitGamePressed = true;
            else
                quitGamePressed = false;
        }
    }
    if(game::getEvent()->type == SDL_MOUSEBUTTONUP) {
        if(SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if(mouseOverRect(newGame)) {
                // TODO Add character selection screen
                game::setCurrent_state(game::CHARCREATION);
                //game::getTextureMapController()->getMap(1)->loadPlayer(100,100);

            } else
                newGamePressed = false;
            if(mouseOverRect(loadGame)) {
                // TODO Add saved game screen
                game::getTextureMapController()->getMap(1)->loadPlayer(100,100);
                game::setCurrent_state(game::INGAME);
            } else
                loadGamePressed = false;
            if(mouseOverRect(settings)) {
                // TODO Add settings panel
            } else
                settingsPressed = false;
            if(mouseOverRect(quitGame)) {
                game::setRunning(false);
            } else
                quitGamePressed = false;
        }
    }

    Screen::update();
}

bool MainMenu::mouseOverRect(SDL_Rect r) {
    return game::getMouseX() < r.x+r.w && game::getMouseX() > r.x &&
     game::getMouseY() < r.y+r.h && game::getMouseY() > r.y;
}
