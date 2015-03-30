#include "InGame.hpp"

#include "EntitySystem.hpp"

using namespace EntitySystem;

InGame::InGame()
{

}

InGame::~InGame()
{
    stick_T.free();

}

void InGame::init()
{
    auto& entity(manager.addEntity());
    //auto& entity = manager.addEntity();

    player = entity.addComponent<Character>();
    std::cout << "player loaded to entity";
    entity.addGroup(game::PLAYER);
    //auto& player(entity.getComponent<Character>());
    //player.init();
    stick_T.loadFromFile(game::getRenderer(),"data/stick.png");
}

void InGame::draw()
{
    Screen::renderStart();

    if(game::getHasChanged())
    {
        SDL_SetRenderTarget(game::getRenderer(),game::getBuffer());
        for(auto iter = game::getTexture_map()->begin(); iter != game::getTexture_map()->end();iter++)
        {
            //std::cout << "render texure" << std::endl;
            ((Texture*)iter->second)->render(game::getRenderer(),
                                    (SDL_Rect*)NULL,
                                    (double)0.0,NULL,SDL_FLIP_NONE);
        }
        SDL_SetRenderTarget(game::getRenderer(),NULL);
        game::setHasChanged(false);
    }
    SDL_RenderCopy(game::getRenderer(),game::getBuffer(),
                    game::getOffset(),game::getBackground());

    stick_T.render(game::getRenderer(),
                    game::getRect()->x-game::getOffset()->x,
                    game::getRect()->y-game::getOffset()->y,
                    (SDL_Rect*)NULL, (double)0.0,NULL,SDL_FLIP_NONE);

    //player.draw();
    manager.draw();

    /* Display inventory */
    if(game::inventoryIsDisplayed())
    {
        //inv.draw();
    }
    Screen::renderEnd();
}

void InGame::update()
{
    //key = SDL_GetKeyboardState(NULL);
    //player.moveChar(4,key);

    manager.update();
    manager.refresh();
    auto& characters(manager.getEntitiesByGroup(game::PLAYER));
    player = characters[0]->getComponent<Character>();

    if((player.getX() - (game::getWidth()/2)) > 0 &&
        (player.getX() + (game::getWidth()/2)) < game::getBackground()->w*2)
    {
        game::getOffset()->x = player.getX() - game::getWidth()/2;
    }
    if((player.getY() - (game::getHeight()/2)) > 0 &&
        (player.getY() + (game::getHeight()/2)) < game::getBackground()->h*2)
    {
        game::getOffset()->y = player.getY() - game::getHeight()/2;
    }

    /* Inventory input */
    if(game::inventoryIsDisplayed())
    {
        //inv.update();
    }
    Screen::update();
}
