/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 *
 * This file is a part of the Hunta2 project.
 *
 * Hunta2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hunta2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "InGame.hpp"

InGame::InGame() {

}

InGame::~InGame() {
    //stick_T.free();

}

void InGame::init() {
    std::cout << " - InGame::init() ..."<<std::endl;
    inv.init();
    inGameManager.reserveEntities(300);

    // CALL A LUA SCRIPT THAT LOADS ALL ENTITYS!!

    //creator.createPlayer(inGameManager,creator,game::getWidth(),game::getHeight());
    //creator.createPlayer(&inGameManager,20,20);
    creator.createItem(inGameManager,0,100,100,true);
    creator.createItem(inGameManager,0,150,150,true);

    creator.createEnvironment(inGameManager,0,400,130);
    creator.createEnvironment(inGameManager,0,130,300);
    creator.createEnvironment(inGameManager,0,300,200);
    creator.createEnvironment(inGameManager,0,220,300);
    creator.createEnvironment(inGameManager,0,220,600);
    creator.createEnvironment(inGameManager,0,720,300);
    creator.createEnvironment(inGameManager,0,4,400);
    creator.createEnvironment(inGameManager,0,1,300);
    creator.createEnvironment(inGameManager,0,220,600);
    creator.createEnvironment(inGameManager,0,7,300);
    creator.createEnvironment(inGameManager,0,9,400);
    creator.createEnvironment(inGameManager,0,1100,1200);

    creator.createEnemy(inGameManager,1,300,300);
    creator.createEnemy(inGameManager,0,345,290);
    creator.createEnemy(inGameManager,1,530,300);
    creator.createEnemy(inGameManager,0,790,570);
    creator.createEnemy(inGameManager,0,345,390);

    tInterface.loadFromFile("data/interface.png"); /// Sample interface
}

void InGame::draw() {
    Screen::renderStart();
    //game::getTextureMap()->draw();
    if(game::getTextureMapController()->mapExists(1)) {
        //std::cerr << "map 1 draw()" << std::endl;
        game::getTextureMapController()->getMap(1)->draw();
    }

    // Update background tiles.
    /*if(game::getHasChanged()) {
        SDL_SetRenderTarget(game::getRenderer(),game::getBuffer());
        for(auto iter = game::getTextureMap()->begin(); iter != game::getTextureMap()->end();iter++) {
            //std::cout << "render texure" << std::endl;
            ((std::shared_ptr<Texture>)iter->second)->render((SDL_Rect*)NULL);
        }
        SDL_SetRenderTarget(game::getRenderer(),NULL);
        game::setHasChanged(false);
    }
    // Draw background tiles.
    SDL_RenderCopy(game::getRenderer(),game::getBuffer(),
                    game::getOffset(),game::getBackground());
*/
    // Draw all entities.
    //inGameManager.draw();
    tInterface.render(0,0,NULL); /// Sample interface
    // Display inventory
    if(showInventory)
        inv.draw();

    Screen::renderEnd();
}

void InGame::update() {
    //inGameManager.refresh(); /* Delete removed entities. */
    //inGameManager.update();
    if(game::getTextureMapController()->mapExists(1)) {
        //std::cerr << "map 1 draw()" << std::endl;
        game::getTextureMapController()->getMap(1)->update();
    }
    /*auto& characters(inGameManager.getEntitiesByGroup(game::PLAYER));
    //std::cout << "characters " << std::endl;
    /// TODO implement camera and keyboardcontroller for the player...
    if(!characters.empty() && characters[0]->hasComponent<Position>()) {

        //std::cout << "position exist" << std::endl;
        playerPos = characters[0]->getComponent<Position>();

        if((playerPos.getX() - (game::getWidth()/2)) > 0 &&
            (playerPos.getX() + (game::getWidth()/2)) < game::getBackground()->w*2) {
            game::getOffset()->x = playerPos.getX() - game::getWidth()/2;
        }
        if((playerPos.getY() - (game::getHeight()/2)) > 0 &&
            (playerPos.getY() + (game::getHeight()/2)) < game::getBackground()->h*2) {
            game::getOffset()->y = playerPos.getY() - game::getHeight()/2;
        }
    }*/

    key = SDL_GetKeyboardState(NULL);
    if(key[SDL_SCANCODE_I]) {
        if(!showInventory && buf == 10) {
            buf = 0;
            showInventory = true;
            inv.loadInventory();
        } else if(showInventory && buf == 10) {
            buf = 0;
           showInventory = false;
        } else
            buf++;
    }
    else
        buf = 10;

    /* Inventory input */
    if(showInventory)
        inv.update();

    Screen::update();
}




