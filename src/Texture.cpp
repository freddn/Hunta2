/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 *
 * This file is a part of the Hunta2 project.
 *
 * Hunta2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hunta2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Texture.hpp"
#include "Global.hpp"

#include <iostream>

Texture::Texture() {
    tclip.w = 32;
    tclip.h = 32;
}

Texture::Texture(int w, int h) {
    tclip.w = w;
    tclip.h = h;
    isClipped = true;
}

Texture::Texture(const std::string &img,bool clip) : imageName(img) {
    isClipped = clip;
    isText = false;
    //currentTexture = nullptr;
    tclip.w = 32;
    tclip.h = 32;
}

Texture::Texture(const std::string &img,bool clip, int w,int h) : imageName(img) {
    isClipped = clip;
    isText = false;
    tclip.w = w;
    tclip.h = h;
}

Texture::Texture(const std::string &text, SDL_Color *textcolor, TTF_Font* font) :
                                        textFont(font),
                                        textColor(textcolor),
                                        textString(text) {
    isText = true;
}

Texture::~Texture() {}

void Texture::init() {
    tWidth = 0;
    tHeight = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    if(entity != nullptr && entity->hasComponent<Position>())
        position = &entity->getComponent<Position>();
    if(!isText)
        loadFromFile(imageName);
    else
        loadFromText(textString,textColor,textFont);
}

void Texture::draw() {
    // draw only on screen ..
    /*if(position->getX()+tWidth > game::getOffset()->x &&
        position->getX() < game::getOffset()->x + game::getWidth() &&
        position->getY()+tHeight > game::getOffset()->y &&
        position->getY() < game::getOffset()->y + game::getHeight())*/
    //std::cerr << game::getOffset()->w << std::endl;
    //int x = game::getOffset()->x;
    render(position->getX()-(game::getOffset()->x),
                position->getY()-(game::getOffset()->y),(SDL_Rect*)nullptr);
}

bool Texture::loadFromFile(const std::string &path) {
    free();
    if(!game::getTextureManager()->hasTexture(path)) {
        SDL_Renderer *renderer = game::getRenderer();
        imageName = path;
        SDL_Surface *tempSurface = IMG_Load(imageName.c_str());

        if(tempSurface == nullptr) {
            std::cerr << "IMG_Load() failed. Image: "<< path << std::endl;
            return false;
        }
        SDL_SetColorKey(tempSurface,SDL_TRUE,
            SDL_MapRGB(tempSurface->format,0xFF,0,0xFF));
        currentTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
    } else {
        currentTexture = game::getTextureManager()->getTexture(path);
    }

    if(currentTexture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface() failed" << std::endl;
        return false;
    }

    SDL_QueryTexture(currentTexture,NULL,NULL,&tWidth,&tHeight);

    if(isClipped) {
        rect.w = tclip.w;
        rect.h = tclip.h;
    } else {
        rect.w = tWidth;
        rect.h = tHeight;
    }
    tclip.x = 0;
    tclip.y = 0;

    return true;
}

bool Texture::loadFromText(const std::string &textureText, SDL_Color *textcolor,
                            TTF_Font * font) {
    free();
    SDL_Renderer *renderer = game::getRenderer();
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font,textureText.c_str(), *textcolor);

    if(tempSurface == nullptr)
        std::cerr << "TTF_RenderText_Solid() failed" << std::endl;
    else {
        currentTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);

        if(currentTexture == nullptr)
            std::cerr << "SDL_CreateTextureFromSurface() failed" << std::endl;
        else {
            tWidth = tempSurface->w;
            tHeight = tempSurface->h;
            rect.w = tWidth;
            rect.h = tHeight;
        }
        SDL_FreeSurface(tempSurface);
    }
    return currentTexture != nullptr;
}

void Texture::free() {
    SDL_DestroyTexture(currentTexture);
    currentTexture = nullptr;
}

void Texture::render(SDL_Rect *clip) {
    render(rect.x, rect.y,clip);
}

void Texture::render(int x, int y,SDL_Rect *clip) {
    SDL_Renderer *renderer = game::getRenderer();
    if(renderer != nullptr) {
        rect.x = x;
        rect.y = y;

        if(clip != nullptr) {
            rect.w = clip->w;
            rect.h = clip->h;
        } else if(tclip.w != 0 && tclip.h != 0 && isClipped)
            clip = &tclip;
        else
            clip = NULL;
        SDL_RenderCopy(renderer,currentTexture, clip,&rect);
        //SDL_RenderCopyEx(renderer,currentTexture, clip,&rect,0.0,nullptr,SDL_FLIP_NONE);
    }
}

void Texture::setSolid(bool s) {
    solid = s;
}

bool Texture::isSolid() {
    return solid;
}

int Texture::getWidth() {
    if(!isClipped)
        return tWidth;
    else
        return tclip.w;
}

int Texture::getHeight() {
    if(!isClipped)
        return tHeight;
    else
        return tclip.h;
}

int Texture::getX() {
    return rect.x;
}

void Texture::setXPos(int x) {
    xPos = x;
}

void Texture::setXRect(int x) {
    rect.x = x;
}

int Texture::getY() {
    return rect.y;
}

void Texture::setYPos(int y) {
    yPos = y;
}

void Texture::setYRect(int y) {
    rect.y = y;
}

void Texture::setClipped(bool clipped) {
    isClipped = clipped;
}

void Texture::setDestRect(const SDL_Rect &destRect) {
    rect.h = destRect.h;
    rect.w = destRect.w;
    rect.x = destRect.x;
    rect.y = destRect.y;
}

SDL_Rect Texture::getRect() {
    return rect;
}

std::string Texture::getImgPath() {
    return imageName;
}

void Texture::setClipX(int x) {

    tclip.x = tclip.w*x;
}

void Texture::setClipY(int y) {
    tclip.y = tclip.h*y;
}

void Texture::setClipW(int w) {
    tclip.w = w;
}

void Texture::setClipH(int h) {
    tclip.h = h;
}

SDL_Texture * Texture::getTexture() {
    return currentTexture;
}

std::shared_ptr<Texture> Texture::clone() const {
    return cloneThis();
}

std::shared_ptr<Texture> Texture::cloneThis() const {
    return (std::shared_ptr<Texture>(new Texture(*this)));
}
