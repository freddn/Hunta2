//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_BODY_HPP
#define HUNTA2_BODY_HPP

#include "Math.h"
struct Shape;

/**
 * Entities can have a body. If an entity has the GPhysics component it also has a body which this class
 * represents.
 * A body has weight, velocity, position and other physical variables.
 */
struct Body {
    Body(Shape *shape, int x, int y);


    /**
     * Apply a force to the body. Can be if the body should be moved or if another body collides with this body.
     */
    void applyForce(const Vec2 &f) {
        force = force + f;
        force += -5*velocity; // "Cap" the velocity a body can have.
    }

    /**
     * Apply an impulse to this body.
     */
    void applyImpulse(const Vec2 &impulse, const Vec2 &contactVector) {
        velocity += invMass*impulse;
        angularVelocity += invInertia * Cross( contactVector, impulse);
    }

    /**
     * Set the body to be static, i.e, infinit mass and not movable. Ex Trees or houses.
     */
    void setStatic() {
        inertia = 0.0f;
        invInertia = 0.0f;
        mass = 0.0f;
        invMass = 0.0f;
    }

    bool isAlive() const;

    void destroy();

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

    bool alive;

    float r, g, b;
};


#endif //HUNTA2_BODY_HPP
