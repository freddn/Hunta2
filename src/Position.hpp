#ifndef POSITION_H
#define POSITION_H

#include "EntitySystem.hpp"

/* This class is a component and will give entitys a position.
 * This position is used in collision-system, drawing and movement.
 */
class Position : EntitySystem::Component
{
    public:
        Position();

        void update();

        int getX();
        int getY();
        void setX(int posX);
        void setY(int posY);

        virtual ~Position();
    protected:
    private:
        int x;
        int y;
};

#endif // POSITION_H
