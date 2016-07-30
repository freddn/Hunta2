#include "Manifold.hpp"
#include "Collision.hpp"

void Manifold::solve() {
    Dispatch[bodyA->shape->getType()][bodyB->shape->getType()]( this, bodyA, bodyB);
}

void Manifold::init() {
    // Calculate average restitution
    e = std::min(bodyA->restitution, bodyB->restitution);

    // Calculate static and dynamic friction
    sf = std::sqrt(bodyA->staticFriction * bodyB->staticFriction);
    df = std::sqrt(bodyA->dynamicFriction * bodyB->dynamicFriction);

    for(unsigned int i = 0; i < contactCount; ++i)
    {
        // Calculate radii from COM to contact
        Vec2 ra = contacts[i] - bodyA->position;
        Vec2 rb = contacts[i] - bodyB->position;

        Vec2 rv = bodyB->velocity + Cross(bodyB->angularVelocity, rb) -
                  bodyA->velocity - Cross(bodyA->angularVelocity, ra);


        // Determine if we should perform a resting collision or not
        // The idea is if the only thing moving this object is gravity,
        // then the collision should be performed without any restitution
        if(rv.LenSqr() < (dt * gravity).LenSqr() + EPSILON)
            e = 0.0f;
    }
}

void Manifold::applyImpulse() {
    // Early out and positional correct if both objects have infinite mass
    if(Equal(bodyA->invMass + bodyB->invMass, 0)) {
        infiniteMassCorrection();
        return;
    }

    for(unsigned int i = 0; i < contactCount; ++i) {
        // Calculate radii from COM to contact
        Vec2 ra = contacts[i] - bodyA->position;
        Vec2 rb = contacts[i] - bodyB->position;

        // Relative velocity
        Vec2 rv = bodyB->velocity + Cross(bodyB->angularVelocity, rb) -
                bodyA->velocity - Cross(bodyA->angularVelocity, ra);
        normal.Normalize();
        // Relative velocity along the normal
        float contactVel = Dot(rv, normal);

        // Do not resolve if velocities are separating
        if(contactVel > 0)
            return;

        float raCrossN = Cross(ra, normal);
        float rbCrossN = Cross(rb, normal);
        float invMassSum = bodyA->invMass + bodyB->invMass + Sqr(raCrossN) *
                          bodyA->invInertia + Sqr(rbCrossN) * bodyB->invInertia;

        // Calculate impulse scalar
        float j = -(1.0f + e) * contactVel;
        j /= invMassSum;
        j /= (float)contactCount;

        // Apply impulse
        Vec2 impulse = normal * j;
        bodyA->applyImpulse( -impulse, ra );
        bodyB->applyImpulse( impulse, rb );

        // Friction impulse
        rv = bodyB->velocity + Cross( bodyB->angularVelocity, rb ) -
                bodyA->velocity - Cross( bodyA->angularVelocity, ra );

        Vec2 t = rv - (normal * Dot( rv, normal ));
        t.Normalize( );

        float jt = -Dot( rv, t );
        jt /= invMassSum;
        jt /= (float)contactCount;

        // Don't apply tiny friction impulses
        if(Equal( jt, 0.0f ))
            return;

        // Coulumb's law
        Vec2 tangentImpulse;
        if(std::abs( jt ) < j * sf)
            tangentImpulse = t * jt;
        else
            tangentImpulse = t * -j * df;

        // Apply friction impulse
        bodyA->applyImpulse( tangentImpulse, ra );
        bodyB->applyImpulse( -tangentImpulse, rb );
    }
}

void Manifold::positionalCorrection( void ) {
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.4f; // Penetration percentage to correct
    Vec2 correction = (std::max(penetration - k_slop, 0.0f )/(bodyA->invMass + bodyB->invMass))*normal*percent;
    bodyA->position -= correction * bodyA->invMass;
    bodyB->position += correction * bodyB->invMass;
}

void Manifold::infiniteMassCorrection() {
    bodyA->velocity.setVec2( 0, 0 );
    bodyB->velocity.setVec2( 0, 0 );
}