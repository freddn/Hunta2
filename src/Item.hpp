#ifndef ITEM_HPP
#define ITEM_HPP

#include "Texture.hpp"

/**
    An item, can be picked up.
*/
class Item : public Texture
{
    public:
        Item();

        void collision(); // What happens when collision with item occurs?
        void action(); // Action to perform?

        virtual ~Item();
    protected:
    private:

};

#endif // ITEM_HPP






