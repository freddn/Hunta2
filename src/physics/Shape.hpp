#ifndef HUNTA2_SHAPE_HPP
#define HUNTA2_SHAPE_HPP

#include "Body.hpp"

struct Shape {
    enum Type {
        CIRCLE,
        RECT,
        sCount
    };
    Shape() {}
    virtual ~Shape() {};
    virtual Shape *clone( void ) const = 0;
    virtual void init( void ) = 0;
    virtual void computeMass( float density ) = 0;
    virtual void setOrient( float radians ) = 0;
    virtual Type getType( void ) const = 0;

    Body *body;

    float radius;
};

struct Circle : public Shape {
    Circle(float r) {radius = r;}
    Circle() {radius = 10;}
    ~Circle() {};
    Shape *clone() const {
        return new Circle(radius);
    }

    void init() {
        computeMass(1.0f);
    }

    void setOrient(float radians) {}

    void computeMass(float density) {
        body->mass = PI * radius * radius * density;
        body->invMass = (body->mass) ? 1.0f / body->mass : 0.0f;
        body->inertia = body->mass * radius * radius;
        body->invInertia = (body->inertia) ? 1.0f / body->inertia : 0.0f;
    }

    Type getType() const {
        return CIRCLE;
    }
};


struct AABB : public Shape {
    AABB() {}
    AABB(const Vec2 &min_, const Vec2 &max_) : min(min_), max(max_) {}
    ~AABB() {};

    Shape *clone() const {
        return new AABB();
    }

    void init() {
        computeMass(1.0f);
    }

    void setOrient(float radians) {}

    void computeMass(float density) {
        body->mass = (max.x-min.x) * (max.y-min.y) * density;
        body->invMass = (body->mass) ? 1.0f / body->mass : 0.0f;
        body->inertia = body->mass * (max.x-min.x) * (max.y-min.y) ;
        body->invInertia = (body->inertia) ? 1.0f / body->inertia : 0.0f;
    }

    Type getType() const {
        return RECT;
    }

    Vec2 min;
    Vec2 max;
};

#endif //HUNTA2_SHAPE_HPP
