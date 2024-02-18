
#include "Button.hpp"

void Button::draw() {
    if(pressed)
        buttonBackground.setClipY(2);
    else if(hoover)
        buttonBackground.setClipY(1);
    else
        buttonBackground.setClipY(0);
    buttonBackground.render(buttonX, buttonY, nullptr);
    buttonText.render(buttonX+20, buttonY+18, nullptr);
}

void Button::update(SDL_Event *event, int mouseX, int mouseY) {

    if (mouseOverButton(mouseX, mouseY))
        hoover = true;
    else {
        hoover = false;
        pressed = false;
    }

    if(event->type == SDL_MOUSEBUTTONDOWN) {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            pressed = mouseOverButton(mouseX, mouseY);
        }
    }
    if(event->type == SDL_MOUSEBUTTONUP) {
        if(SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if(mouseOverButton(mouseX, mouseY)) {
                if(function != nullptr)
                    function();
            } else
                pressed = false;
        }
    }
}

void Button::onClick(std::function<void()> func) {
    function = func;
}

void Button::setImg(std::string img, bool clipped, int cw, int ch) {
    buttonBackground.setClipped(clipped);
    buttonBackground.setClipW(cw);
    buttonBackground.setClipH(ch);
    buttonBackground.loadFromFile(img);
}

void Button::setRect(int x, int y, int w, int h) {
    buttonX = x;
    buttonY = y;
    buttonW = w;
    buttonH = h;
}

Texture Button::getTextTexture() {
    return buttonText;
}

bool Button::mouseOverButton(int mouseX, int mouseY) {
    return mouseX < buttonX+buttonW && mouseX > buttonX &&
            mouseY < buttonY+buttonH && mouseY > buttonY;
}

