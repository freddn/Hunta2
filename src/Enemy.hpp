#ifndef ENEMY_H
#define ENEMY_H

#include "Game.hpp"
#include "Texture.hpp"
#include "GPhysics.hpp"
#include "Position.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;
/* The enemy class. */
struct Enemy : Component
{
    public:
        Enemy(EntityManager *m);

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
        int xSpawnPos;
        int ySpawnPos;

        int enemyID = -1;

        bool aggro;
};

#endif // ENEMY_H
