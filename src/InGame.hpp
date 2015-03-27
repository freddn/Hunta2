#ifndef INGAME_H
#define INGAME_H


#include "Inventory.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include "Character.hpp"

struct InGame : public Screen
{
    public:
        //InGame();
        void init() override;
        void update() override;
        void draw() override;
        void displayInventory(bool);
        ~InGame() override;
    protected:
    private:
        bool showInventory = false;
        //Inventory inv;
        Item stick_T;
        Character player;
        const Uint8 *key;
};

#endif // INGAME_H
