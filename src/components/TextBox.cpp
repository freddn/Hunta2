#include "TextBox.hpp"
#include "../common/HelperFunctions.hpp"

TextBox::TextBox(int x, int y, int w, int h, const std::string &str) :
        xPos(x), yPos(y), width(w), height(h), str(str) {
}

TextBox::~TextBox() {
    background = nullptr;
    backgroundOutline = nullptr;
}

void TextBox::draw() {
    if (active) {
        if (background != nullptr)
            SDL_RenderCopy(renderer, background, NULL, &boxRect);
        for(auto texture = text.begin();texture!=text.end();++texture)
            (*texture)->render((*texture)->getX(), (*texture)->getY(), NULL);
    }
}

void TextBox::setActive(bool active) {
    this->active = active;
}

void TextBox::init(SDL_Renderer *renderer, SDL_Color *color, TTF_Font *font) {
    this->renderer = renderer;
    boxRect.x = xPos;
    boxRect.y = yPos;
    boxRect.w = width;
    boxRect.h = height;
    SDL_Surface *backgroundSurface = SDL_CreateRGBSurface(0,boxRect.w,boxRect.h,32,0,0,0,0);
    SDL_FillRect(backgroundSurface,NULL,SDL_MapRGB(backgroundSurface->format,0,100,100));
    background = SDL_CreateTextureFromSurface(renderer,backgroundSurface);

    SDL_FreeSurface(backgroundSurface);

    std::string newStr = str;
    std::string tempStr = str;
    bool wrapped = false;
    while(!wrapped) {
        if(newStr.length() <= 0) {
            break;
        }
        Texture *textTexture = new Texture;
        textTexture->setXRect(xPos+10);
        textTexture->setYRect(yPos+10+((int)text.size()*32));

        if(textTexture->setText(newStr,color,font)) {
            int newLength = (int)((newStr.length() * ((float)boxRect.w / (float)textTexture->getWidth())) - 1);
            std::size_t found = newStr.find('\n', 0);
            if(found != std::string::npos && found <= (unsigned int)newLength) {
                tempStr = newStr;
                newStr = newStr.substr(0,found);
                textTexture->setText(newStr, color, font);
                newStr = tempStr.substr(found+1);
            } else if(newStr.length() > (unsigned int)newLength) {
                tempStr = newStr;
                newStr = newStr.substr(0, (unsigned int)newLength);
                if(newStr.length() == 0) {
                    HelperFunctions::log("string ended.");
                    break;
                }
                textTexture->setText(newStr, color, font);
                HelperFunctions::log("prev '" + newStr + "' next '" + tempStr.substr((unsigned long)newLength));
                newStr = tempStr.substr((unsigned long)newLength);

                if(newStr.length() == 0) {
                    HelperFunctions::log("string ended.");
                    break;
                }
            } else {
                wrapped = true;
            }
            HelperFunctions::log("text added to container..");
            std::unique_ptr<Texture> uPtr{textTexture};
            text.emplace_back(std::move(uPtr));

        } else
            wrapped = true;
    }
}

bool TextBox::isActive() { return active; }

