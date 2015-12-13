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

#include "Game.hpp"

#include "InGame.hpp"
#include "MainMenu.hpp"
#include "CharacterCreationScreen.hpp"
#include <unistd.h>

#include <iostream>

namespace game {
    SDL_Event event;
    SDL_Rect offset;
    SDL_Rect rect;
    SDL_Rect background;
    int mouseX = 0;
    int mouseY = 0;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *buffer = nullptr;
    TTF_Font *font = nullptr;
    TTF_Font *dmgFont = nullptr;
    Screen screen;
    Editor editor;
    InGame inGame;
    MainMenu mMenu;

    //int current_state = INGAME;
    int current_state = MAINMENU;
    LuaInterface lInterface;
    MapController mapController;
    TextureManager textureManager;
    PlayerController playerController;
    EnemyDataController enemyController;
    ItemManager itemManager;
    UIController uiController;
    CharacterCreationScreen creationScreen;
    Inventory inventory(400,160);
    std::shared_ptr<Map> textureMap;
    int width = 640;
    int t_width = width/32;
    int height = 480;
    int t_height = height/32;
    int maxFPS = 45;
    bool hasChanged = true;

    int countedFrames = 1;
    float currentFPS = 0.f;
    float avgFPS = 0.f;
    LTimer timer;

    LTimer fpsTimer;
    int currentTick = 0;
    int selected;

    SDL_Color textColor = {255,255,255,0};
    bool running = true;

    void start() {
        std::cerr << " - game::start() ..." << std::endl;
        lInterface.initLua();
        playerController.setName("assdd");
        //playerController.save(&lInterface);
        playerController.load("nooobn", &lInterface);
        std::cout <<"Saved game '" <<playerController.getName() << "' Loaded! Level: "<<playerController.getLevel() << std::endl;

        mapController.init(&lInterface);
        itemManager.init(&lInterface);
        //playerController.load("Freddun", &lInterface);
        std::cerr << " - game::start() (load map) ..."<<std::endl;
        std::cerr << " - game::start() (creating states) ..."<<std::endl;
        editor.init();
        inGame.init();
        mMenu.init();
        uiController.init();
        inventory.init();
        //textureMap = mapController.getMap(1);
        if(current_state == INGAME)
            mapController.getMap(1)->loadPlayer(100,100);
        fpsTimer.start();
        timer.start();
        std::cerr << " - game::start() (main loop) ..."<<std::endl;
        while(running) {
            /* Get current time */
            currentTick = fpsTimer.getTicks();

            pollEvents();

            switch(current_state) {
            case(MAINMENU):
                /* Show the main menu */
                //mMenu.update();
                mMenu.draw();
                break;
            case(CHARCREATION):
                creationScreen.createCharacter();
                break;
            case(INGAME):
                inGame.renderStart();
                inGame.draw();
                uiController.draw();
                inGame.renderEnd();

                uiController.update();
                inGame.update();
                break;
            case(PAUSED):
                screen.update();
                /* GAME IS PAUSED */
                /* Show menu */
                break;
            case(GAMEOVER):
                screen.update();
                /* Show a menu */
                break;
            case(EDITOR):
                editor.update();
                editor.draw(); // SELECTED
                break;
            }
            avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if(countedFrames > 500) {
                avgFPS = 0;
                countedFrames = 0;
                fpsTimer.stop();
                fpsTimer.start();
            }

            if((fpsTimer.getTicks() - currentTick) < TICKS_PER_FRAME) {
                SDL_Delay((TICKS_PER_FRAME-(fpsTimer.getTicks()-currentTick)));
            }
            ++countedFrames;
        }
    }

