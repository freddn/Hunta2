#ifndef INGAME_H
#define INGAME_H


#include "Inventory.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include "Character.hpp"

class Inventory;

class InGame : public Screen
{
    public:
        InGame();
        void init();
        void checkForInput();
        void render();
        void displayInventory(bool);
        virtual ~InGame();
    protected:
    private:
    bool showInventory = false;
    Inventory inv;
    Item stick_T;
    Character player;
    const Uint8 *key;
};

#endif // INGAME_H
