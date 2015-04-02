#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "EntitySystem.hpp"
#include "Position.hpp"

/* Texture class. Can load an image, render the texture and get texture data.*/
struct Texture : EntitySystem::Component
{
    public:
        Texture();
        Texture(std::string img);
        Texture(std::string text,SDL_Color textcolor,TTF_Font* font);

        void init(); // Component
        void draw(); // Component
        void update(); // Component

        bool loadFromFile(SDL_Renderer *renderer, std::string path);
        bool loadFromText(SDL_Renderer *renderer, std::string text, SDL_Color textcolor,TTF_Font *font);
        void free();
        // (
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        // )
        void render(SDL_Renderer *renderer, int x, int y,SDL_Rect* clip = NULL,double angle = 0.0,
                    SDL_Point* center = NULL,SDL_RendererFlip = SDL_FLIP_NONE);
        void render(SDL_Renderer *renderer, SDL_Rect* clip = NULL,double angle = 0.0,
                    SDL_Point* center = NULL,SDL_RendererFlip = SDL_FLIP_NONE);
        int getWidth();
        int getHeight();
        SDL_Rect getRect();
        void setXPos(int x);
        void setYPos(int y);
        void setXRect(int x);
        void setYRect(int y);
        int getX();
        int getY();

        void setClipX(int x);
        void setClipY(int y);

        std::string getImgPath();
        bool isSolid();
        void setSolid(bool solidBool);
        Texture *clone() const { return new Texture(*this); }

        ~Texture();
    protected:
    private:
        Position *position{nullptr};
        SDL_Texture *currentTexture = NULL;
        SDL_Rect rect;
        SDL_Rect tclip;
        SDL_Color textColor;
        TTF_Font* textFont;
        bool isText = false;
        bool solid = false; // texture is solid?
        std::string imageName = "image";
        std::string textString;
        int xPos;
        int yPos;
        int tWidth; //texture width
        int tHeight; //texture height
};

#endif // TEXTURE_H









