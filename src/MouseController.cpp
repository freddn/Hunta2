#include "MouseController.hpp"
#include "SDL2/SDL.h"

#include "Texture.hpp"
#include "Shape.hpp"
MouseController::MouseController()
{
    //ctor
}

MouseController::MouseController(bool x, bool y) {
    controllX = x;
    controllY = y;
}

MouseController::~MouseController()
{
    //dtor
}

void MouseController::init() {
    position = &entity->getComponent<Position>();
    if(entity->hasComponent<Texture>()) {
        width = entity->getComponent<Texture>().getWidth();
        height = entity->getComponent<Texture>().getHeight();
    } else if(entity->hasComponent<Shape>()) {
        width = entity->getComponent<Shape>().getWidth();
        height = entity->getComponent<Shape>().getHeight();
    }
    setCenteredX(true);
}

void MouseController::update() {
    int tempX = mouseX;
    int tempY = mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    if(tempX != mouseX && controllX)
        position->setX(mouseX - (width/2));
    if(tempY != mouseY && controllY)
        position->setY(mouseY - (height/2));

}


void MouseController::setMouseX(int x) {}

void MouseController::setMouseY(int y) {}

int MouseController::getMouseX() {
    return mouseX;
}

int MouseController::getMouseY() {
    return mouseY;
}

bool MouseController::rightMouseButton() {
    return rMouseBtn;
}

bool MouseController::leftMouseButton() {
    return lMouseBtn;
}

void MouseController::setRMouseBtn(bool rMouse) {
    rMouseBtn = rMouse;
}

void MouseController::setLMouseBtn(bool lMouse) {
    lMouseBtn = lMouse;
}

void MouseController::setCenteredX(bool c) {
    if(!c)
        width = 0;
}

void MouseController::setCenteredY(bool c) {
    if(!c)
        height = 0;
}



