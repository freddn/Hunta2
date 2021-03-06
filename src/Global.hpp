#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTimer.hpp"
#include "MapController.hpp"
#include "tools/Editor.hpp"
#include "TextureManager.hpp"
#include "ItemManager.hpp"
#include "PlayerController.hpp"
#include "ui/UIController.hpp"
#include "EnemyManager.hpp"
#include "MouseController.hpp"
#include "ui/CharacterCreationScreen.hpp"
#include "ui/SaveSlotSelection.hpp"
#include "ui/InGame.hpp"
#include "ui/MainMenu.hpp"
#include "physics/PhysicsEngine.hpp"

/**
 * This namespace holds alot of important game related objects.
 */
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
