#include "Icon.hpp"

#include "../Global.hpp"

Icon::Icon(std::string img) {
    iconImage.setClipped(true);
    iconImage.loadFromFile(img);
    iconImage.setClipW(0);
    iconImage.setClipH(0);

    SDL_Surface * temp = SDL_CreateRGBSurface(0,36,36,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,255,0,0));
    rSelect = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);
}

Icon::Icon(std::string img, int width, int height) {
    iconImage.setClipped(true);
    iconImage.loadFromFile(img);
    iconImage.setClipW(width);
    iconImage.setClipH(height);

    SDL_Surface * temp = SDL_CreateRGBSurface(0,36,36,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,255,0,0));
    rSelect = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);
}

void Icon::init() {


    //iconImage.init();
}

Icon::~Icon() {
    //dtor
}

void Icon::setSelected(bool s) {
    selected = s;
}

void Icon::draw() {
    if(selected) {
        SDL_Rect srcrect{0,0,36,36};
        SDL_Rect dstrect{posX-2,posY-2,36,36};
        SDL_RenderCopy(game::getRenderer(),rSelect,&srcrect,&dstrect);
    }
    iconImage.render(posX,posY,nullptr);
}

int Icon::getType() {
    return type;
}

void Icon::setType(int t) {
    type = t;
}

int Icon::getID() {
    return iconID;
}

void Icon::setID(int id) {
    iconID = id;
}

void Icon::setX(int x) {
    posX = x;
}
void Icon::setY(int y) {
    posY = y;
}
