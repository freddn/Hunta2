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

#include <string>


#include "InGame.hpp"
#include "MainMenu.hpp"

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
    Screen screen;
    Editor editor;
    InGame inGame;
    MainMenu mMenu;

    int current_state = EDITOR;
    MapClass textureMapController;
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
    const Uint8 *key = nullptr;

    SDL_Color textColor = {255,255,255,0};
    bool running = true;

    void start() {
        std::cerr << " - game::start() ..." << std::endl;
        key = SDL_GetKeyboardState(nullptr);
        textureMapController.init();
        std::cerr << " - game::start() (load map) ..."<<std::endl;
        std::string map2 = "data/map2";
        if(!textureMapController.loadMap(1)) {
            std::cerr << "Map could not be loaded" << std::endl;
        }
        //std::map<int,Texture*> textures;
        std::cerr << " - game::start() (creating states) ..."<<std::endl;
        //interface.loadFromFile("data/interface.png");
        editor.init();
        inGame.init();
        mMenu.init();
        textureMap = textureMapController.getMap(1);

        fpsTimer.start();
        std::cerr << " - game::start() (main loop) ..."<<std::endl;
        while(running) {
            /* Get current time */
            currentTick = fpsTimer.getTicks();

            pollEvents();
            switch(current_state) {
            case(MAINMENU):
                /* Show the main menu */
                mMenu.update();
                mMenu.draw();
                break;
            case(INGAME):

                inGame.update();
                inGame.draw();
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
            if(avgFPS > 2000000) {
                avgFPS = 0;
            }
            //avgFPS = 1000.f / (fpsTimer.getTicks() - currentTick);


            if((fpsTimer.getTicks() - currentTick) < TICKS_PER_FRAME) {
                SDL_Delay((TICKS_PER_FRAME-(fpsTimer.getTicks()-currentTick)));
            }
            //SDL_Delay(5);
            ++countedFrames;
        }
    }

    void pollEvents() {
        const Uint8 *key = SDL_GetKeyboardState(NULL);

        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT)
                running = false;//game::setRunning(false);
            else if(event.type == SDL_KEYDOWN) {
                if(key[SDL_SCANCODE_ESCAPE])
                    running = false;//game::setRunning(false);
                else if(key[SDL_SCANCODE_S]) {
                    if (timer.isStarted())
                        timer.stop();
                    else
                        timer.start();
                } else if(key[SDL_SCANCODE_P]) {
                    if(timer.isPaused())
                        timer.unpause();
                    else
                        timer.pause();
                } else if(key[SDL_SCANCODE_2])
                    current_state = MAINMENU;
                else if(key[SDL_SCANCODE_1]) {
                    if(current_state == EDITOR) {
                        /* Save as map_y_x */
                        //std::cout << "save map size: " << textures.size() << std::endl;
                        offset.x = game::getWidth();
                        offset.y = game::getHeight();

                        textureMapController.saveMaps();

                        textureMapController.loadMap(1);
                        //textureMap = textureMapController.getMap(1);
                        textureMapController.getMap(1)->loadPlayer(100,100);
                        //std::cout << "loaded map size: " << textures.size() << std::endl;
                    }
                    game::setCurrent_state(game::INGAME);
                    // LOAD MAP
                } else if(key[SDL_SCANCODE_3])
                    current_state = game::PAUSED;
                else if(key[SDL_SCANCODE_0])
                    current_state = game::GAMEOVER;
                else if(key[SDL_SCANCODE_4]) {
                    textureMapController.getMap(1)->destroyPlayer();
                    textureMapController.getMap(1)->update();
                    current_state = game::EDITOR;
                    // LOAD MAP.
                    // SAVE MAP.
                }
            } else if(current_state == EDITOR && SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                editor.place();
            } else if(event.type == SDL_MOUSEWHEEL && current_state == EDITOR) {

                //if(event.wheel.y > 0 && editor.getSelected() < 2)
                    //editor.setSelected(editor.getSelected()+event.wheel.y);
                //else if(event.wheel.y < 0 && editor.getSelected() > 0)
                editor.setSelected(editor.getSelected()+event.wheel.y);

                //std::cerr << "MOUSEWHEEL!!" << "sel: " <<editor.getSelected()<<"y: "<<event.wheel.y << std::endl;
            } else if(event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX,&mouseY);
            }

        }
    }

    bool init_game(bool fullscreen) {
        offset.x = width/2;
        offset.y = height/2;
        offset.w = width;
        offset.h = height;
        background.x = 0;
        background.y = 0;
        background.w = width;
        background.h = height;
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
        if(font == nullptr) {
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
        //for(auto iter = game::getTextureMap()->begin(); iter != game::getTextureMap()->end();iter++){
            //((Texture*)iter->second)->free();
            //free((Texture*)iter->second);
            //delete (Texture*)iter->second;
        game::getTextureMap()->close();
        //erase(game::getTextureMap()->begin(),game::getTextureMap()->end());
        //}

        SDL_DestroyTexture(buffer);
        buffer = nullptr;

        SDL_RenderClear(renderer);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(gWindow);
        renderer = nullptr;
        gWindow = nullptr;
        TTF_CloseFont(font);
        font = nullptr;

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

    int getCurrentState() {
        return current_state;
    }

    void setCurrent_state(int temp) {
        current_state = temp;
    }

    MapClass *getTextureMapController()  {
        return &textureMapController;
    }

    std::shared_ptr<Map> getTextureMap() {
        return textureMap;
    }

    void setTextureMap(std::shared_ptr<Map> tempMap) {
        textureMap = tempMap;
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

