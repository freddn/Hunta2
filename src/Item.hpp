#ifndef ITEM_HPP
#define ITEM_HPP

#include "Texture.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

/*
 * The item-class. An item can be picked up if it's on the ground. It will go
 * to the inventory if picked up.
 */
struct Item : Component
{
    public:
        Item();
        void init();
        void collision(); // remove?
        void action(); // remove?
        void pickUp();
        void getInfo();
        void draw();
        void update();
        virtual ~Item();
    protected:
    private:

};

#endif // ITEM_HPP






