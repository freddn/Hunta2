#include "UIController.hpp"

UIController::UIController() {
    inventory = new Inventory(445,150);
}

UIController::UIController( const UIController &obj) {
    inventory = new Inventory(445,150);
    *inventory = *obj.inventory;
}

UIController::~UIController() {
    delete inventory;
}

void UIController::init() {
    inventory->init();
    tInterface.loadFromFile("data/interface.png"); /// Sample interface
}

void UIController::draw() {
    if (showInventory) {
        inventory->draw();
    }
}

void UIController::update() {
    key = SDL_GetKeyboardState(NULL);
    if(key[SDL_SCANCODE_I]) {
        if (!showInventory && buf == 10) {
            buf = 0;
            showInventory = true;
            inventory->loadInventory();
        } else if (showInventory && buf == 10) {
            buf = 0;
            showInventory = false;
        } else
            buf++;
    } else
        buf = 10;

    /* Inventory input */
    if(showInventory)
        inventory->update();
}