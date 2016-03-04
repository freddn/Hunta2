//
// Created by fredrik on 3/2/16.
//

#include "Body.hpp"
#include "Shape.hpp"

Body::Body(Shape *shape_, int x, int y)
        : shape( shape_->clone() ) {
    shape->body = this;
    position.setVec2(x, y);
    velocity.setVec2( 0, 0 );
    angularVelocity = 0;
    torque = 0;
    orient = Random( -PI, PI );
    force.setVec2( 0, 0 );
    staticFriction = 0.5f;
    dynamicFriction = 0.3f;
    restitution = 0.2f;
    shape->init();
    r = Random( 0.2f, 1.0f );
    g = Random( 0.2f, 1.0f );
    b = Random( 0.2f, 1.0f );
}

void Body::setOrient(float radians) {
    orient = radians;
    shape->setOrient(radians);
}