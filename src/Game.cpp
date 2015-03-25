#include "Game.hpp"


namespace game
{
    SDL_Event event;
    SDL_Rect offset;
    SDL_Rect rect;
    SDL_Rect background;
    int mouseX;
    int mouseY;
    SDL_Window *gWindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *buffer = NULL;
    TTF_Font * font;

    int current_state = INGAME;
    MapClass textureMap;
    std::map<int,Texture*> texture_map;
    int width = 640;
    int t_width = width/32;
    int height = 480;
    int t_height = height/32;
    int maxFPS = 60;
    bool hasChanged = true;

    int countedFrames = 0;
    float currentFPS = 0.f;
    float avgFPS = 0.f;
    LTimer timer;
    LTimer fpsTimer;
    int currentTick;
    int selected;
    const Uint8 *key;

    bool displayInventory = false;

    SDL_Color text_color = {255,255,255};
    bool running = true;

    void start()
    {
        printf("%d\n",current_state);
        key = SDL_GetKeyboardState(NULL);
        textureMap.init(renderer);

        if(!textureMap.loadMap("data/map2"))
        {
            std::cerr << "Map could not be loaded" << std::endl;
        }
        //std::map<int,Texture*> textures;
        Screen screen;
        Editor editor;
        InGame in_game;
        in_game.init();
        texture_map = textureMap.getMap();

        buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, width*2, height*2);

        fpsTimer.start();
        while(running)
        {
            /* Get current time */
            currentTick = (int)SDL_GetTicks();
            /* Get input from keyboard */

            switch(current_state)
            {
            case(MAINMENU):
                /* Show the main menu */
                screen.checkForInput();
                break;
            case(INGAME):
                in_game.checkForInput();
                in_game.render();
                break;
            case(PAUSED):
                screen.checkForInput();
                /* GAME IS PAUSED */
                /* Show menu */
                break;
            case(GAMEOVER):
                screen.checkForInput();
                /* Show a menu */
                break;
            case(EDITOR):
                editor.checkForInput();
                editor.render(); // SELECTED
                break;
            }

            avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if(avgFPS > 2000000)
            {
                avgFPS = 0;
            }
            if(((int)SDL_GetTicks() - currentTick) < 1000/game::getMaxFPS()) {
                SDL_Delay((int)((1000/game::getMaxFPS())-((int)SDL_GetTicks()-currentTick)));
            }
            countedFrames ++;
        }
    }

    bool init_game()
    {
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

        bool success = true;

        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Init video failed." << std::endl;
            success = false;
        }
        else
        {
            gWindow = SDL_CreateWindow("Hunta 2",SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                            width,height,SDL_WINDOW_SHOWN);
            if(gWindow == NULL)
            {
                std::cerr << "Window could not be created." << std::endl;
                success = false;
            }
            else
            {
                renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
                if(renderer == NULL)
                {
                    std::cerr << "renderer could not be created" << std::endl;
                    success = false;;
                }
                else
                {
                    if(IMG_Init(IMG_INIT_PNG) < 0)
                    {
                        std::cerr << "IMG_Init() failed." << std::endl;
                        success = false;
                    }
                    if(TTF_Init() != 0)
                    {
                        std::cerr << "TTF_Init() failed" << std::endl;
                        success = false;
                    }
                    else
                    {
                        font = TTF_OpenFont("freefont/FreeSans.ttf",24);
                        if(font == NULL)
                        {
                            std::cerr << "No font" << std::endl;
                            success = false;
                        }
                    }
                }
            }
        }
        return success;
    }

    bool inventoryIsDisplayed()
    {
        return displayInventory;
    }

    void showInventory()
    {
        displayInventory = true;
        hasChanged = true;
    }
    void hideInventory()
    {
        displayInventory = false;
        hasChanged = true;
    }

    void close()
    {
        for(auto iter = game::getTexture_map()->begin(); iter != game::getTexture_map()->end();iter++)
        {
            ((Texture*)iter->second)->free();
        }

        SDL_DestroyTexture(buffer);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(gWindow);
        renderer = NULL;
        gWindow = NULL;
        TTF_CloseFont(font);
        font = NULL;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }



    SDL_Event *getEvent()
    {
        return &event;
    }

    SDL_Rect *getOffset()
    {
        return &offset;
    }

    SDL_Rect *getRect()
    {
        return &rect;
    }

    void setRectX(int x)
    {
        rect.x = x;
    }

    SDL_Rect *getBackground()
    {
        return &background;
    }

    SDL_Color getText_color()
    {
        return text_color;
    }

    int getMouseX()
    {
        return mouseX;
    }

    void setMouseX(int x)
    {
        mouseX = x;
    }

    int getMouseY()
    {
        return mouseY;
    }

    void setMouseY(int y)
    {
        mouseY = y;
    }

    SDL_Window *getGWindow()
    {
        return gWindow;
    }

    SDL_Renderer *getRenderer()
    {
        return renderer;
    }

    SDL_Texture *getBuffer()
    {
        return buffer;
    }

    void setBuffer(SDL_Texture * temp)
    {
        buffer = temp;
    }

    TTF_Font * getFont()
    {
        return font;
    }

    int getCurrent_state()
    {
        return current_state;
    }

    void setCurrent_state(int temp)
    {
        current_state = temp;
    }

    MapClass *getTextureMap()
    {
        return &textureMap;
    }

    std::map<int,Texture*> *getTexture_map()
    {
        return &texture_map;
    }

    void setTexture_map(std::map<int,Texture*> temp_map)
    {
        texture_map = temp_map;
    }

    int getWidth()
    {
        return width;
    }

    int getT_width()
    {
        return t_width;
    }
    int getHeight()
    {
        return height;
    }
    int getT_height()
    {
        return t_height;
    }

    int getMaxFPS()
    {
        return maxFPS;
    }

    bool getHasChanged()
    {
        return hasChanged;
    }

    void setHasChanged(bool boolean)
    {
        hasChanged = boolean;
    }

    float getAvgFPS()
    {
        return avgFPS;
    }

    LTimer getTimer()
    {
        return timer;
    }

    void setRunning(bool boolean)
    {
        running = boolean;
    }

}

