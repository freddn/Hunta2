#include "Global.hpp"


namespace game {
    SDL_Event event;
    SDL_Rect offset;
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

    physics::PhysicsEngine physicsEngine(1000.0f/60.0f,10);

    Inventory inventory(580, 260);
    std::shared_ptr<Map> textureMap;
    int width = 800;
    int t_width = width/32;
    int height = 600;
    int t_height = height/32;
    int maxFPS = 45;
    float avgFPS = 0.f;
    bool hasChanged = true;

    LTimer timer;

    int selected;

    SDL_Color textColor = {255,255,255,0};
    bool running = true;

    Editor *getEditor() { return &editor; }

    SDL_Event *getEvent() { return &event; }
    SDL_Rect *getOffset() { return &offset; }
    SDL_Rect *getBackground() { return &background; }
    SDL_Color *getTextColor() { return &textColor; }

    int getMouseX() { return mouseX; }
    void setMouseX(int x) { mouseX = x; }
    int getMouseY() { return mouseY; }
    void setMouseY(int y) { mouseY = y; }

    SDL_Window *getGWindow() { return gWindow; }
    void setWindow(SDL_Window* window) { gWindow = window; }
    SDL_Renderer *getRenderer() { return renderer; }
    void setRenderer(SDL_Renderer *r) { renderer = r; }
    SDL_Texture *getBuffer() { return buffer; }

    void setBuffer(SDL_Texture * temp) { buffer = temp; }

    TTF_Font * getFont() { return font; }
    TTF_Font * getDmgFont() { return dmgFont; }
    void setFont(TTF_Font * f) { font = f; }
    void setDmgFont(TTF_Font * f) { dmgFont = f; }

    int getCurrentState() { return currentState; }
    void setCurrentState(int temp) { currentState = temp; }

    PlayerController *getPlayerController() { return &playerController; }
    MapController *getTextureMapController()  { return &mapController; }
    EnemyManager *getEnemyDataController() { return &enemyManager; }
    MouseController *getMouseController() { return &mouseController; }
    ItemManager *getItemManager() { return &itemManager; }

    Inventory *getInventory() { return &inventory; }

    std::shared_ptr<Map> getTextureMap() { return textureMap; }

    LuaInterface *getLuaInterface() { return &lInterface; }

    void setTextureMap(std::shared_ptr<Map> tempMap) { textureMap = tempMap; }
    TextureManager *getTextureManager() { return &textureManager; }

    CharacterCreationScreen *getCharacterCreationScreen() { return &creationScreen; }
    SaveSlotSelection *getSaveSlotSelection() { return &saveSlotSelection; }

    Screen *getScreen() { return &screen; }
    InGame *getInGame() { return &inGame; }
    MainMenu *getMainMenu() { return &mMenu; }
    UIController *getUIController() { return &uiController; }

    physics::PhysicsEngine *getPhysicsEngine() { return &physicsEngine; }

    int getWidth() { return width; }
    int getTWidth() { return t_width; }
    int getHeight() { return height; }
    int getTHeight() { return t_height; }
    int getMaxFPS() { return maxFPS; }
    float getAvgFPS() { return avgFPS; }
    void setAvgFPS(float a) { avgFPS = a; }
    bool getHasChanged() { return hasChanged; }

    void setHasChanged(bool boolean) { hasChanged = boolean; }

    LTimer* getTimer() { return &timer; }

    bool isRunning() { return running; }
    void setRunning(bool boolean) { running = boolean; }

}
