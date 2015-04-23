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

        GPhysics *physics{nullptr};
        Texture *texture{nullptr};
        Position *position{nullptr};

        EntityManager *manager{nullptr};

        int xPos; // x-position of the enemy.
        int yPos; // y-position of the enemy.
};

#endif // ENEMY_H
