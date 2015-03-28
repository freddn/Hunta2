#ifndef ITEM_HPP
#define ITEM_HPP

#include "Texture.hpp"
#include "EntitySystem.hpp"


/**
    An item, can be picked up.
*/
class Item : public Texture, EntitySystem::Component
{
    public:
        Item();
        void init();
        void collision(); // What happens when collision with item occurs?
        void action(); // Action to perform?
        void pickUp();
        void getInfo();
        void draw();
        void update();
        virtual ~Item();
    protected:
    private:

};

#endif // ITEM_HPP






