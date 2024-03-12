/* Copyright (C) 2015 Fredrik Mörtberg <fredrikmo@hotmail.com>
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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Hunta2. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Character.hpp"

#include "Projectile.hpp"
#include "Item.hpp"
#include "../common/HelperFunctions.hpp"

#include "../Global.hpp"
#include "../Enums.hpp"

Character::Character() {
}

Character::Character(EntitySystem::EntityManager &m) {
    manager = &m;
}

Character::~Character() {
}

void Character::init() {
    HelperFunctions::log("Character::init() ...");
    position = &entity->getComponent<Position>();
    texture = &entity->getComponent<Texture>();
    physics = &entity->getComponent<GPhysics>();
    health = &entity->getComponent<Health>();

    level = game::getPlayerController()->getLevel();

    physics->setKeyControlled(true);
    /// Set the right offset.
    if(position->getX()-(game::getOffset()->w/2) < 0)
        game::getOffset()->x = 0;
    else if(position->getX()+(game::getOffset()->w/2) > game::getOffset()->w*2)
        game::getOffset()->x = game::getOffset()->w;
    else
        game::getOffset()->x = (int)position->getX() - (game::getOffset()->w/2);

    if(position->getY()-(game::getOffset()->h/2) < 0)
        game::getOffset()->y = 0;
    else if(position->getY()+(game::getOffset()->h/2) > game::getOffset()->h*2)
        game::getOffset()->y = game::getOffset()->h;
    else
        game::getOffset()->y = (int)position->getY() - (game::getOffset()->h/2);

    /// Set the position of the texture.
    texture->setXRect(game::getOffset()->w-game::getOffset()->x);
    texture->setYRect(game::getOffset()->h-game::getOffset()->y);
}

void Character::update() {
    //SDL_PumpEvents();
    const Uint8 *key = SDL_GetKeyboardState(NULL);
    moveChar(key);
    game::getPlayerController()->setPosX((int)position->getX());
    game::getPlayerController()->setPosY((int)position->getY());
    /* FIXME */
    if(game::getPlayerController()->getLevel() != level ||
       game::getPlayerController()->getHealthChanged()) {
        game::getPlayerController()->setHealthChanged(false);
        health->setMaxHp(game::getPlayerController()->getHp());
        health->setHp(game::getPlayerController()->getCurrentHp());
        level = game::getPlayerController()->getLevel();
    }

    /// Look for items to pick up.
    for(auto& e: manager->getEntitiesByGroup(game::ITEM)) {
        Position temp = e->getComponent<Position>();
        int width = e->getComponent<Texture>().getWidth();
        int height = e->getComponent<Texture>().getHeight();

        if((position->getX()+10 < temp.getX()+width &&
                position->getX()+22 > temp.getX()) &&
                (position->getY()+10 < temp.getY()+height &&
                 position->getY()+22 > temp.getY())) {

            int success = game::getInventory()->addItem(e->getComponent<Item>().getID(),
                                          e->getComponent<Item>().getAmount());
            if(success == 0)
                e->destroy();
        }
    }

    /// Check if left mouse button is pressed.
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if(!attacking) {
            attacking = true;
            // Fire a projectile..
            if(manager->canAdd()) {
                auto &projectile(manager->addEntity());
                projectile.addComponent<Position>(position->getX()+20,
                                                  position->getY()+40);
                projectile.addComponent<Texture>("data/fireball.png",false);
                projectile.addComponent<GPhysics>();
                projectile.addComponent<Projectile>(
                        game::getMouseX()+game::getOffset()->x,
                        game::getMouseY()+game::getOffset()->y,
                        game::getMouseX()+game::getOffset()->x-position->getX(),
                        game::getMouseY()+game::getOffset()->y-position->getY());
                projectile.addGroup(game::PROJECTILE);
                projectile.getComponent<GPhysics>().setVelocity(20);
            }
        }
    } else
        attacking = false;
}

void Character::moveChar(const Uint8 *key) {
    /// Walk downwards
    if(key[SDL_SCANCODE_DOWN]) {
        physics->setDir(game::SOUTH,true); /// Set this walking direction true.
        //texture->setClipX(0);
        texture->setClipY(0);
    } else
        physics->setDir(game::SOUTH,false); /// Set this walking direction false.

    /// Walk upwards
    if(key[SDL_SCANCODE_UP]) {
        physics->setDir(game::NORTH,true); /// Set this walking direction true.
        //texture->setClipX(1);
        texture->setClipY(0);
    } else
        physics->setDir(game::NORTH,false); /// Set this walking direction false.

    /// Walk to right
    if(key[SDL_SCANCODE_RIGHT]) {
        physics->setDir(game::EAST,true); /// Set this walking direction true.
        texture->setClipX(1);
        texture->setClipY(1);
    } else
        physics->setDir(game::EAST,false); /// Set this walking direction false.

    /// Walk to left
    if(key[SDL_SCANCODE_LEFT]) {
        physics->setDir(game::WEST,true); /// Set this walking direction true.
        texture->setClipX(0);
        texture->setClipY(1);
    } else
        physics->setDir(game::WEST,false); /// Set this walking direction false.
}

