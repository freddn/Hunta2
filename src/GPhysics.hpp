#ifndef GPHYSICS_H
#define GPHYSICS_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "Texture.hpp"

/*
 * The physics of an object. This class is a component and will
 * give an entity collision detection, velocity and movement.
 */
struct GPhysics : EntitySystem::Component
{
    public:
        GPhysics();
        void update();
        void init();
        void clearCol();
        bool isColliding(int x, int y);
        bool isColliding(EntitySystem::Entity *e);
        void setDir(int dir, bool isMoving);
        void setVelocity(float v);
        void setXVelocity();
        void setYVelocity();
        float getXVel();
        float getYVel();

        virtual ~GPhysics();
    protected:
    private:

        bool dirUp = false;
        bool dirDown = false;
        bool dirLeft = false;
        bool dirRight = false;
        bool colUp = false;
        bool colDown = false;
        bool colLeft = false;
        bool colRight = false;
        Position *position{nullptr};
        Texture *texture{nullptr};
        float xVel{0.0f};
        float yVel{0.0f};
        float vel{4};
};

#endif // GPHYSICS_H
