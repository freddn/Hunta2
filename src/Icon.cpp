#include "Icon.hpp"

#include "Game.hpp"

Icon::Icon(std::string img) {
    iconImage.setClipped(true);
    iconImage.loadFromFile(img);
    iconImage.setClipW(0);
    iconImage.setClipH(0);

    SDL_Surface * temp = SDL_CreateRGBSurface(0,36,36,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,255,0,0));
    rSelect = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);
    //ctor
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

std::size_t Icon::getType() {
    return type;
}

void Icon::setType(std::size_t t) {
    type = t;
}

int Icon::getID() {
    return iconID;
}

void Icon::setID(int id) {
    iconID = id;
}

std::string Icon::getImagePath() {
    return iconImage.getImgPath();
}

void Icon::setX(int x) {
    posX = x;
}
void Icon::setY(int y) {
    posY = y;
}
