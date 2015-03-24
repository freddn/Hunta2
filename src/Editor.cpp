#include "Editor.hpp"


Editor::Editor()
{
    //ctor

    r_select = SDL_CreateRGBSurface(0,36,36,32,0,0,0,0);
    SDL_FillRect(r_select,NULL,SDL_MapRGB(r_select->format,255,0,0));
    rect_select = SDL_CreateTextureFromSurface(game::getRenderer(),r_select);
    //

    rground.x = 0;
    rground.y = 2;
    rground.w = 32;
    rground.h = 32;

    rwater.x = 32*2;
    rwater.y = 2;
    rwater.w = 32;
    rwater.h = 32;

    rgrass.x = 32*4;
    rgrass.y = 2;
    rgrass.w = 32;
    rgrass.h = 32;

    sel.y = 0;
    sel.w = 36;
    sel.h = 36;
}

Editor::~Editor()
{
    //dtor
    SDL_FreeSurface(r_select);
    SDL_DestroyTexture(rect_select);
}



void Editor::render()
{
    Screen::renderStart();

    game::setRectX(game::getMouseX()-(game::getMouseX()%32)); // ?
    game::getRect()->y = game::getMouseY()-(game::getMouseY()%32); // ?

    switch(getSelected())
    {
    case(game::GRASS):
        sel.x = rgrass.x -2;
    break;
    case(game::GROUND):
        sel.x = rground.x -2;
    break;
    case(game::WATER):
        sel.x = rwater.x -2;
    break;
    }
    if(game::getHasChanged())
    {
        SDL_SetRenderTarget(game::getRenderer(),game::getBuffer());
        for(auto iter = game::getTexture_map()->begin(); iter != game::getTexture_map()->end();iter++)
        {
            if(((Texture*)iter->second)->getX() > -32 &&
                ((Texture*)iter->second)->getX() < game::getBackground()->w &&
                ((Texture*)iter->second)->getY() > -32 &&
                ((Texture*)iter->second)->getY() < game::getBackground()->h)
            {

                ((Texture*)iter->second)->render(game::getRenderer(),(SDL_Rect*)NULL,
                            (double)0.0,NULL,SDL_FLIP_NONE);
            }
        }
        SDL_SetRenderTarget(game::getRenderer(),NULL);
        game::setHasChanged(false);
    }
    SDL_RenderCopy(game::getRenderer(),game::getBuffer(),game::getOffset(),game::getBackground());
    SDL_RenderCopy(game::getRenderer(),rect_select,NULL,&sel);

    game::getTextureMap()->getGroundTile()->render(game::getRenderer(),rground.x,rground.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);
    game::getTextureMap()->getWaterTile()->render(game::getRenderer(),rwater.x,rwater.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);
    game::getTextureMap()->getGrassTile()->render(game::getRenderer(),rgrass.x,rgrass.y,(SDL_Rect*)NULL,
                    (double)0.0,NULL,SDL_FLIP_NONE);

    //CLICK EVENT..
    Screen::renderEnd();
}

void Editor::checkForInput()
{
    key = SDL_GetKeyboardState(NULL);
    if(key[SDL_SCANCODE_UP])
    {
        game::getOffset()->y = game::getOffset()->y - 4;
    }
    else if(key[SDL_SCANCODE_DOWN])
    {
        game::getOffset()->y = game::getOffset()->y + 4;
    }
    else if(key[SDL_SCANCODE_LEFT])
    {
        game::getOffset()->x = game::getOffset()->x - 4;
    }
    else if(key[SDL_SCANCODE_RIGHT])
    {
        game::getOffset()->x = game::getOffset()->x + 4;
    }
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        int tempX = (game::getMouseX()+game::getOffset()->x)-((game::getMouseX()+game::getOffset()->x)%32);
        int tempY = (game::getMouseY()+game::getOffset()->y)-((game::getMouseY()+game::getOffset()->y)%32);
        int index = (tempX/32)+((tempY/32)*40);

        if(game::getTexture_map()->count(index) < 2)
        {
            if(game::getTexture_map()->count(index) != 0)
            {
                game::getTexture_map()->erase(index);
            }
            if(getSelected() == game::GROUND)
            {
                /* place ground tile on map */
                Texture *temp = game::getTextureMap()->getGroundTile()->clone();
                temp->setXRect(tempX);
                temp->setYRect(tempY);
                game::getTexture_map()->insert(std::pair<int,Texture*>(index,temp));
            }
            else if(getSelected() == game::WATER)
            {
                /* place water on the map. */
                Texture *temp = game::getTextureMap()->getWaterTile()->clone();
                temp->setXRect(tempX);
                temp->setYRect(tempY);
                game::getTexture_map()->insert(std::pair<int,Texture*>(index,temp));
            }
            else
            {
                /* place grass on the map. */
                Texture *temp = game::getTextureMap()->getGrassTile()->clone();
                temp->setXRect(tempX);
                temp->setYRect(tempY);
                game::getTexture_map()->insert(std::pair<int,Texture*>(index,temp));
            }
            game::setHasChanged(true);
        }
    }

    Screen::checkForInput();
}




