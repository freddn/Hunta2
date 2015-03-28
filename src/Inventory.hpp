#ifndef INVENTORY_H
#define INVENTORY_H



#include <SDL2/SDL.h>

#include "Texture.hpp"


#include "EntitySystem.hpp"

using namespace EntitySystem;

struct Inventory : Component
{
    public:
        Inventory(int x, int y);
        void init();
        void update();
        void draw();
        void loadInventory();
        ~Inventory();
    protected:
    private:
        SDL_Texture *inv_bg;
        Texture frame;
        int sizeX = 6;
        int sizeY = 6;
};

#endif // INVENTORY_H
