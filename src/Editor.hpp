#ifndef EDITOR_H
#define EDITOR_H

#include "Screen.hpp"
#include "Game.hpp"




class Editor : public Screen
{
    public:
        Editor();

        void checkForInput();
        void render(); /* TODO put selected in Editor. */


        virtual ~Editor();
    protected:
    private:
    SDL_Rect rground;
    SDL_Rect rwater;
    SDL_Rect rgrass;
    SDL_Rect sel;
    const Uint8 *key = NULL;
    //int selected;
    SDL_Surface *r_select;
    SDL_Texture *rect_select;
};

#endif // EDITOR_H
