#include "Body.hpp"
#include "Shape.hpp"

Body::Body(Shape *shape_, float x, float y)
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
    alive = true;
}

void Body::setOrient(float radians) {
    orient = radians;
    shape->setOrient(radians);
}

bool Body::isAlive() const {
    return alive;
}

void Body::destroy() {
    alive = false;
}

Body::~Body() {
    delete shape;
}
