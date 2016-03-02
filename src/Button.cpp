
#include "Button.hpp"

void Button::draw() {
    if(pressed)
        buttonBackground.setClipY(2);
    else if(hoover)
        buttonBackground.setClipY(1);
    else
        buttonBackground.setClipY(0);
    buttonBackground.render(buttonRect.x, buttonRect.y, nullptr);
    buttonText.render(buttonRect.x+20, buttonRect.y+18, nullptr);
}

void Button::update(SDL_Event *event, int mouseX, int mouseY) {

    if (mouseOverRect(buttonRect, mouseX, mouseY))
        hoover = true;
    else {
        hoover = false;
        pressed = false;
    }

    if(event->type == SDL_MOUSEBUTTONDOWN) {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            pressed = mouseOverRect(buttonRect, mouseX, mouseY) ? true : false;
        }
    }
    if(event->type == SDL_MOUSEBUTTONUP) {
        if(SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if(mouseOverRect(buttonRect, mouseX, mouseY)) {
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


void Button::setImg(std::string img) {
    buttonBackground.loadFromFile(img);
}

void Button::setImg(std::string img, bool clipped, int cw, int ch) {
    buttonBackground.setClipped(clipped);
    buttonBackground.setClipW(cw);
    buttonBackground.setClipH(ch);
    buttonBackground.loadFromFile(img);
}

SDL_Rect *Button::getRect() {
    return &buttonRect;
}

void Button::setClipH(int ch) {
    buttonBackground.setClipH(ch);
}

void Button::setClipW(int cw) {
    buttonBackground.setClipW(cw);
}

void Button::setClipped(bool clipped) {
    buttonBackground.setClipped(clipped);
}

void Button::setRect(int x, int y, int w, int h) {
    buttonRect.x = x;
    buttonRect.y = y;
    buttonRect.w = w;
    buttonRect.h = h;
}

void Button::setPosY(int y) {
    buttonRect.y = y;
}

void Button::setPosX(int x) {
    buttonRect.x = x;
}

void Button::setHeight(int h) {
    buttonRect.h = h;
}

void Button::setWidth(int w) {
    buttonRect.w = w;
}

void Button::setButtonText(std::string text, SDL_Color *color, TTF_Font *font) {
    buttonText.loadFromText(text, color, font);
}

bool Button::mouseOverRect(SDL_Rect r, int mouseX, int mouseY) {
    return mouseX < r.x+r.w && mouseX > r.x &&
            mouseY < r.y+r.h && mouseY > r.y;
}

