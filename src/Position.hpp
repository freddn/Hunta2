#ifndef POSITION_H
#define POSITION_H

#include "EntitySystem.hpp"

/* This class is a component and will give entitys a position.
 * This position is used in collision-system, drawing and movement.
 */
struct Position : EntitySystem::Component
{
    public:
        Position();
        Position(int xPos,int yPos);

        void update();

        int getX();
        int getY();
        void setX(int posX);
        void setY(int posY);
        /* TODO
         * - Add SDL_Rect.
         * - Setters and getters for the rect.
         */
        virtual ~Position();
    protected:
    private:
        int x;
        int y;
};

#endif // POSITION_H
