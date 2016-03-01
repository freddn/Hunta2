#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTimer.hpp"
#include "MapController.hpp"
#include "Editor.hpp"
#include "TextureManager.hpp"
#include "ItemManager.hpp"
#include "PlayerController.hpp"
#include "UIController.hpp"
#include "EnemyManager.hpp"
#include "MouseController.hpp"
#include "CharacterCreationScreen.hpp"
#include "SaveSlotSelection.hpp"
#include "InGame.hpp"
#include "MainMenu.hpp"

namespace game {
    /** Getters for important game variables/objects. */
    Editor *getEditor();
    SDL_Event *getEvent();
    SDL_Rect *getOffset();
    SDL_Rect *getBackground();

    SDL_Window *getGWindow();

    SDL_Renderer *getRenderer();
    SDL_Texture *getBuffer();

    SDL_Color *getTextColor();
    TTF_Font *getFont();
    TTF_Font * getDmgFont();

    int getCurrentState();

    PlayerController *getPlayerController();
    UIController *getUIController();
    MapController *getTextureMapController();
    MouseController *getMouseController();

    ItemManager *getItemManager();
    EnemyManager *getEnemyDataController();
    TextureManager *getTextureManager();

    Inventory *getInventory();

    CharacterCreationScreen *getCharacterCreationScreen();
    SaveSlotSelection *getSaveSlotSelection();
    LuaInterface *getLuaInterface();
    InGame *getInGame();
    MainMenu *getMainMenu();
    Screen *getScreen();

    int getWidth();
    int getTWidth();
    int getHeight();
    int getTHeight();
    int getMouseX();
    int getMouseY();
    int getMaxFPS();
    bool getHasChanged();
    float getAvgFPS();
    LTimer* getTimer();
    LTimer* getFPSTimer();
    bool isRunning();

    /** Setters. */
    void setHasChanged(bool boolean);
    void setTextureMap(std::shared_ptr<Map> temp_map);
    void setBuffer(SDL_Texture *temp);
    void setRenderer(SDL_Renderer *r);
    void setFont(TTF_Font * f);
    void setDmgFont(TTF_Font * f);
    void setCurrentState(int temp);
    void setWindow(SDL_Window* window);
    void setMouseX(int x);
    void setMouseY(int y);
    void setAvgFPS(float a);
    void setRunning(bool boolean);
}

#endif // GLOBAL_H
