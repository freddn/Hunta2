
#include "CharacterCreationScreen.hpp"
#include "Game.hpp"
#include <iostream>
CharacterCreationScreen::CharacterCreationScreen() {}

CharacterCreationScreen::~CharacterCreationScreen() {}

void CharacterCreationScreen::init() {

}

void CharacterCreationScreen::draw() {

}

void CharacterCreationScreen::update() {


}

void CharacterCreationScreen::createCharacter() {
    bool renderText = false;
    SDL_Event e;
    SDL_Color textColor = {0xFF,0xFF,0xFF,0xFF};

    std::string inputText = "Some text";

    Texture text;
    Texture desc;
    desc.loadFromText("Enter name:",textColor,game::getFont());

    text.loadFromText(inputText.c_str(),textColor,game::getFont());

    SDL_StartTextInput();
    bool running = true;
    while(running) {
        renderText = false;

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    game::setCurrent_state(game::MAINMENU);
                } else if(e.key.keysym.sym == SDLK_RETURN) {
                    running = false;
                    game::setCurrent_state(game::INGAME);
                    game::newGame(inputText);
                } else if(e.key.keysym.sym == SDLK_BACKSPACE && inputText.length()>0) {
                    inputText.pop_back();
                    renderText = true;
                } else if(e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                    SDL_SetClipboardText(inputText.c_str());
                else if(e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    inputText = SDL_GetClipboardText();
                    renderText = true;
                }
            }

            if(e.type == SDL_TEXTINPUT) {
                if(!( (e.text.text[0] == 'c' || e.text.text[0] == 'C') &&
                            (e.text.text[0] == 'v' || e.text.text[0] == 'V') &&
                        SDL_GetModState() & KMOD_CTRL)) {
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }
        if(renderText) {
            if(inputText != "") {
                text.loadFromText(inputText.c_str(),textColor,game::getFont());

            } else
                text.loadFromText(" ", textColor,game::getFont());
        }
        //SDL_SetRenderDrawColor(game::getRenderer())
        SDL_RenderClear(game::getRenderer());

        desc.render(50,200,nullptr);
        text.render(200,200,nullptr);

        SDL_RenderPresent(game::getRenderer());

    }
    SDL_StopTextInput();

}
