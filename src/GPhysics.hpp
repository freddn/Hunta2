#ifndef GPHYSICS_H
#define GPHYSICS_H

#include "EntitySystem.hpp"

/* The physics of an object. This class is a component and will
 * give an entity collision detection, velocity and movement.
 */
class GPhysics : EntitySystem::Component
{
    public:
        GPhysics();
        virtual ~GPhysics();
    protected:
    private:
};

#endif // GPHYSICS_H
