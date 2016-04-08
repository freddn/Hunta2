//
// Created by fredrik on 3/2/16.
//

#include <iostream>
#include "PhysicsEngine.hpp"

#include "Shape.hpp"

namespace physics {

    void IntegrateForces( Body *b, float dt ) {
        if(b->invMass == 0.0f)
            return;

        b->velocity += (b->force * b->invMass + gravity) * (dt / 2.0f);
        b->angularVelocity += b->torque * b->invInertia * (dt / 2.0f);

        //b->force = Vec2(0,0);
    }

    void IntegrateVelocity( Body *b, float dt ) {
        if(b->invMass == 0.0f)
            return;

        b->position += b->velocity * dt;
        b->orient += b->angularVelocity * dt;
        b->setOrient( b->orient);
        IntegrateForces( b, dt );
    }

    void PhysicsEngine::step() {
        // Generate new collision info
        contacts.clear();
        for(unsigned int i = 0; i < bodies.size( ); ++i) {
            Body *bodyA = bodies[i];

            for(unsigned int j = i + 1; j < bodies.size( ); ++j) {
                Body *bodyB = bodies[j];
                if(bodyA->invMass == 0 && bodyB->invMass == 0)
                    continue;
                Manifold m(bodyA, bodyB);
                m.solve();
                if(m.contactCount)
                    contacts.emplace_back(m);
            }
        }

        // Integrate forces
        for(unsigned int i = 0; i < bodies.size(); ++i)
            IntegrateForces( bodies[i], dt_ );

        // Initialize collision
        for(unsigned int i = 0; i < contacts.size(); ++i)
            contacts[i].init();

        // Solve collisions
        for(int j = 0; j < iterations; ++j)
            for(unsigned int i = 0; i < contacts.size(); ++i)
                contacts[i].applyImpulse();

        // Integrate velocities
        for(unsigned int i = 0; i < bodies.size(); ++i)
            IntegrateVelocity( bodies[i], dt_ );

        // Correct positions
        for(unsigned int i = 0; i < contacts.size(); ++i)
            contacts[i].positionalCorrection();

        // Clear all forces
        for(unsigned int i = 0; i < bodies.size(); ++i) {
            Body *b = bodies[i];
            b->force.setVec2( 0, 0 );
            b->torque = 0;
        }
    }

    Body *PhysicsEngine::add(Shape *shape, int x, int y) {
        assert(shape);
        Body *b = new Body(shape, x, y);
        bodies.push_back(b);
        return b;
    }

    bool isColliding(AABB a, AABB b) {
        if(a.max.x < b.min.x || a.min.x > b.max.x)
            return false;
        if(a.max.y < b.min.y || a.min.y > b.max.y)
            return false;
        return true;
    }


    float distance(Vec2 a, Vec2 b) {
        return sqrt((((int)(a.x - b.x)^2) + ((int)(a.y - b.y)^2)));
    }


    /*bool circleIsColliding(Manifold *m) {
        Object *a = m->a;
        Object *b = m->b;

        Vec2 n = b->position - a->position;

        if(m->aType == CIRCLE && m->bType == CIRCLE) {

            float r = ((Circle*)a)->radius + ((Circle*)b)->radius;
            r *= r;
            if(n.LenSqr() > r)
                return false;

            //Circles have collided, compute manifold
            float d = n.Len(); // sqrt

            // distance between circles is not zero
            if(d != 0) {
                // Distance is difference between radius and distance
                m->penetration = r - d;

                m->normal = t / d;

            } else {
                m->penetration = ((Circle*)a)->radius;
                m->normal = Vec2(1, 0);
                return true;
            }
        } else if(m->aType == AABB && m->bType == AABB) {
            AABB abox = *((AABB*)a);
            AABB bbox = *((AABB*)b);

            // Calculate half extents along x axis
            float a_extent = (abox.max.x - abox.min.x) / 2;
            float b_extent = (bbox.max.x - bbox.min.x) / 2;

            // Overlap on x axis
            float x_overlap = a_extent + b_extent - std::abs(n.x);

            // SAT test
            if(x_overlap > 0) {
                // same for y
                float a_extent = (abox.max.y - abox.min.y) / 2;
                float b_extent = (bbox.max.y - bbox.min.y) / 2;

                float y_overlap = a_extent + b_extent - std::abs(n.y);

                if(y_overlap > 0) {
                    // Which axis is axis of least penetration
                    if(x_overlap > y_overlap) {
                        // Point towards b, n points from a to b
                        if(n.x < 0)
                            m->normal = Vec2(-1, 0);
                        else
                            m->normal = Vec2(1, 0);
                        m->penetration = x_overlap;
                        return true;
                    } else {
                        if(n.y < 0)
                            m->normal = Vec2(0, -1);
                        else
                            m->normal = Vec2(0, 1);
                        m->penetration = y_overlap;
                        return true;
                    }
                }
            }
        } else if((m->aType == CIRCLE && m->bType == AABB) ||
                    (m->aType == AABB && m->bType == CIRCLE)) {
            Vec2 closest = n;
        }

        return false;
    }

    void resolveCollision(Manifold *m) {
        Object *a = m->a;
        Object *b = m->b;

        // Relative velocity
        Vec2 rv = b->velocity - a->velocity;

        // Calculate relative velocity in terms of the normal direction
        float velAlongNormal = (rv.x* m->normal.x) + (rv.y* m->normal.y);

        if(velAlongNormal > 0)
            return;


        // Calculate restitution
        float e = std::min(a->restitution, b->restitution);

        if(a->mass == 0)
            a->inv_mass = 0;
        else
            a->inv_mass = 1/ a->mass;
        if(b->mass == 0)
            b->inv_mass = 0;
        else
            b->inv_mass = 1/ b->mass;

        // Calculate impulse scalar
        float j = -(1+e) * velAlongNormal;
        j /= a->inv_mass + b->inv_mass;

        // Apply impulse
        Vec2 impulse = m->normal * j;

        float mass_sum = a->mass + b->mass;
        float ratio = a->mass / mass_sum;
        a->velocity = a->velocity - (impulse*ratio);
        ratio = b->mass / mass_sum;
        b->velocity = b->velocity + (impulse*ratio);



        //a->velocity = a->velocity - (impulse * (1 / a->mass));
        //b->velocity = b->velocity + (impulse * (1 / b->mass));
    }

    void positionalCorrection(Manifold *m) {
        Object *a = m->a;
        Object *b = m->b;
        const float percent = 0.2; // 20% - 80%
        const float slop = 0.01; // 0.01 0.1

        Vec2 correction = std::max(m->penetration - slop, 0.0f) / ((m->normal * percent) * (a->inv_mass+b->inv_mass));

        a->position = a->position - (correction * a->inv_mass);//////////////////
        b->position = b->position + (correction * b->inv_mass);
    }*/

    void PhysicsEngine::refresh() {
        bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
           [](const Body *b) {
               return !b->isAlive();
           }), bodies.end());

    }
}