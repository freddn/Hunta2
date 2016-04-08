
#include "CharacterCreationScreen.hpp"
#include "../Game.hpp"
#include "../Global.hpp"
#include "../Enums.hpp"
#include "../HelperFunctions.hpp"
#include <iostream>
CharacterCreationScreen::CharacterCreationScreen() {}

CharacterCreationScreen::~CharacterCreationScreen() {}

void CharacterCreationScreen::init() {
    textColor = game::getTextColor();
    inputText = "wolfhunter";

    desc.loadFromText("Enter name:  _____________________",textColor,game::getFont());

    text.loadFromText(inputText.c_str(),textColor,game::getFont());

    SDL_StartTextInput();
}

void CharacterCreationScreen::draw() {
    Screen::renderStart();

    game::getSaveSlotSelection()->draw();
    desc.render(200,200,nullptr);
    text.render(350,200,nullptr);

    Screen::renderEnd();
}

void CharacterCreationScreen::update(SDL_Event *e) {
    bool renderText = false;
    // game::getSaveSlotSelection()->update(e);
    if(e->type == SDL_KEYDOWN) {
        if(e->key.keysym.sym == SDLK_ESCAPE) {
            game::setCurrentState(game::MAINMENU);
        } else if(e->key.keysym.sym == SDLK_RETURN) {
            game::setCurrentState(game::INGAME);
            SDL_StopTextInput();
            game::newGame(inputText);
        } else if(e->key.keysym.sym == SDLK_BACKSPACE && inputText.length()>0) {
            inputText.pop_back();
            renderText = true;
        } else if(e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            SDL_SetClipboardText(inputText.c_str());
        else if(e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
            std::string temp = SDL_GetClipboardText();
            inputText.append(temp,0,maxlen-inputText.length());
            renderText = true;
        }
    }

    if(e->type == SDL_TEXTINPUT) {
        if(!( (e->text.text[0] == 'c' || e->text.text[0] == 'C') &&
              (e->text.text[0] == 'v' || e->text.text[0] == 'V') &&
              SDL_GetModState() & KMOD_CTRL) &&
           inputText.length() < maxlen) {
            inputText += e->text.text;
            renderText = true;
        }
    }

    if(renderText) {
        if(inputText != "") {
            text.loadFromText(inputText.c_str(),textColor,game::getFont());

        } else
            text.loadFromText(" ", textColor,game::getFont());
    }
}

// TODO Add save slot selection.. DONE
// TODO add background (low prio)
// TODO class selection (low prio)
// TODO start game button
// TODO add textbox
// TODO add back to menu button

int CharacterCreationScreen::getSaveSlot(std::string string) {
    if(nameOnSlot.find(string) != nameOnSlot.end())
        return nameOnSlot.at(string);
    else
        return -1;
}

void CharacterCreationScreen::saveSlot(int slot, std::string name, int level) {
    switch (slot) {
        case 1:
            name1 = name;
            level1 = level;
            saveslot1 = true;
            HelperFunctions::log(HelperFunctions::MESSAGE, "Saveslot 1 is used by "+name);
            break;
        case 2:
            name2 = name;
            level2 = level;
            saveslot2 = true;
            HelperFunctions::log(HelperFunctions::MESSAGE, "Saveslot 2 is used by "+name);
            break;
        case 3:
            name3 = name;
            level3 = level;
            saveslot3 = true;
            HelperFunctions::log(HelperFunctions::MESSAGE, "Saveslot 3 is used by "+name);
            break;
        default:
            break;
    }
}
