#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.hpp"
#include "EntitySystem.hpp"

/* The enemy class. */
struct Enemy : EntitySystem::Component
{
    public:
        Enemy();

        void init();
        void draw();
        void update();

        virtual ~Enemy();
    protected:
    private:
};

#endif // ENEMY_H
