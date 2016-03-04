//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_PHYSICSHELPER_HPP
#define HUNTA2_PHYSICSHELPER_HPP

#include "Vec2.hpp"
#include "Shape.hpp"
#include "Manifold.hpp"


namespace physics {
    struct PhysicsEngine {
        PhysicsEngine(float d, int iterations_) :
        dt_(d), iterations(iterations_) {}

        void step();
        void clear();
        Body *add(Shape *shape, int x, int y);

        float dt_;
        int iterations;
        std::vector<Body*> bodies;
        std::vector<Manifold> contacts;
    };

    /** Check for collision */
    bool isColliding(float x, float y); /// Current entity is inside this position?
    bool isColliding(AABB a, AABB b);
    bool isColliding(Circle a, Circle b);
    bool isColliding(Manifold *m);

    float distance(Vec2 a, Vec2 b);


}


#endif //HUNTA2_PHYSICSHELPER_HPP
