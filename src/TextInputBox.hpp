//
// Created by fredrik on 2/18/16.
//

#ifndef HUNTA2_TEXTINPUTBOX_HPP
#define HUNTA2_TEXTINPUTBOX_HPP

#include "Texture.hpp"

class TextInputBox {
public:
    TextInputBox();

    void draw();
    void update(SDL_Event e);
    void init();

    void inputStart();
    void inputDone();
    void clear();
    bool takingInput();
    void setColor(SDL_Color *color);
    void setMaxlen(unsigned int max);
    void setPos(int x, int y);
    void setOnEnter(std::function<void(std::string)> funct);

    virtual ~TextInputBox();

private:
    std::string inputText;
    SDL_Color *textColor;
    unsigned int maxlen = 250;
    Texture text;
    Texture desc;
    int posX = 200;
    int posY = 200;
    bool renderText = false;
    bool takeInput = false;
    std::function<void(std::string)> funct = nullptr;


};


#endif //HUNTA2_TEXTINPUTBOX_HPP
