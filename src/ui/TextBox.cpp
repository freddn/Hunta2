//
// Created by fredrik on 3/2/16.
//

#include <iostream>
#include "TextBox.hpp"


TextBox::TextBox(int x, int y, int w, int h, const std::string &str) :
        xPos(x), yPos(y), width(w), height(h), str(str) {
}

TextBox::~TextBox() {
    if(background != nullptr)
        SDL_DestroyTexture(background);
    if(boxRect != nullptr)
        delete boxRect;
}


void TextBox::draw() {
    if (active) {
        if (background != nullptr)
            SDL_RenderCopy(renderer, background, NULL, boxRect);
        for(auto texture = text.begin();texture!=text.end();++texture)
            (*texture)->render((*texture)->getX(), (*texture)->getY(), NULL);
    }
}

void TextBox::remove() {
    active = false;
}


void TextBox::setActive(bool active) {
    this->active = active;
}

void TextBox::setText(const std::string &str) {
    this->str = str;
}

void TextBox::init(SDL_Renderer *renderer, SDL_Color *color, TTF_Font *font) {
    this->renderer = renderer;
    boxRect = new SDL_Rect;
    boxRect->x = xPos;
    boxRect->y = yPos;
    boxRect->w = width;
    boxRect->h = height;
    SDL_Surface *temp = SDL_CreateRGBSurface(0,boxRect->w,boxRect->h,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,0,100,100));
    background = SDL_CreateTextureFromSurface(renderer,temp);

    SDL_FreeSurface(temp);

    std::string newStr = str;
    std::string tempStr = str;
    bool wrapped = false;
    while(!wrapped) {
        if(newStr.length() <= 0) {
            break;
        }
        Texture *temp = new Texture;
        temp->setXRect(xPos+10);
        temp->setYRect(yPos+10+(text.size()*32));

        if(temp->loadFromText(newStr,color,font)) {
            unsigned long newLength = (int)((newStr.length() * ((float)boxRect->w / (float)temp->getWidth())) - 1);
            std::size_t found = newStr.find('\n', 0);
            if(found != std::string::npos && found <= newLength) {
                tempStr = newStr;
                newStr = newStr.substr(0,found);
                temp->loadFromText(newStr, color, font);
                newStr = tempStr.substr(found+1);
            } else if(newStr.length() > newLength) {
                tempStr = newStr;
                newStr = newStr.substr(0, newLength);
                if(newStr.length() == 0) {
                    std::cerr << "string ended.\n";
                    break;
                }
                temp->loadFromText(newStr, color, font);
                std::cerr << "prev '" << newStr << "' next '" << tempStr.substr(newLength) << "'\n";
                newStr = tempStr.substr(newLength);

                if(newStr.length() == 0) {
                    std::cerr << "string ended.\n";
                    break;
                }
            } else {
                wrapped = true;
            }
            std::cerr << "text added to container..\n";
            std::unique_ptr<Texture> uPtr{temp};
            text.emplace_back(std::move(uPtr));

        } else
            wrapped = true;
    }
}

bool TextBox::isActive() { return active; }

