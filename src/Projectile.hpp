#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "Texture.hpp"
#include "GPhysics.hpp"

using namespace EntitySystem;

struct Projectile : Component {
public:
    Projectile(int x, int y,int relX,int relY);
    void update();
    void init();
    ~Projectile();
private:
    int destX;
    int destY;
    int posY;
    int posX;
    GPhysics *physics{nullptr};
    //Texture *texture{nullptr};
    Position *position{nullptr};
};

#endif // PROJECTILE_H
