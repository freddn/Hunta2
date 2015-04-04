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
        Position(float xPos,float yPos);

        void update();

        float getX();
        float getY();
        void setX(float posX);
        void setY(float posY);
        /* TODO
         * - Add SDL_Rect.
         * - Setters and getters for the rect.
         */
        virtual ~Position();
    protected:
    private:
        float x{0};
        float y{0};
};

#endif // POSITION_H
