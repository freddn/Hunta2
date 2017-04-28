#ifndef HUNTA2_PHYSICSHELPER_HPP
#define HUNTA2_PHYSICSHELPER_HPP

#include <memory>
#include <vector>

#include "Vec2.hpp"
#include "Shape.hpp"
#include "Manifold.hpp"


namespace physics {
    struct PhysicsEngine {
        PhysicsEngine(float d, int iterations_) :
        dt_(d), iterations(iterations_) {}
        ~PhysicsEngine();

        void step();
        void refresh();

        Body *add(Shape *shape, float x, float y);

        float dt_;
        int iterations;
        std::vector<std::unique_ptr<Body>> bodies;
        std::vector<Manifold> contacts;
    };
}


#endif //HUNTA2_PHYSICSHELPER_HPP
