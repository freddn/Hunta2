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
    creator.createPlayer(&inGameManager);
    creator.createItem(&inGameManager,0,100,100,true);
    creator.createItem(&inGameManager,0,150,150,true);

    creator.createEnvironment(&inGameManager,0,400,130);
    creator.createEnvironment(&inGameManager,0,130,300);
    creator.createEnvironment(&inGameManager,0,300,200);
    creator.createEnvironment(&inGameManager,0,220,300);

    //stick_T.loadFromFile(game::getRenderer(),"data/stick.png");
}

void InGame::draw()
{
    //std::cerr << "InGame::draw" << std::endl;
    Screen::renderStart();
    //std::cerr << "InGame::draw" << std::endl;
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

    //stick_T.render(game::getRenderer(),
    //                game::getRect()->x-game::getOffset()->x,
    //                game::getRect()->y-game::getOffset()->y,
     //               (SDL_Rect*)NULL, (double)0.0,NULL,SDL_FLIP_NONE);

    //player.draw();
    //std::cerr << "InGame::draw" << std::endl;
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
    //key = SDL_GetKeyboardState(NULL);
    //player.moveChar(4,key);
    //std::cerr << "InGame::update" << std::endl;
    inGameManager.refresh();
    //std::cerr << "manager.refresh()"<<std::endl;
    inGameManager.update();
    //std::cerr << "manager.update()"<<std::endl;
    //std::cout << "InGame::update" << std::endl;
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
    //std::cerr << "InGame::update" << std::endl;
    Screen::update();
}
