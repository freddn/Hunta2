#ifndef HUNTA2_MANIFOLD_HPP
#define HUNTA2_MANIFOLD_HPP

struct Body;

#include "Vec2.hpp"

struct Manifold {
    Manifold(Body *a, Body *b) : bodyA(a), bodyB(b) {}

    void solve();
    void init();
    void applyImpulse();
    void positionalCorrection();
    void infiniteMassCorrection();

    Body *bodyA;
    Body *bodyB;

    float penetration;
    Vec2 normal;
    Vec2 contacts[2];
    unsigned int contactCount;
    float e;
    float df;
    float sf;
};


#endif //HUNTA2_MANIFOLD_HPP
