#include <iostream>
#include "PhysicsEngine.hpp"

namespace physics {

    void IntegrateForces( Body *b, float dt ) {
        if(b->invMass == 0.0f)
            return;

        b->velocity += (b->force * b->invMass + gravity) * (dt / 2.0f);
        b->angularVelocity += b->torque * b->invInertia * (dt / 2.0f);
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
            Body *bodyA = bodies[i].get();

            for(unsigned int j = i + 1; j < bodies.size( ); ++j) {
                Body *bodyB = bodies[j].get();
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
            IntegrateForces( bodies[i].get(), dt_ );

        // Initialize collision
        for(unsigned int i = 0; i < contacts.size(); ++i)
            contacts[i].init();

        // Solve collisions
        for(int j = 0; j < iterations; ++j)
            for(unsigned int i = 0; i < contacts.size(); ++i)
                contacts[i].applyImpulse();

        // Integrate velocities
        for(unsigned int i = 0; i < bodies.size(); ++i)
            IntegrateVelocity( bodies[i].get(), dt_ );

        // Correct positions
        for(unsigned int i = 0; i < contacts.size(); ++i)
            contacts[i].positionalCorrection();

        // Clear all forces
        for(unsigned int i = 0; i < bodies.size(); ++i) {
            Body *b = bodies[i].get();
            b->force.setVec2( 0, 0 );
            b->torque = 0;
        }
    }

    Body *PhysicsEngine::add(Shape *shape, float x, float y) {
        assert(shape);

        Body *b = new Body(shape, x, y);
        std::unique_ptr<Body> uPtr{b};
        bodies.push_back(std::move(uPtr));
        return b;
    }

    void PhysicsEngine::refresh() {
        bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
           [](const std::unique_ptr<Body> &b) {
               return !b.get()->isAlive();
           }), bodies.end());
    }

    PhysicsEngine::~PhysicsEngine() {
        bodies.clear();
    }
}