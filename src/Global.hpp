#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MapController.hpp"
#include "PlayerController.hpp"
#include "EnemyManager.hpp"

#include "components/MouseController.hpp"
#include "components/ItemManager.hpp"
#include "components/TextureManager.hpp"

#include "common/LTimer.hpp"
#include "common/HelperFunctions.hpp"

// Physics
#include "physics/PhysicsEngine.hpp"
#include "physics/Rect.h"

// Editor
#include "tools/Editor.hpp"

// UI
#include "ui/UIController.hpp"
#include "ui/CharacterCreationScreen.hpp"
#include "ui/SaveSlotSelection.hpp"
#include "ui/InGame.hpp"
#include "ui/MainMenu.hpp"

/**
 * This namespace holds alot of important game related objects.
 */
namespace game {
    /** Getters for important game variables/objects. */
    Editor *getEditor();

    SDL_Event *getEvent();

    Rect *getOffset();

    Rect *getBackground();

    SDL_Window *getGWindow();

    SDL_Renderer *getRenderer();

    SDL_Texture *getBuffer();

    SDL_Color *getTextColor();

    TTF_Font *getFont();

    TTF_Font *getDmgFont();

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

    physics::PhysicsEngine *getPhysicsEngine();

    int getWidth();

    int getHeight();

    float getMouseX();

    float getMouseY();

    float getAvgFPS();

    LTimer *getTimer();

    bool isRunning();

    /** Setters. */
    void setBuffer(SDL_Texture *temp);

    void setRenderer(SDL_Renderer *r);

    void setFont(TTF_Font *f);

    void setDmgFont(TTF_Font *f);

    void setCurrentState(int temp);

    void setWindow(SDL_Window *window);

    void setMouseX(float x);

    void setMouseY(float y);

    void setAvgFPS(float a);

    void setRunning(bool boolean);
}

#endif // GLOBAL_H
