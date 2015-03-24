#ifndef INVENTORY_H
#define INVENTORY_H



#include <SDL2/SDL.h>

#include "Texture.hpp"


class Inventory
{
    public:
        Inventory();

        void init();
        void render();
        void checkForInput();
        void loadInventory();
        virtual ~Inventory();
    protected:
    private:
    SDL_Texture *inv_bg;
    Texture frame;
    int sizeX = 6;
    int sizeY = 6;
};

#endif // INVENTORY_H
