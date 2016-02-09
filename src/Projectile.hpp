#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "GPhysics.hpp"
#include "LTimer.hpp"

using namespace EntitySystem;


/**
 * A projectile component.
 */
struct Projectile : Component {
public:
    /**
     * Create a projectile whith the target position (relX,relY)
     */
    Projectile(int x, int y,int relX,int relY);

    /**
     * Move the projectile if it doesn't has reached its maximum range.
     */
    void update();

    /**
     * Give the destination position to the physics component, i.e., start the projectile.
     */
    void init();

    /**
     * Change the range of the projectile.
     */
    void setRange(int r);

    ~Projectile();
private:
    int destX;
    int destY;
    int posY;
    int posX;
    int startX = 0;
    int startY = 0;
    int range = 200;
    GPhysics *physics{nullptr};
    LTimer timer;
    Position *position{nullptr};
};

#endif // PROJECTILE_H
