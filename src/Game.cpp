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


namespace game {
    SDL_Event event;
    SDL_Rect offset;
    SDL_Rect rect;
    SDL_Rect background;
    int mouseX;
    int mouseY;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *buffer = nullptr;
    TTF_Font * font;

    int current_state = INGAME;
    MapClass textureMap;
    std::map<int,Texture*> texture_map;
    int width = 640;
    int t_width = width/32;
    int height = 480;
    int t_height = height/32;
    int maxFPS = 45;
    bool hasChanged = true;

    int countedFrames = 0;
    float currentFPS = 0.f;
    float avgFPS = 0.f;
    LTimer timer;
    LTimer fpsTimer;
    int currentTick;
    int selected;
    const Uint8 *key;

    SDL_Color text_color = {255,255,255,0};

    bool running = true;

    void start() {
        std::cerr << " - game::start() ..." << std::endl;
        key = SDL_GetKeyboardState(nullptr);
        textureMap.init();
        std::cerr << " - game::start() (load map) ..."<<std::endl;
        std::string map2 = "data/map2";
        if(!textureMap.loadMap(map2)) {
            std::cerr << "Map could not be loaded" << std::endl;
        }
        //std::map<int,Texture*> textures;
        std::cerr << " - game::start() (creating states) ..."<<std::endl;
        Screen screen;
        Editor editor;
        InGame in_game;
        MainMenu mMenu;
        mMenu.init();
        in_game.init();
        texture_map = *textureMap.getMap();

        fpsTimer.start();
        std::cerr << " - game::start() (main loop) ..."<<std::endl;
        while(running) {
            /* Get current time */
            currentTick = (int)SDL_GetTicks();

            switch(current_state) {
            case(MAINMENU):
                /* Show the main menu */
                mMenu.update();
                mMenu.draw();
                break;
            case(INGAME):
                in_game.update();
                in_game.draw();
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
            if(((int)SDL_GetTicks() - currentTick) < 1000/game::getMaxFPS()) {
                SDL_Delay((int)((1000/game::getMaxFPS())-((int)SDL_GetTicks()-currentTick)));
            }
            countedFrames ++;
        }
    }

    bool init_game() {
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

        gWindow = SDL_CreateWindow("Hunta 2",SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,height,SDL_WINDOW_OPENGL |
                                   SDL_WINDOW_RESIZABLE); //SDL_WINDOW_SHOWN);

        if(gWindow == nullptr) {
            std::cerr << "Window could not be created." << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == nullptr) {
            std::cerr << "Renderer could not be created" << std::endl;
            return false;
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
        for(auto iter = game::getTextureMap()->begin(); iter != game::getTextureMap()->end();iter++){
            //((Texture*)iter->second)->free();
            //free((Texture*)iter->second);
            delete (Texture*)iter->second;
        }

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

    SDL_Event *getEvent() {
        return &event;
    }

    SDL_Rect *getOffset() {
        return &offset;
    }

    SDL_Rect *getRect() {
        return &rect;
    }

    void setRectX(int x) {
        rect.x = x;
    }

    SDL_Rect *getBackground() {
        return &background;
    }

    SDL_Color *getText_color() {
        return &text_color;
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

    int getCurrent_state() {
        return current_state;
    }

    void setCurrent_state(int temp) {
        current_state = temp;
    }

    MapClass *getTextureMapObject()  {
        return &textureMap;
    }

    std::map<int,Texture*> *getTextureMap() {
        return &texture_map;
    }

    void setTextureMap(std::map<int,Texture*> &temp_map) {
        texture_map = temp_map;
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

