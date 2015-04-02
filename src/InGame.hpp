#ifndef INGAME_H
#define INGAME_H

#include <memory>
#include <vector>
#include "Inventory.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include "Character.hpp"

#include "EntitySystem.hpp"
#include "EntityCreator.hpp"

using namespace EntitySystem;

/* This is the game-state of the game. Here we draw all game-related things
 * on the screen and deal with all input and events related to the game itself. */
struct InGame : public Screen
{
    public:
        InGame();
        void init();
        void update();
        void draw();
        void displayInventory(bool);
        ~InGame();
    protected:
    private:
        bool showInventory = false;
        //Inventory inv;

        //EntitySystem::EntityManager* inGameManager;
        EntityCreator creator;
        EntitySystem::EntityManager inGameManager;
        Item stick_T;
        Position playerPos;

        const Uint8 *key;
};

#endif // INGAME_H
