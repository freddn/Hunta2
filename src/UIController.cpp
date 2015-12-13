#include "UIController.hpp"
#include "Game.hpp"
#include <iostream>
UIController::UIController() {
}

UIController::UIController( const UIController &obj) {
}

UIController::~UIController() {
}

void UIController::init() {
    std::cerr << "UIController.init()" << std::endl;
    tInterface.loadFromFile("data/interface.png"); /// Sample interface
}

void UIController::draw() {
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