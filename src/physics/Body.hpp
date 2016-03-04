//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_BODY_HPP
#define HUNTA2_BODY_HPP

#include "Math.h"
struct Shape;

struct Body {
    Body(Shape *shape, int x, int y);

    void applyForce(const Vec2 &f) {
        force = force + f;
        force += -5*velocity;
    }

    void applyImpulse(const Vec2 &impulse, const Vec2 &contactVector) {
        velocity += invMass*impulse;
        angularVelocity += invInertia * Cross( contactVector, impulse);
    }

    void setStatic() {
        inertia = 0.0f;
        invInertia = 0.0f;
        mass = 0.0f;
        invMass = 0.0f;
    }

    void setOrient(float radians);

    Vec2 position;
    Vec2 velocity;

    float angularVelocity;
    float torque;
    float orient;

    Vec2 force;

    float inertia;
    float invInertia;
    float mass;
    float invMass;

    float staticFriction;
    float dynamicFriction;
    float restitution;

    Shape *shape;

    float r, g, b;
};


#endif //HUNTA2_BODY_HPP
