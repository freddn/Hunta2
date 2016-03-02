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

#include "Game.hpp"


#include "HelperFunctions.hpp"
#include <unistd.h>
#include <iostream>

#include "Global.hpp"
#include "Enums.hpp"

namespace game {

    void start() {
        getOffset()->x = getWidth() / 2;
        getOffset()->y = getHeight() / 2;
        getOffset()->w = getWidth();
        getOffset()->h = getHeight();

        getBackground()->x = 0;
        getBackground()->y = 0;
        getBackground()->w = 2048;
        getBackground()->h = 2048;

        int countedFrames = 0;
        setCurrentState(MAINMENU);

        LTimer fpsTimer;
        LTimer delayTimer;
        LTimer update;

        getSaveSlotSelection()->init();

        HelperFunctions::log("game::start()");
        getLuaInterface()->initLua();
        getLuaInterface()->loadFile("data/savedata/saveslots.lua");
        getPlayerController()->setName("assdd");
        //playerController.save(&lInterface);
        getPlayerController()->load("nooobn", getLuaInterface());
        std::stringstream temp;
        temp << "Saved game '" <<getPlayerController()->getName() << "' Loaded!";
        HelperFunctions::log(temp.str());

        HelperFunctions::log("game::start() (load map)");
        getTextureMapController()->init(getLuaInterface());
        getItemManager()->init(getLuaInterface());

        HelperFunctions::log("game::start() (creating states)");

        getEditor()->init();
        getInGame()->init();
        getMainMenu()->init();
        getUIController()->init();

        getInventory()->init();

        if(getCurrentState() == INGAME)
            getTextureMapController()->getMap(1)->loadPlayer(100,100);

        fpsTimer.start();
        update.start();
        getTimer()->start();

        HelperFunctions::log("game::start() (main loop)");

        while(isRunning()) {
            /* Start the delay timer */
            delayTimer.start();

            pollEvents();

            switch(getCurrentState()) {
            case(MAINMENU):
                /* Show the main menu */
                getMainMenu()->draw();
                break;
            case(CHARCREATION):
                getCharacterCreationScreen()->draw();
                break;
            case(INGAME):
                getLuaInterface()->runLuaMain();

                getInGame()->renderStart();
                getInGame()->draw();
                getUIController()->draw();
                getInGame()->renderEnd();
                if(!getInGame()->takingInput())
                    getInGame()->update();
                getUIController()->update();

                break;
            case(PAUSED):
                getScreen()->update();
                /* GAME IS PAUSED */
                /* TODO Show menu */
                break;
            case(GAMEOVER):
                getScreen()->update();
                /* TODO Show a menu */
                break;
            case(EDITOR):
                getEditor()->update();
                getEditor()->draw(); // SELECTED
                break;
            default:
                setCurrentState(MAINMENU);
                break;
            }
            countedFrames++;
            if(delayTimer.getTicks() < 1000 / SCREEN_FPS) {
                SDL_Delay((1000/SCREEN_FPS) - delayTimer.getTicks());
            }

            if(update.getTicks() > 1000) {
                setAvgFPS(countedFrames / (fpsTimer.getTicks() / 1000.f));
                update.start();
            }
        }
    }

