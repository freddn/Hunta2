#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Texture
{
    public:
        Texture();
        bool loadFromFile(SDL_Renderer *renderer, std::string path);
        bool loadFromText(SDL_Renderer *renderer, std::string text, SDL_Color textcolor,TTF_Font * font);
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
    SDL_Texture *currentTexture = NULL;
    SDL_Rect rect;
    SDL_Rect tclip;
    bool solid = 0;
    std::string imageName = "image";
    int width = 640;
    int height = 480;
    int xPos;
    int yPos;
    int tWidth;
    int tHeight;
};

#endif // TEXTURE_H









