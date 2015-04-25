#include "InGame.hpp"

InGame::InGame()
{

}

InGame::~InGame()
{
    //stick_T.free();

}

void InGame::init()
{
    std::cout << " - InGame::init() ..."<<std::endl;
    creator.createPlayer(&inGameManager,game::getWidth(),game::getHeight());
    //creator.createPlayer(&inGameManager,20,20);
    creator.createItem(&inGameManager,0,100,100,true);
    creator.createItem(&inGameManager,0,150,150,true);

    creator.createEnvironment(&inGameManager,0,400,130);
    creator.createEnvironment(&inGameManager,0,130,300);
    creator.createEnvironment(&inGameManager,0,300,200);
    creator.createEnvironment(&inGameManager,0,220,300);
    creator.createEnvironment(&inGameManager,0,220,600);
    creator.createEnvironment(&inGameManager,0,720,300);
    creator.createEnvironment(&inGameManager,0,620,400);
    creator.createEnvironment(&inGameManager,0,1100,1200);

    creator.createEnemy(&inGameManager,0,300,300);
    creator.createEnemy(&inGameManager,0,345,290);
    //stick_T.loadFromFile(game::getRenderer(),"data/stick.png");
}

void InGame::draw()
{
    Screen::renderStart();

    /* Update background tiles. */
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
    /* Draw background tiles. */
    SDL_RenderCopy(game::getRenderer(),game::getBuffer(),
                    game::getOffset(),game::getBackground());

    /* Draw all entities. */
    inGameManager.draw();

    /* Display inventory */
    if(game::inventoryIsDisplayed())
    {
        //inv.draw();
    }
    Screen::renderEnd();
}

void InGame::update()
{
    inGameManager.refresh(); /* Delete removed entities. */
    inGameManager.update();

    auto& characters(inGameManager.getEntitiesByGroup(game::PLAYER));
    //std::cout << "characters " << std::endl;
    if(!characters.empty() && characters[0]->hasComponent<Position>())
    {

        //std::cout << "position exist" << std::endl;
        playerPos = characters[0]->getComponent<Position>();

        if((playerPos.getX() - (game::getWidth()/2)) > 0 &&
            (playerPos.getX() + (game::getWidth()/2)) < game::getBackground()->w*2)
        {
            game::getOffset()->x = playerPos.getX() - game::getWidth()/2;
        }
        if((playerPos.getY() - (game::getHeight()/2)) > 0 &&
            (playerPos.getY() + (game::getHeight()/2)) < game::getBackground()->h*2)
        {
            game::getOffset()->y = playerPos.getY() - game::getHeight()/2;
        }
    }

    /* Inventory input */
    if(game::inventoryIsDisplayed())
    {
        //inv.update();
    }
    Screen::update();
}
