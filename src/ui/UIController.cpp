#include "UIController.hpp"
#include "../Global.hpp"
#include "../common/HelperFunctions.hpp"

UIController::UIController() {
}

UIController::UIController( const UIController &obj) {
}

UIController::~UIController() {
}

void UIController::init() {
    HelperFunctions::log("UIController.init()");
    tInterface.loadFromFile("data/interface.png"); /// Sample interface
    SDL_Rect r = *((SDL_Rect*)game::getOffset());
    r.x = 0;
    r.y = 0;
    tInterface.setDestRect(r);
}

void UIController::draw() {
    //tInterface.render();
    if (showInventory) {
        game::getInventory()->draw();
    }
}

void UIController::update() {
    key = SDL_GetKeyboardState(NULL);
    if(key[SDL_SCANCODE_I]) {
        if (!showInventory && buf == 10) {
            buf = 0;
            showInventory = true;
            //game::getInventory()->loadInventory();
        } else if (showInventory && buf == 10) {
            buf = 0;
            showInventory = false;
        } else
            buf++;
    } else
        buf = 10;

    /* Inventory input */
    if(showInventory)
        game::getInventory()->update();
}

bool UIController::inventoryIsDisplayed() {
    return showInventory;
}

void UIController::setInventoryDisplayed(bool displayed) {
    showInventory = displayed;
}