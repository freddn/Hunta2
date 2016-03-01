#include "Shape.hpp"

#include "Global.hpp"

Shape::Shape() {}

Shape::~Shape() {
    SDL_DestroyTexture(shape);
}


Shape::Shape(int w, int h,int r,int g,int b) {
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
}


void Shape::init() {
    position = &entity->getComponent<Position>();

    SDL_Surface * temp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,red,green,blue));
    shape = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);
}

void Shape::draw() {
    SDL_Rect rect{(int)position->getX(),(int)position->getY(),width,height};
    SDL_RenderCopy(game::getRenderer(),shape,NULL,&rect);
}

int Shape::getWidth() {
    return width;
}

int Shape::getHeight() {
    return height;
}
