#include "Global.hpp"


namespace game {
    SDL_Event event;
    Rect offset;
    Rect background;
    float mouseX = 0;
    float mouseY = 0;
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
    int currentState = -1;
    LuaInterface lInterface;
    MapController mapController;
    TextureManager textureManager;
    PlayerController playerController;
    EnemyManager enemyManager;
    ItemManager itemManager;
    UIController uiController;
    MouseController mouseController;
    CharacterCreationScreen creationScreen;
    SaveSlotSelection saveSlotSelection;

    physics::PhysicsEngine physicsEngine(1000.0f / 60.0f, 10);

    Inventory inventory(580, 260);
    int width = 800;
    int height = 600;
    float avgFPS = 0.f;

    LTimer timer;

    SDL_Color textColor = {255, 255, 255, 0};
    bool running = true;

    Editor *getEditor() { return &editor; }

    SDL_Event *getEvent() { return &event; }

    Rect *getOffset() { return &offset; }

    Rect *getBackground() { return &background; }

    SDL_Color *getTextColor() { return &textColor; }

    float getMouseX() { return mouseX; }

    void setMouseX(float x) { mouseX = x; }

    float getMouseY() { return mouseY; }

    void setMouseY(float y) { mouseY = y; }

    SDL_Window *getGWindow() { return gWindow; }

    void setWindow(SDL_Window *window) { gWindow = window; }

    SDL_Renderer *getRenderer() { return renderer; }

    void setRenderer(SDL_Renderer *r) { renderer = r; }

    SDL_Texture *getBuffer() { return buffer; }

    void setBuffer(SDL_Texture *temp) { buffer = temp; }

    TTF_Font *getFont() { return font; }

    TTF_Font *getDmgFont() { return dmgFont; }

    void setFont(TTF_Font *f) { font = f; }

    void setDmgFont(TTF_Font *f) { dmgFont = f; }

    int getCurrentState() { return currentState; }

    void setCurrentState(int temp) { currentState = temp; }

    PlayerController *getPlayerController() { return &playerController; }

    MapController *getTextureMapController() { return &mapController; }

    EnemyManager *getEnemyDataController() { return &enemyManager; }

    MouseController *getMouseController() { return &mouseController; }

    ItemManager *getItemManager() { return &itemManager; }

    Inventory *getInventory() { return &inventory; }

    LuaInterface *getLuaInterface() { return &lInterface; }

    TextureManager *getTextureManager() { return &textureManager; }

    CharacterCreationScreen *getCharacterCreationScreen() { return &creationScreen; }

    SaveSlotSelection *getSaveSlotSelection() { return &saveSlotSelection; }

    Screen *getScreen() { return &screen; }

    InGame *getInGame() { return &inGame; }

    MainMenu *getMainMenu() { return &mMenu; }

    UIController *getUIController() { return &uiController; }

    physics::PhysicsEngine *getPhysicsEngine() { return &physicsEngine; }

    int getWidth() { return width; }

    int getHeight() { return height; }

    float getAvgFPS() { return avgFPS; }

    void setAvgFPS(float a) { avgFPS = a; }

    LTimer *getTimer() { return &timer; }

    bool isRunning() { return running; }

    void setRunning(bool boolean) { running = boolean; }
}
