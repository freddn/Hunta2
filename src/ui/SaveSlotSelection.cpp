#include <iostream>
#include "SaveSlotSelection.hpp"

#include "../Global.hpp"


SaveSlotSelection::SaveSlotSelection() {}

SaveSlotSelection::~SaveSlotSelection() {}


void SaveSlotSelection::init() {
    slot1.setImg("data/button.png", true, 256, 64);
    slot1.setRect(32*1, 40, 256, 64);
    slot1.setButtonText("No saved game", game::getTextColor(), game::getFont());
    slot1.onClick([](/* TODO goto Settings */) { });

    slot2.setImg("data/button.png", true, 256, 64);
    slot2.setRect(32*1, 120, 256, 64);
    slot2.setButtonText("No saved game", game::getTextColor(), game::getFont());
    slot2.onClick([](/* TODO goto Settings */) { });

    slot3.setImg("data/button.png", true, 256, 64);
    slot3.setRect(32*1, 200, 256, 64);
    slot3.setButtonText("No saved game", game::getTextColor(), game::getFont());
    slot3.onClick([](/* TODO Select */) { });
}

void SaveSlotSelection::update(SDL_Event *e) {
    int mX = game::getMouseX();
    int mY = game::getMouseY();

    /* Update the buttons. */
    slot1.update(e,mX,mY);
    slot2.update(e,mX,mY);
    slot3.update(e,mX,mY);
}

void SaveSlotSelection::draw() {
    slot1.draw();
    slot2.draw();
    slot3.draw();
}

void SaveSlotSelection::setSlot(int slot, std::string name, int level) {
    switch (slot) {
    case 1:
        std::cerr << name+" LV"+std::to_string(level)+"\n";
        slot1.setButtonText(name+" LV"+std::to_string(level), game::getTextColor(), game::getFont());
        break;
    case 2:
        std::cerr << name+" LV"+std::to_string(level)+"\n";
        slot2.setButtonText(name+" LV"+std::to_string(level), game::getTextColor(), game::getFont());
        break;
    case 3:
        std::cerr << name+" LV"+std::to_string(level)+"\n";
        slot3.setButtonText(name+" LV"+std::to_string(level), game::getTextColor(), game::getFont());
        break;
    default:
        break;
    }
}
