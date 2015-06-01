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
#include "Game.hpp"


Texture::Texture() {
    currentTexture = NULL;
    tWidth = 0;
    tHeight = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Texture::Texture(std::string img,bool clip) {
    isClipped = clip;
    isText = false;
    imageName = img;
    currentTexture = NULL;
    tclip.w = 32;
    tclip.h = 32;
    tWidth = 0;
    tHeight = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Texture::Texture(std::string img,bool clip, int w,int h) {
    isClipped = clip;

    isText = false;
    imageName = img;
    currentTexture = NULL;
    tWidth = 0;
    tHeight = 0;
    tclip.w = w;
    tclip.h = h;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Texture::Texture(std::string text,SDL_Color textcolor,TTF_Font* font) {
    isText = true;
    textFont = font;
    textColor = textcolor;
    textString = text;
    currentTexture = NULL;
    tWidth = 0;
    tHeight = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Texture::~Texture() {
    free();
}

void Texture::init() {
    //std::cout << " - Texture::init() ..." << std::endl;
    position = &entity->getComponent<Position>();

    if(!isText)
        loadFromFile(game::getRenderer(),imageName);
    else
        loadFromText(game::getRenderer(),textString,textColor,textFont);
}

void Texture::draw() {
    //std::cerr << "-- Texture::draw"<<std::endl;
    if(position->getX()+tWidth > game::getOffset()->x &&
        position->getX() < game::getOffset()->x + game::getWidth() &&
        position->getY()+tHeight > game::getOffset()->y &&
        position->getY() < game::getOffset()->y + game::getHeight())
    render(game::getRenderer(),position->getX()-game::getOffset()->x,
                position->getY()-game::getOffset()->y,(SDL_Rect*)NULL,
                (double)0.0,NULL,SDL_FLIP_NONE);
}
/*
void Texture::update()
{
    //std::cerr<< "Texture::update()"<<std::endl;
}
*/

bool Texture::loadFromFile(SDL_Renderer *renderer, std::string path) {
    free();
    imageName = path;
    SDL_Surface *tempSurface = IMG_Load(imageName.c_str());

    if(tempSurface == NULL)
        std::cerr << "IMG_Load() failed. Image: "<< path << std::endl;
    else {
        SDL_SetColorKey(tempSurface,SDL_TRUE,
            SDL_MapRGB(tempSurface->format,0xFF,0,0xFF));
        currentTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);

        if(currentTexture == NULL) {
            std::cerr << "SDL_CreateTextureFromSurface() failed" << std::endl;
        } else {
            tWidth = tempSurface->w;
            tHeight = tempSurface->h;

            if(isClipped) {
                rect.w = tclip.w; // tWidth
                rect.h = tclip.h; // tWidth
            } else {
                rect.w = tWidth;
                rect.h = tHeight;
            }
            tclip.x = 0;
            tclip.y = 0;
        }
        SDL_FreeSurface(tempSurface);
    }
    return currentTexture != NULL;
}

bool Texture::loadFromText( SDL_Renderer *renderer, std::string textureText,
                            SDL_Color textcolor, TTF_Font * font) {
    free();
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font,textureText.c_str(), textcolor);

    if(tempSurface == NULL)
        std::cerr << "TTF_RenderText_Solid() failed" << std::endl;
    else {
        currentTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);

        if(currentTexture == NULL)
            std::cerr << "SDL_CreateTextureFromSurface() failed" << std::endl;
        else {
            tWidth = tempSurface->w;
            tHeight = tempSurface->h;
            rect.w = tWidth;
            rect.h = tHeight;
        }
        SDL_FreeSurface(tempSurface);
    }
    return currentTexture != NULL;
}

void Texture::free() {
    if(currentTexture != NULL) {
        SDL_DestroyTexture(currentTexture);

        currentTexture = NULL;
        tWidth = 0;
        tHeight = 0;
    }

}

void Texture::render(SDL_Renderer * renderer,SDL_Rect* clip,double angle,
                    SDL_Point* center,SDL_RendererFlip flip) {
    render(renderer,rect.x , rect.y,clip,angle,
                    center,flip);
}


void Texture::render(   SDL_Renderer * renderer, int x, int y,SDL_Rect* clip,
                        double angle, SDL_Point* center,SDL_RendererFlip flip) {
    rect.x = x;
    rect.y = y;

    if(clip != NULL) {
        rect.w = clip->w;
        rect.h = clip->h;
    } else if(tclip.w != 0 && tclip.h != 0 && isClipped)
        clip = &tclip;

    SDL_RenderCopyEx(renderer,currentTexture, clip,&rect,angle,center,flip);
}

void Texture::setSolid(bool s) {
    solid = s;
}

bool Texture::isSolid() {
    return solid;
}

int Texture::getWidth() {
    return tWidth;
}

int Texture::getHeight() {
    return tHeight;
}

int Texture::getX() {
    return xPos;
    //return rect.x;
}

void Texture::setXPos(int x) {
    xPos = x;
    //position->setX(x);
    //rect.x = x;
}

void Texture::setXRect(int x) {
    rect.x = x;
}

int Texture::getY() {
    return yPos;
    //return rect.y;
}

void Texture::setYPos(int y) {
    yPos = y;
    //rect.y = y;
}

void Texture::setYRect(int y) {
    rect.y = y;
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