    void pollEvents() {
        const Uint8 *key = SDL_GetKeyboardState(NULL);
        getMouseController()->clear();
        while(SDL_PollEvent(getEvent()) != 0) {
            if(getEvent()->type == SDL_QUIT) {
                setRunning(false);
                break;
            }

            getMouseController()->update(getEvent());

            if(getCurrentState() == MAINMENU)
                getMainMenu()->update();
            else if(getCurrentState() == CHARCREATION) {

                getSaveSlotSelection()->update(getEvent());
                getCharacterCreationScreen()->update(getEvent());
            } else if(getCurrentState() == INGAME) {
                if(getInGame()->takingInput()) {
                    getInGame()->updateEvents(getEvent());
                    continue;
                } else
                    getInGame()->updateEvents(getEvent());
            }

            if(getCurrentState() == EDITOR && SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                getEditor()->place();
            else if(getEvent()->type == SDL_KEYDOWN) {
                if(key[SDL_SCANCODE_T]) {
                    getTextureMapController()->getMap(1)->clear();
                } else if(key[SDL_SCANCODE_ESCAPE]) {
                    if(getUIController()->inventoryIsDisplayed()) {
                        getUIController()->setInventoryDisplayed(false);
                    } else
                        setCurrentState(MAINMENU);
                } else if(key[SDL_SCANCODE_2])
                    setCurrentState(MAINMENU);
                else if(key[SDL_SCANCODE_1]) {
                    if(getCurrentState() == EDITOR) {
                        getTextureMapController()->saveMaps();
                        getTextureMapController()->loadMap(1);
                    }
                    getTextureMapController()->getMap(1)->loadPlayer(100,100);
                    game::setCurrentState(game::INGAME);
                } else if(key[SDL_SCANCODE_3])
                    setCurrentState(PAUSED);
                else if(key[SDL_SCANCODE_0])
                    setCurrentState(GAMEOVER);
                else if(key[SDL_SCANCODE_4]) {
                    getTextureMapController()->getMap(1)->destroyPlayer();
                    getTextureMapController()->getMap(1)->update();
                    setCurrentState(EDITOR);
                }
            } else if(getEvent()->type == SDL_MOUSEWHEEL && getCurrentState() == EDITOR)
                getEditor()->setSelected(getEditor()->getSelected()+getEvent()->wheel.y);
            else if(getEvent()->type == SDL_MOUSEMOTION) {
                int mx;
                int my;
                SDL_GetMouseState(&mx, &my);
                setMouseX(mx);
                setMouseY(my);
            }
        }
    }

    void newGame(std::string nick) {
        getPlayerController()->setName(nick);
        //playerController.load(nick,&lInterface);

        //playerController.save(&lInterface, 1);
        //playerController.save(&lInterface, 2);

        getTextureMapController()->loadMap(1);
        getTextureMapController()->getMap(1)->loadPlayer(100,100);
        game::setCurrentState(INGAME);
    }

    bool initVideo(bool fullscreen) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            HelperFunctions::log(HelperFunctions::ERROR, "Init video failed.");
            return false;
        }
        if (fullscreen) {
            setWindow(SDL_CreateWindow("Hunta", SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       getWidth(), getHeight(), SDL_WINDOW_OPENGL |
                                                                SDL_WINDOW_FULLSCREEN));
        } else
            setWindow(SDL_CreateWindow("Hunta", SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       getWidth(), getHeight(), SDL_WINDOW_OPENGL |
                                                                SDL_WINDOW_RESIZABLE)); //SDL_WINDOW_SHOWN);

        if (getGWindow() == nullptr) {
            HelperFunctions::log(HelperFunctions::ERROR, "Window could not be created.");
            return false;
        }
        return true;
    }

    bool initTextureHandling() {
        if(getGWindow() == nullptr) {
            HelperFunctions::log(HelperFunctions::ERROR,
                                 "No window has been created!");
            return false;
        }

        setRenderer(SDL_CreateRenderer(getGWindow(),-1,SDL_RENDERER_ACCELERATED));

        if(getRenderer() == nullptr) {
            HelperFunctions::log(HelperFunctions::WARNING,
                                 "Could not initiate hardware rendered.");
            /* Testing software rendering instead.. */
            setRenderer(SDL_CreateRenderer(getGWindow(),-1,SDL_RENDERER_SOFTWARE));
            if(getRenderer() == nullptr) {
                HelperFunctions::log(HelperFunctions::ERROR,
                                     "Could not initiate software renderer.");
                return false;
            }
        }

        if(IMG_Init(IMG_INIT_PNG) < 0) {
            HelperFunctions::log(HelperFunctions::ERROR,
                                 "IMG_Init() failed.");
            return false;
        }

        if(TTF_Init() != 0) {
            HelperFunctions::log(HelperFunctions::ERROR,
                                 "TTF_Init() failed");
            return false;
        }

        setFont(TTF_OpenFont("freefont/FreeSans.ttf",24));
        setDmgFont(TTF_OpenFont("freefont/FreeMonoBold.ttf",9));
        if(getFont() == nullptr || getDmgFont() == nullptr) {
            char buf[255];
            getcwd(buf,255);
            printf("path: %s\n%s\n",buf, SDL_GetError());
            perror("NOFONT");
            HelperFunctions::log(HelperFunctions::ERROR, "No font");
            return false;
        }

        setBuffer(SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET,
                                   getWidth()*2, getHeight()*2));

        if(getBuffer() == 0) {
            HelperFunctions::log(HelperFunctions::ERROR,
                                 "Failed to create texture buffer");
            return false;
        }

        /* Everything went better than expected. */
        return true;
    }

    void close() {
        //game::getTextureMapController()->getMap(1)->clear();

        SDL_DestroyTexture(getBuffer());
        setBuffer(nullptr);

        SDL_RenderClear(getRenderer());
        SDL_DestroyRenderer(getRenderer());
        SDL_DestroyWindow(getGWindow());
        setRenderer(nullptr);
        setWindow(nullptr);
        TTF_CloseFont(getFont());
        TTF_CloseFont(getDmgFont());
        setFont(nullptr);
        setDmgFont(nullptr);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

