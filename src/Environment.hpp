#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "GPhysics.hpp"


struct Environment : EntitySystem::Component
{
    public:
        Environment();

        void init();

        bool isSolid();

        Position* getPosition();

        virtual ~Environment();
    protected:
    private:
    Position *position{nullptr};
    GPhysics *physics{nullptr};
    bool solid{true};
};

#endif // ENVIRONMENT_H
