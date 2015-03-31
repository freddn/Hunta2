#ifndef EDITOR_H
#define EDITOR_H

#include "Screen.hpp"
#include "Game.hpp"

/* This class represents the map-editor.
 * Currently we can only draw the background-tiles.
 * TODO Put objects on the map. Trees/houses/enemys.
 */
struct Editor : public Screen
{
    public:
        Editor();
        void init();
        void update();
        void draw();
        ~Editor();
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
