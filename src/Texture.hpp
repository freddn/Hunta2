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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "EntitySystem.hpp"
#include "Position.hpp"

/** Texture class. Can load an image, render the texture and get texture data.*/
struct Texture : EntitySystem::Component {
public:
    /** Create a regular texture, size will be set as the size of the image. */
    Texture();
    Texture(int w, int h);
    /** Create a texture and choose if it is clipped, clip = 32 x 32 px. */
    Texture(std::string img,bool clip);

    /** Create a texture and choose if it is clipped, clip = w x h px. */
    Texture(std::string img, bool clip, int w, int h);

    /** Create a text that can be drawn to the screen. */
    Texture(std::string text, SDL_Color textcolor, TTF_Font* font);

    void init();
    void draw();

    /** Loads an image to the texture. */
    bool loadFromFile(std::string path);

    /** Loads a text string to the texture. */
    bool loadFromText(std::string text, SDL_Color textcolor,TTF_Font *font);
    void free();
    // (
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    // )
    /** Renders the texture on the screen at x-position = x and y-position = y. */
    void render(int x, int y,
                    SDL_Rect* clip = NULL);/*,double angle = 0.0,
                SDL_Point* center = NULL,SDL_RendererFlip = SDL_FLIP_NONE);*/

    /** Renders the image on the screen at x-position = rect.x and
     * y-position = rect.y. */
    void render(SDL_Rect* clip = NULL);
                    /*double angle = 0.0, SDL_Point* center = NULL,
                    SDL_RendererFlip = SDL_FLIP_NONE);*/

    /** Getters and setters. */
    int getWidth();
    int getHeight();
    SDL_Rect getRect();
    void setXPos(int x);
    void setYPos(int y);
    void setXRect(int x);
    void setYRect(int y);
    int getX();
    int getY();

    void setClipped(bool clipped);
    void setClipX(int x);
    void setClipY(int y);
    void setClipW(int w);
    void setClipH(int h);
    void setClip(SDL_Rect *clip);

    std::string getImgPath();
    bool isSolid();
    void setSolid(bool solidBool);

    /** Gets a new instance of current texture. Shared SDL_Texture so
     * need to keep the original SDL_Texture unfree'd. */
    //Texture *clone() const { return new Texture(*this); }
    std::shared_ptr<Texture> clone() const;// {return cloneThis()}
    ~Texture();
private:
    virtual std::shared_ptr<Texture> cloneThis() const;

    Position *position{nullptr};

    SDL_Texture *currentTexture{nullptr};
    SDL_Rect rect;
    SDL_Rect tclip;
    SDL_Color textColor;
    TTF_Font* textFont{nullptr};
    bool isClipped = false;
    bool isText = false;
    bool solid = false; // texture is solid?
    std::string imageName = "image_name";
    std::string textString;
    int xPos;
    int yPos;
    int tWidth; //texture width
    int tHeight; //texture height
};

#endif // TEXTURE_H









