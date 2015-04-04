#ifndef GPHYSICS_H
#define GPHYSICS_H

#include "EntitySystem.hpp"
#include "Position.hpp"

/* The physics of an object. This class is a component and will
 * give an entity collision detection, velocity and movement.
 */
struct GPhysics : EntitySystem::Component
{
    public:
        GPhysics();
        // Collision
        void update();
        void init();

        bool isColliding(int dir, int x, int y);
        bool isColliding(int dir, Position destPos);

        void setDir(int dir, bool isMoving);
        void setVelocity(float v);
        void setXVelocity();
        void setYVelocity();
        float getXVel();
        float getYVel();
        bool dirUp = false;
        bool dirDown = false;
        bool dirLeft = false;
        bool dirRight = false;
        virtual ~GPhysics();
    protected:
    private:


        Position *position{nullptr};

        float xVel{0.0f};
        float yVel{0.0f};
        float vel{4};
};

#endif // GPHYSICS_H
