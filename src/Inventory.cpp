#include "Inventory.hpp"

#include "Game.hpp"


using namespace EntitySystem;

/*Inventory::~Inventory()
{

}
*/


void Inventory::init()
{
    frame.loadFromFile(game::getRenderer(),"data/frame.png");
    inv_bg = SDL_CreateTexture(game::getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, sizeX*32, sizeY*32);
    SDL_SetRenderTarget(game::getRenderer(),inv_bg);
    SDL_Rect clipRect = {0,0,32,32};
    SDL_Rect destRect = {0,0,32,32};

    for(int y = 0;y<sizeY;y++)
    {
        for(int x = 0;x<sizeX;x++)
        {
            if(x == 0)
            {
                //SDL_RenderCopy(game::getRenderer(),frame,NULL,NULL);
                //frame.render(game::getRenderer(),NULL,0,NULL,SDL_FLIP_NONE);
            }
        }
    }

    SDL_SetRenderTarget(game::getRenderer(),NULL);
}

void Inventory::loadInventory()
{

}

void Inventory::draw()
{
    frame.render(game::getRenderer(),(SDL_Rect*)NULL,0,NULL,SDL_FLIP_NONE);
}

void Inventory::update()
{

}