    void pollEvents() {
        const Uint8 *key = SDL_GetKeyboardState(NULL);

        while(SDL_PollEvent(&event) != 0) {
            if(current_state == MAINMENU)
                mMenu.update();
            if(event.type == SDL_QUIT)
                running = false;
            else if(current_state == EDITOR && SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                editor.place();
            else if(event.type == SDL_KEYDOWN) {
                if(key[SDL_SCANCODE_T]) {
                    mapController.getMap(1)->clear();
                }else if(key[SDL_SCANCODE_ESCAPE])
                    current_state = MAINMENU;
                else if(key[SDL_SCANCODE_2])
                    current_state = MAINMENU;
                else if(key[SDL_SCANCODE_1]) {
                    if(current_state == EDITOR) {
                        mapController.saveMaps();
                        mapController.loadMap(1);
                    }
                    mapController.getMap(1)->loadPlayer(100,100);
                    game::setCurrent_state(game::INGAME);
                } else if(key[SDL_SCANCODE_3])
                    current_state = game::PAUSED;
                else if(key[SDL_SCANCODE_0])
                    current_state = game::GAMEOVER;
                else if(key[SDL_SCANCODE_4]) {
                    mapController.getMap(1)->destroyPlayer();
                    mapController.getMap(1)->update();
                    current_state = game::EDITOR;
                }
            } else if(event.type == SDL_MOUSEWHEEL && current_state == EDITOR)
                editor.setSelected(editor.getSelected()+event.wheel.y);
            else if(event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&mouseX,&mouseY);
        }
    }
    void newGame(std::string nick) {
        playerController.load(nick,&lInterface);
        mapController.loadMap(1);
        mapController.getMap(1)->loadPlayer(100,100);
        game::setCurrent_state(game::INGAME);
    }

    bool init_game(bool fullscreen) {
        offset.x = width/2;
        offset.y = height/2;
        offset.w = width;
        offset.h = height;
        background.x = 0;
        background.y = 0;
        background.w = 2048;
        background.h = 2048;
        rect.x = 400;
        rect.y = 400;
        rect.h = 32;
        rect.w = 32;

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Init video failed." << std::endl;
            return false;
        }
        if(fullscreen) {
            gWindow = SDL_CreateWindow("Hunta",SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,height,SDL_WINDOW_OPENGL |
                                   SDL_WINDOW_FULLSCREEN);
        } else
            gWindow = SDL_CreateWindow("Hunta",SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,height,SDL_WINDOW_OPENGL |
                                   SDL_WINDOW_RESIZABLE); //SDL_WINDOW_SHOWN);

        if(gWindow == nullptr) {
            std::cerr << "Window could not be created." << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == nullptr) {
            std::cerr << "Renderer could not be created "
                        <<"(SDL_RENDERER_ACCELERATED)" << std::endl;
            /* Testing software rendering instead.. */
            renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_SOFTWARE);
            if(renderer == nullptr) {
                std::cerr << "Renderer could not be created "
                        <<"(SDL_RENDERER_SOFTWARE)" << std::endl;
                return false;
            }
        }

        if(IMG_Init(IMG_INIT_PNG) < 0) {
            std::cerr << "IMG_Init() failed." << std::endl;
            return false;
        }

        if(TTF_Init() != 0) {
            std::cerr << "TTF_Init() failed" << std::endl;
            return false;
        }

        font = TTF_OpenFont("freefont/FreeSans.ttf",24);
        dmgFont = TTF_OpenFont("freefont/FreeMonoBold.ttf",9);
        if(font == nullptr || dmgFont == nullptr) {
            char buf[255];
            getcwd(buf,255);
            printf("path: %s\n",buf);
            perror("NOFONT ");
            std::cerr << "No font" << std::endl;
            return false;
        }

        buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET, width*2, height*2);

        if(buffer == 0) {
            std::cerr << "Failed to create buffer" << std::endl;
            return false;
        }

        /* Everything went better than expected. */
        return true;
    }

    void close() {
        game::getTextureMap()->clear();

        SDL_DestroyTexture(buffer);
        buffer = nullptr;

        SDL_RenderClear(renderer);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(gWindow);
        renderer = nullptr;
        gWindow = nullptr;
        TTF_CloseFont(font);
        TTF_CloseFont(dmgFont);
        font = nullptr;
        dmgFont = nullptr;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    Editor *getEditor() {
        return &editor;
    }

    SDL_Event *getEvent() {
        return &event;
    }

    SDL_Rect *getOffset() {
        return &offset;
    }

    SDL_Rect *getBackground() {
        return &background;
    }

    SDL_Color *getTextColor() {
        return &textColor;
    }

    int getMouseX() {
        return mouseX;
    }

    void setMouseX(int x) {
        mouseX = x;
    }

    int getMouseY() {
        return mouseY;
    }

    void setMouseY(int y) {
        mouseY = y;
    }

    SDL_Window *getGWindow() {
        return gWindow;
    }

    SDL_Renderer *getRenderer() {
        return renderer;
    }

    SDL_Texture *getBuffer() {
        return buffer;
    }

    void setBuffer(SDL_Texture * temp) {
        buffer = temp;
    }

    TTF_Font * getFont() {
        return font;
    }

    TTF_Font * getDmgFont() {
        return dmgFont;
    }

    int getCurrentState() {
        return current_state;
    }

    void setCurrent_state(int temp) {
        current_state = temp;
    }

    PlayerController *getPlayerController() {
        return &playerController;
    }

    MapController *getTextureMapController()  {
        return &mapController;
    }

    EnemyDataController *getEnemyDataController() {
        return &enemyController;
    }

    ItemManager *getItemManager() {
        return &itemManager;
    }

    Inventory *getInventory() {
        return &inventory;
    }

    std::shared_ptr<Map> getTextureMap() {
        return textureMap;
    }

    void setTextureMap(std::shared_ptr<Map> tempMap) {
        textureMap = tempMap;
    }

    TextureManager *getTextureManager() {
        return &textureManager;
    }

    int getWidth() {
        return width;
    }

    int getTWidth() {
        return t_width;
    }

    int getHeight() {
        return height;
    }

    int getTHeight() {
        return t_height;
    }

    int getMaxFPS() {
        return maxFPS;
    }

    bool getHasChanged() {
        return hasChanged;
    }

    void setHasChanged(bool boolean) {
        hasChanged = boolean;
    }

    float getAvgFPS() {
        return avgFPS;
    }

    LTimer* getTimer() {
        return &timer;
    }

    void setRunning(bool boolean) {
        running = boolean;
    }
}

