//
// Created by fredrik on 2/18/16.
//

#include <SDL2/SDL_events.h>
#include "TextInputBox.hpp"
#include "Game.hpp"

TextInputBox::TextInputBox() {

}


TextInputBox::~TextInputBox() {

}


void TextInputBox::init() {
    textColor = {0xFF,0xFF,0xFF,0xFF};
    inputText = "";

   // desc.loadFromText("> ",textColor,game::getFont());

    text.loadFromText(inputText.c_str(),textColor,game::getFont());
}

void TextInputBox::draw() {
    //desc.render(posX-40,posY,nullptr);
    text.render(posX,posY,nullptr);
    if(renderText) {
        if(inputText != "") {
            text.loadFromText(inputText.c_str(),textColor,game::getFont());
        } else
            text.loadFromText(" ", textColor,game::getFont());
    }
}

void TextInputBox::update(SDL_Event e) {
    renderText = false;

    if(e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_ESCAPE) {
            inputDone();
        } else if(e.key.keysym.sym == SDLK_RETURN) {
            if(takeInput) {
                if(inputText.length() > 0)
                    funct(inputText);
                inputDone();
            } else {
                inputStart();
            }
        } else if(takeInput) {
            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                inputText.pop_back();
                renderText = true;
            } else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                SDL_SetClipboardText(inputText.c_str());
            else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                std::string temp = SDL_GetClipboardText();
                inputText.append(temp, 0, maxlen - inputText.length());
                renderText = true;
            }
        }
    }

    if(e.type == SDL_TEXTINPUT && takeInput) {
        if(!( (e.text.text[0] == 'c' || e.text.text[0] == 'C') &&
              (e.text.text[0] == 'v' || e.text.text[0] == 'V') &&
              SDL_GetModState() & KMOD_CTRL) &&
           inputText.length() < maxlen) {
            inputText += e.text.text;
            renderText = true;
        }
    }
}

void TextInputBox::setColor(SDL_Color color) {
    textColor = color;
}

void TextInputBox::inputStart() {
    takeInput = true;
    SDL_StartTextInput();
}

void TextInputBox::inputDone() {
    clear();
    takeInput = false;
    SDL_StopTextInput();
}

void TextInputBox::setOnEnter(std::function<void(std::string)> funct) {
    this->funct = funct;
}

void TextInputBox::setMaxlen(unsigned int max) {
     maxlen = max;
}

void TextInputBox::clear() {
    text.loadFromText(" ", textColor,game::getFont());
    inputText = "";
}

bool TextInputBox::takingInput() {
    return takeInput;
}

void TextInputBox::setPos(int x, int y) {
    posX = x;
    posY = y;
}
